// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TargetIndicator.h"

#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "NiagaraComponent.h"
#include "Curves/CurveFloat.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "SkillBase.h"

#include "GameFramework/Character.h"

// Sets default values
ATargetIndicator::ATargetIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ConeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConeMesh"));
	ConeMesh->SetupAttachment(RootComponent);

	TargetDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("TargetDecal"));
	TargetDecal->SetupAttachment(RootComponent);
	TargetDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); // 바닥을 바라보게 회전

	SkillRangeDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("SkillRangeDecal"));
	SkillRangeDecalComponent->SetupAttachment(RootComponent);
	SkillRangeDecalComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f)); // 바닥을 바라보게 회전
	//SkillRangeDecal->SetVisibility(false);

	LineEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LineEffect"));
	LineEffect->SetupAttachment(RootComponent);

	// 커서 올릴 수 있는 땅 및 지형
	FloorObjTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	FloorObjTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	// 커서 올릴 수 있는 상대방
	HoverObjTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Enemy));
}

// Called when the game starts or when spawned
void ATargetIndicator::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ATargetIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC) return;

	float Offset = 0.f;

	if (OffsetCurve)
	{
		OffsetTimer += DeltaTime * 0.5f;
		if (OffsetTimer > 1.0f) OffsetTimer = 0.0f;

		Offset = FMath::Lerp(0.0f, 100.0f, OffsetCurve->GetFloatValue(OffsetTimer)) + 50.0f;
	}

	FHitResult HitResult;

	// [수정] 스킬 범위를 보여주는 중일 때는 락을 강제로 풀고 오직 땅바닥만 레이싱합니다.
	if (bShowSkillRange)
	{
		bCursorLock = false;
		CurrentTarget = nullptr;

		if (PC->GetHitResultUnderCursorForObjects(FloorObjTypes, false, HitResult) && HitResult.bBlockingHit)
		{
			LastCursorLocation = HitResult.ImpactPoint;
		}
	}
	else if (!bCursorLock) // 스킬 범위 표시 중이 아니고, 락이 풀려있을 때만 정상 작동
	{
		if (PC->GetHitResultUnderCursorForObjects(HoverObjTypes, false, HitResult) && HitResult.bBlockingHit)
		{
			CurrentTarget = HitResult.GetActor();
		}
		else if (PC->GetHitResultUnderCursorForObjects(FloorObjTypes, false, HitResult) && HitResult.bBlockingHit)
		{
			CurrentTarget = nullptr;
		}

		LastCursorLocation = HitResult.ImpactPoint;
	}
	else
	{
		if (CurrentTarget && !IsValid(CurrentTarget))
		{
			CurrentTarget = nullptr;
		}
	}

	// ---------------------------------------------------------------------------
	// [2단계] 최종 연산 목적지 좌표 설정
	// ---------------------------------------------------------------------------
	FVector FinalTargetLocation = FVector::ZeroVector;

	// [수정] bShowSkillRange 상태일 때는 CurrentTarget이 무조건 nullptr이므로 자동으로 LastCursorLocation을 따릅니다.
	if (CurrentTarget)
	{
		FinalTargetLocation = CurrentTarget->GetActorLocation();
	}
	else
	{
		FinalTargetLocation = bCursorLock ? LastCursorLocation : HitResult.ImpactPoint;
	}

	// ---------------------------------------------------------------------------
	// [3단계] 결정된 최종 좌표(FinalTargetLocation) 기반 피드백 표현 영역
	// ---------------------------------------------------------------------------

	if (bShowSkillRange)
	{
		// [수정] 스킬 범위 표시 시에는 땅바닥 위치(LastCursorLocation) 기준으로 고정 처리
		SetActorLocation(LastCursorLocation);

		ConeMesh->SetRelativeLocation(FVector(0.f, 0.f, Offset));
		if (SkillRangeDecalComponent)
		{
			SkillRangeDecalComponent->SetWorldLocation(LastCursorLocation);
		}
	}
	else
	{
		// 기본 위치 설정은 bShowSkillRange가 아닐 때만 작동
		SetActorLocation(FinalTargetLocation);

		if (CurrentTarget)
		{
			FVector Center;
			FVector BoxExtent;
			CurrentTarget->GetActorBounds(false, Center, BoxExtent);

			ConeMesh->SetRelativeLocation(FVector(0.f, 0.f, Offset + BoxExtent.Z * 1.5f));

			float EnemyRadius = FMath::Max(BoxExtent.X, BoxExtent.Y);
			float DecalRadius = EnemyRadius + 15.0f;

			TargetDecal->DecalSize = FVector(100.0f, DecalRadius, DecalRadius);
			TargetDecal->SetWorldLocation(FinalTargetLocation);
		}
		else
		{
			ConeMesh->SetRelativeLocation(FVector(0.f, 0.f, Offset));

			TargetDecal->DecalSize = FVector(100.0f, 35.0f, 35.f);
			TargetDecal->SetWorldLocation(FinalTargetLocation);
		}
	}

	// [수정] 나이아가라 점선 제어: bShowSkillRange가 켜져있으면 조건 불문하고 무조건 끕니다.
	if (!bShowSkillRange && (CurrentTarget || bCursorLock))
	{
		if (ACharacter* Character = PC->GetCharacter())
		{
			LineEffect->SetVisibility(true);
			LineEffect->SetVectorParameter(FName("StartPos"), FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, 0.0f));
			LineEffect->SetVectorParameter(FName("EndPos"), FVector(FinalTargetLocation.X, FinalTargetLocation.Y, 0.0f));
		}
	}
	else
	{
		LineEffect->SetVisibility(false);
	}

}

void ATargetIndicator::ShowSkillRange(TObjectPtr<USkillBase> Skill)
{
	TObjectPtr<UMaterialInstanceDynamic> Material = ConeMesh->CreateDynamicMaterialInstance(0, ConeMesh->GetMaterial(0));

	Material->SetVectorParameterValue(FName("Color"), FLinearColor::Blue);

	TargetDecal->SetVisibility(false);

	if (!bShowSkillRange)
	{
		bShowSkillRange = true;

		if (!SkillRangeDecalComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("SkillRangeDecalComponent : Component Init Failed"))
			return;
		}

		SkillRangeDecalComponent->SetDecalMaterial(Skill->GetDecalMaterial());
		FVector2D SkillBound = Skill->GetSkillBound();
		SkillRangeDecalComponent->DecalSize = FVector(15.f, SkillBound.X, SkillBound.Y);
		SkillRangeDecalComponent->SetVisibility(true);
	}
}

void ATargetIndicator::HideSkillRange()
{
	TObjectPtr<UMaterialInstanceDynamic> Material = ConeMesh->CreateDynamicMaterialInstance(0, ConeMesh->GetMaterial(0));

	Material->SetVectorParameterValue(FName("Color"), FLinearColor::Red);

	TargetDecal->SetVisibility(true);

	bShowSkillRange = false;

	if (!SkillRangeDecalComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillRangeDecalComponent : Component Init Failed"))
		return;
	}

	SkillRangeDecalComponent->SetVisibility(false);
	SkillRangeDecalComponent = nullptr;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Exorcist.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

#include "AnimInstanceBase_Exorcist.h"
#include "ExorcistController.h"
#include "SkillManager.h"
#include "SkillBase.h"
#include "StatusAttribute.h"
#include "TargetIndicator.h"

// Sets default values
AExorcist::AExorcist()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultArmLength = 650.f;
	DefaultCameraRotation = FRotator(-50.f, 0.f, 0.f);
	DefaultCameraPosition = FVector(0.0f, 0.0f, 600.0f);
	DefaultRotationRate = FRotator(0.f, 640.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->RotationRate = DefaultRotationRate;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = DefaultArmLength;       
	CameraBoom->SetRelativeRotation(DefaultCameraRotation); 
	CameraBoom->SetRelativeLocation(DefaultCameraPosition);
	CameraBoom->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	GetCapsuleComponent()->SetCapsuleRadius(35.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->bReceivesDecals = false;

	SkillManager = CreateDefaultSubobject<USkillManager>(TEXT("SkillManager"));
	StatusAttribute = CreateDefaultSubobject<UStatusAttribute>(TEXT("StatusAttribute"));

	// Set StatusAttribute At Derived Classes

	StatusAttribute->SetMaxSpeed(500.0f);

}

void AExorcist::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetMesh())
		AnimInstance = Cast<UAnimInstanceBase_Exorcist>(GetMesh()->GetAnimInstance());
	else
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance Not Selected"));



	if (!IsValid(SkillManager) || !IsValid(StatusAttribute))
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);


	State.AddTag(Tags::Exorcist_Idle);
}

void AExorcist::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PC = Cast<AExorcistController>(GetController());

	if (!PC)
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void AExorcist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StatusAttribute->IsDead())
		return;

	FollowingCursor(DeltaTime);

	StatusAttribute->SetSpeed(GetVelocity().Length());
}

void AExorcist::Move(const FInputActionValue& Value)
{
	if (StatusAttribute->GetDeBuffs().HasTag(Tags::Block) ||		// 강력 CC 시 이동 불가
		StatusAttribute->GetDeBuffs().HasTag(Tags::Debuff_Root))	// 속박 시 이동 불가
		return;

	if (StatusAttribute->IsDead())
		return;

	State.RemoveTag(Tags::Exorcist_Idle);
	State.AddTag(Tags::Exorcist_Moving);

	FVector2D MovementVector = Value.Get<FVector2D>();

	float speed = StatusAttribute->GetFinalMaxSpeed();

	if (StatusAttribute->GetDeBuffs().HasTag(Tags::Debuff_Slow))
	{
		speed *= StatusAttribute->GetActiveEffect().Find(Tags::Debuff_Slow)->Value / 100.0f;
	}

	if (AnimInstance->IsAnyMontagePlaying())
	{
		speed *= 0.75f;
		GetCharacterMovement()->ForceReplicationUpdate();
	}

	GetCharacterMovement()->MaxWalkSpeed = speed;

	if (Controller != nullptr)
	{
		// 컨트롤러나 카메라가 바라보는 회전값 중 수평(Yaw) 방향만 추출
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		// 롤 시점 기준으로 화면 위쪽(정북향) 벡터 계산
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// 롤 시점 기준으로 화면 오른쪽(정동향) 벡터 계산
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 계산된 절대 방향 벡터에 키보드 입력 가중치만큼 이동 명령 전달
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


void AExorcist::Casting(FGameplayTag Input)
{
	if (StatusAttribute->IsDead())
		return;

	SkillManager->ProcessSkillCast(Input, bShowSkillRange);
}

void AExorcist::ReleaseInput(FGameplayTag Input)
{
	if (StatusAttribute->IsDead())
		return;

	SkillManager->ProcessSkillRelease(Input);
}

void AExorcist::FollowingCursor(float DeltaTime)
{
	FVector TargetLocation = PC->GetIndicator()->GetActorLocation();
	FVector StartLocation = GetActorLocation();
	TargetLocation.Z = StartLocation.Z;
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 15.0f);

	SetActorRotation(NewRotation);
}


void AExorcist::BeginCast(FGameplayTag Input)
{
	SkillManager->BeginCast(Input);
}

void AExorcist::EndCast(FGameplayTag Input)
{
	SkillManager->EndCast(Input);
}

void AExorcist::GetMovementAnimData(float& OutSpeed, float& OutDirection, bool& OutIsDead)
{
	FVector Velocity = GetVelocity();

	if (!IsValid(StatusAttribute))
		return;

	OutSpeed = StatusAttribute->GetSpeed();
	OutDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, GetActorRotation());
	OutIsDead = StatusAttribute->IsDead();
}

void AExorcist::ApplyDamage(const FSkillDamageEvent& DmgEvent)
{
	StatusAttribute->ProcessApplyDamage(DmgEvent);
}

void AExorcist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExorcist::Move);
			EnhancedInputComponent->BindActionInstanceLambda(MoveAction, ETriggerEvent::Completed, [this](const FInputActionInstance& I)
			{
				State.RemoveTag(Tags::Exorcist_Moving);
				State.AddTag(Tags::Exorcist_Idle);
			});
		}

		// [수정] 스킬 입력 이벤트 분리 처리
		for (auto Iter : CastActions)
		{
			if (Iter.Value)
			{
				// 1. 키를 누르고 있을 때 (Triggered) -> Casting 함수 내부에서 사거리를 켤지 즉시 시전할지 판단
				EnhancedInputComponent->BindAction(Iter.Value, ETriggerEvent::Started, this, &AExorcist::Casting, Iter.Key);

				// 2. 스킬 키에서 손을 뗐을 때 (Completed) -> 사거리 표시 중이었다면 즉시 스킬 시전!
				EnhancedInputComponent->BindAction(Iter.Value, ETriggerEvent::Completed, this, &AExorcist::ReleaseInput, Iter.Key);
			}
		}

		// Shift 키 입력 설정
		EnhancedInputComponent->BindActionInstanceLambda(ShowSkillRangeAction, ETriggerEvent::Started, [this](const FInputActionInstance& I)
		{
			bShowSkillRange = true;
		});
		EnhancedInputComponent->BindActionInstanceLambda(ShowSkillRangeAction, ETriggerEvent::Completed, [this](const FInputActionInstance& I)
		{
			if (!SkillManager->GetCurrentAimingInput().IsValid())
				bShowSkillRange = false;
		});

		if (SkillManager)
			EnhancedInputComponent->BindAction(ReleaseSkillAction, ETriggerEvent::Started, this, &AExorcist::ReleaseInput, SkillManager->GetCurrentAimingInput());
	}
}

void AExorcist::DebugApplyChanges()
{
	StatusAttribute->SetMaxSpeed(GetCharacterMovement()->MaxWalkSpeed);
	StatusAttribute->SetHP(StatusAttribute->GetHP() - 10.f);
	StatusAttribute->SetMP(StatusAttribute->GetMP() + 10.f);

	UE_LOG(LogTemp, Warning, TEXT("Registered Objects Count : %d"), GetOBJPool->GetRegisteredActorCount());
}
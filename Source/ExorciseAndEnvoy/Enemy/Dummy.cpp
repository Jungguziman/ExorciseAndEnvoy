// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Dummy.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Components/Widget.h"
#include "Components/WidgetComponent.h"

#include "StatusAttribute.h"
#include "EnemyStatusWidget.h"
#include "AnimInstanceBase_Enemy.h"


// Sets default values
ADummy::ADummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCapsuleHalfHeight(100.f);
	CapsuleComponent->SetCapsuleRadius(35.f);

	RootComponent = CapsuleComponent;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->bReceivesDecals = false;
	SkeletalMesh->SetupAttachment(RootComponent);

	StatusAttribute = CreateDefaultSubobject<UStatusAttribute>(TEXT("StatusAttribute"));

	StatusAttribute->SetDefence(5.f);
	StatusAttribute->SetHPRegen(0.f);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidgetComponent"));

	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
	GetOBJPool->RegisterActor(this);
	WidgetComponent->SetWidget(StatusWidget);

	if (SkeletalMesh)
		AnimInstance = Cast<UAnimInstanceBase_Enemy>(SkeletalMesh->GetAnimInstance());
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StatusAttribute->GetHP() <= 0.f && !IsDead)
	{
		IsDead = true;
		AnimInstance->Montage_Play(DeathMontage);

		GetOBJPool->UnregisterActor(this);
	}
	else if (IsDead && !AnimInstance->IsAnyMontagePlaying())
	{
		Destroy();
	}

}

void ADummy::ApplyDamage(const FSkillDamageEvent& DmgEvent)
{
	UE_LOG(LogTemp, Log, TEXT("[Dummy] DMG : %f"), DmgEvent.FinalDamage);

	StatusAttribute->ProcessApplyDamage(DmgEvent);
	StatusWidget->UpdateHPBar(StatusAttribute->GetHP(), StatusAttribute->GetFinalMaxHP());
}

void ADummy::BeginCast(FGameplayTag Input)
{
	
}

void ADummy::EndCast(FGameplayTag Input)
{
}

void ADummy::GetMovementAnimData(float& OutSpeed, float& OutDirection, bool& OutIsDead)
{
	FVector Velocity = GetVelocity();

	OutSpeed = StatusAttribute->GetSpeed();
	OutDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, GetActorRotation());
	OutIsDead = StatusAttribute->GetHP() <= 0.f ? true : false;
}

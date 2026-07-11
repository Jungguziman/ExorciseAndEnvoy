// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Dummy.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


#include "StatusAttribute.h"


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

}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
	GetOBJPool->RegisterActor(this);
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StatusAttribute->GetHP() <= 0.f)
	{
		GetOBJPool->UnregisterActor(this);
		Destroy();
	}
}

void ADummy::ApplyDamage(const FSkillDamageEvent& DmgEvent, UStatusAttribute* AttackerStatus)
{
	StatusAttribute->ProcessApplyDamage(DmgEvent, AttackerStatus);
}

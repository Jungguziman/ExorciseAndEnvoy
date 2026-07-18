// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "TimerManager.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "Damageable.h"
#include "Exorcist.h"
#include "StatusAttribute.h"

#include "SkillProjectile.h"


// Sets default values for this component's properties
USkillBase::USkillBase()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USkillBase::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


// Called every frame
void USkillBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void USkillBase::CastSkill(FVector Location)
{
	if (SkillForm.MatchesTag(Tags::Skill_Form_Area) && SkillFXAsset)
	{
		UNiagaraComponent* SpawnedFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			SkillFXAsset,
			Location,
			FRotator::ZeroRotator,
			FVector(1.f, 1.f, 1.f),
			true
		);

		SpawnedFX->SetFloatParameter(TEXT("SkillBound"), Bound.X);
	}
	else if (SkillForm.MatchesTag(Tags::Skill_Form_Targeting) && SkillProjectile_Class)
	{
		FActorSpawnParameters Params;
		Params.Owner = OwnerCharacter;
		Params.Instigator = OwnerCharacter;

		ASkillProjectile* Projectile = GetWorld()->SpawnActor<ASkillProjectile>(
			SkillProjectile_Class,
			OwnerCharacter->GetActorLocation(),
			OwnerCharacter->GetActorRotation(),
			Params
		);
	}

	auto Status = Cast<IDamageable>(OwnerCharacter)->GetStatusAttribute();
	Status->SetMP(Status->GetMP() - MPCost);
}


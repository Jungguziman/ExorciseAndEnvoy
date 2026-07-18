// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/CircleShapeSkill.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

#include "Damageable.h"

#include "Exorcist.h"
#include "StatusAttribute.h"
#include "ObjectPoolSubsystem.h"

UCircleShapeSkill::UCircleShapeSkill()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> DecalMaterialRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Texture/UI/Skill/MI_SkillRange_Circle360.MI_SkillRange_Circle360'"));
	if (DecalMaterialRef.Succeeded())
	{
		SkillRangeDecalMaterial = DecalMaterialRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/NiagaraExamples/FX_Explosions/NS_Dirt_Explosion_Medium.NS_Dirt_Explosion_Medium'"));

	if (NiagaraSystemAsset.Succeeded())
	{
		SkillFXAsset = NiagaraSystemAsset.Object;
	}

	Bound = FVector2D(300.0f, 300.0f);

	CoolTime = 3.5f;
	PreCastDelay = .3f;
	PostCastDelay = 1.f;

	Damage = 50.f;
	MPCost = 20.f;

	SkillForm = Tags::Skill_Form_Circle;
}

void UCircleShapeSkill::BeginPlay()
{
	Super::BeginPlay();
}

void UCircleShapeSkill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCircleShapeSkill::CastSkill(FVector Location)
{
	Super::CastSkill(Location);
	
	TArray<AActor*> ActorArr;
	GetOBJPool->GetActorsInCircle(FVector2D(Location), Bound.X, ActorArr);

	for (AActor* Target : ActorArr)
	{
		IDamageable* Damageable = Cast<IDamageable>(Target);
		if (!Damageable)
			continue;

		IDamageable* Caster = Cast<IDamageable>(OwnerCharacter);
		if (!Caster)
			continue;

		FSkillDamageEvent DmgEvent;
		DmgEvent.FinalDamage = Damage;
		DmgEvent.Debuffs = SkillEffects;
		DmgEvent.PenetrationRate = Caster->GetStatusAttribute()->GetPenetrationRate();

		Damageable->ApplyDamage(DmgEvent);
	}

}

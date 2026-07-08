// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/CircleShapeSkill.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

UCircleShapeSkill::UCircleShapeSkill()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> DecalMaterialRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Texture/UI/Skill/MI_SkillRange_Circle360.MI_SkillRange_Circle360'"));
	if (DecalMaterialRef.Succeeded())
	{
		SkillRangeDecalMaterial = DecalMaterialRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/Exorcists/NS_CircleSkill.NS_CircleSkill'"));

	if (NiagaraSystemAsset.Succeeded())
	{
		SkillFXAsset = NiagaraSystemAsset.Object;
	}

	Bound = FVector2D(300.0f, 300.0f);
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
}

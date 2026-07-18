// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "CircleShapeSkill.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class EXORCISEANDENVOY_API UCircleShapeSkill : public USkillBase
{
	GENERATED_BODY()
	
public:
	UCircleShapeSkill();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	virtual void CastSkill(FVector Location) override;

};

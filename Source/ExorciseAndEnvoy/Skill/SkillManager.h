// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillManager.generated.h"

class USkillBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXORCISEANDENVOY_API USkillManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void TryCast(FGameplayTag Input);

	TObjectPtr<USkillBase> GetSkill(FGameplayTag Key) { return Skill_Instances[Key]; }

	void SetSkillCastLocation(FVector Location) { NextSkillCastLocation = Location; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	TMap<FGameplayTag, TSubclassOf<USkillBase>> Skill_Classes;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<USkillBase>> Skill_Instances;
	
	UPROPERTY()
	FVector NextSkillCastLocation = FVector::ZeroVector;

};

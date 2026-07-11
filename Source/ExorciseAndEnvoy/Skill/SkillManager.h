// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillManager.generated.h"

class AExorcist;
class USkillBase;
class UAnimInstance;

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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ProcessSkillCast(FGameplayTag Input, bool bShiftPressed);
	void ProcessSkillRelease(FGameplayTag Input);

	void TryCast(FGameplayTag Input);

	// 선/후딜 제어용 내부 내부 생명주기 제어 함수
	void BeginCast(FGameplayTag Input);
	void EndCast(FGameplayTag Input);
	void ExecuteAttack();

	// Getter API
	USkillBase* GetSkill(FGameplayTag Input);
	bool IsSkillInCoolTime(FGameplayTag Input);
	FORCEINLINE void SetSkillCastLocation(FVector Location) { NextSkillCastLocation = Location; }

	FGameplayTag GetCurrentAimingInput() { return CurrentAimingInput; }

protected:
	UPROPERTY(EditAnywhere, Category = "Skill | Config")
	TMap<FGameplayTag, TSubclassOf<USkillBase>> Skill_Classes;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<USkillBase>> Skill_Instances;

	UPROPERTY()
	TObjectPtr<AExorcist> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<UAnimInstance> OwnerAnimInstance;

private:
	FGameplayTag CurrentInput = FGameplayTag::EmptyTag;
	FGameplayTag CurrentAimingInput = FGameplayTag::EmptyTag;

	UPROPERTY()
	TMap<FGameplayTag, bool> IsCastings;

	FVector NextSkillCastLocation;

};

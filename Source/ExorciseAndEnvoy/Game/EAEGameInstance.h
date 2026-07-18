// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsClasses.h"
#include "EAEGameInstance.generated.h"

class UGameplayTagsManager;

namespace Tags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Exorcist_Idle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Exorcist_Moving);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Exorcist_Casting);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Exorcist_Dead);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Idle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Following);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Attacking);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Dead);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Buff);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Buff_Gaurd);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Buff_Heist);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Buff_Shield);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Buff_Tenacity);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Fear);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Knockback);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Root);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Silence);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Slow);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Stun);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Taunt);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Block);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Burn);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Dark);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Electric);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Freeze);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Light);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Plauge);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Rock);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stack_Wind);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Burn);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Dark);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Electric);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Freeze);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Light);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Plauge);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Rock);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Type_Wind);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_None);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_A);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Q);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_E);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_R);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Single);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Projectile);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Arrow);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Circle);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Sector);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Ultimate);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Targeting);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Form_Area);

}

USTRUCT(BlueprintType)
struct FValueAttribute
{
	GENERATED_BODY()

	FValueAttribute() : Base(1.f), Bonus(0.0f), Ratio(100.0f) {}

	FValueAttribute(float BaseValue) : Base(BaseValue), Bonus(0.0f), Ratio(100.0f) {}

	FValueAttribute(float BaseValue, float BonusValue, float FinalRatio) : Base(BaseValue), Bonus(BonusValue), Ratio(FinalRatio) {}

public:
	UPROPERTY(EditAnywhere, Category = "Stat")
	float Base;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float Bonus;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float Ratio;

	FORCEINLINE float GetFinalValue() const { return (Base + Bonus) * (Ratio / 100.0f); }
	FORCEINLINE void SetValue(float Value) { Base = Value; }
	FORCEINLINE void AddBonusValue(float BonusValue) { Bonus += BonusValue; }
	FORCEINLINE void SetBonusValue(float BonusValue) { Bonus = BonusValue; }
	FORCEINLINE void AddFinalRatio(float FinalRatio) { Ratio += FinalRatio; }
	FORCEINLINE void SetFinalRatio(float FinalRatio = 100.0f) { Ratio = FinalRatio; }
};

USTRUCT(BlueprintType)
struct FActiveEffect
{
	GENERATED_BODY()

	FTimerHandle TimerHandle;
	FGameplayTag EffectTag;
	FGameplayTag BlockTag;

	float Duration;
	float Value;

	FActiveEffect() :
		Duration(0.0f), Value(100.0f) {
	}
	FActiveEffect(FGameplayTag EffectTag, float Duration, float Value) :
		EffectTag(EffectTag), Duration(Duration), Value(Value) {
	}
	FActiveEffect(FGameplayTag EffectTag, FGameplayTag BlockTag, float Duration, float Value) :
		EffectTag(EffectTag), BlockTag(BlockTag), Duration(Duration), Value(Value) {
	}

};

USTRUCT(BlueprintType)
struct FSkillDamageEvent
{
	GENERATED_BODY()

	FSkillDamageEvent() {}
	FSkillDamageEvent(float FinalDamage) : FinalDamage(FinalDamage) {}
	FSkillDamageEvent(float FinalDamage, float PenetrationRate) : FinalDamage(FinalDamage), PenetrationRate(PenetrationRate) {}

	FSkillDamageEvent(float FinalDamage, float PenetrationRate, std::initializer_list<FActiveEffect> Effects) : FinalDamage(FinalDamage)
	{
		for (FActiveEffect Effect : Effects)
			Debuffs.Add(Effect);
	}

	UPROPERTY()
	float FinalDamage = 0.f;

	UPROPERTY()
	float PenetrationRate = 0.f;

	UPROPERTY()
	TArray<FActiveEffect> Debuffs;
};


UCLASS()
class EXORCISEANDENVOY_API UEAEGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEAEGameInstance();

		
};

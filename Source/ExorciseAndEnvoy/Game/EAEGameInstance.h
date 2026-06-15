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
	inline static FGameplayTag Exorcist_Idle;
	inline static FGameplayTag Exorcist_Moving;
	inline static FGameplayTag Exorcist_Casting;
	inline static FGameplayTag Exorcist_Dead;

	inline static FGameplayTag Enemy_Idle;
	inline static FGameplayTag Enemy_Following;
	inline static FGameplayTag Enemy_Attacking;
	inline static FGameplayTag Enemy_Dead;

	inline static FGameplayTag Buff_Gaurd;
	inline static FGameplayTag Buff_Heist;
	inline static FGameplayTag Buff_Shield;
	inline static FGameplayTag Buff_Tenacity;

	inline static FGameplayTag DeBuff_Fear;
	inline static FGameplayTag DeBuff_Knockback;
	inline static FGameplayTag DeBuff_Silence;
	inline static FGameplayTag DeBuff_Slow;
	inline static FGameplayTag DeBuff_Stun;
	inline static FGameplayTag DeBuff_Taunt;

	inline static FGameplayTag SkillType_Burn;
	inline static FGameplayTag SkillType_Dark;
	inline static FGameplayTag SkillType_Electric;
	inline static FGameplayTag SkillType_Freeze;
	inline static FGameplayTag SkillType_Light;
	inline static FGameplayTag SkillType_Plauge;
	inline static FGameplayTag SkillType_Rock;
	inline static FGameplayTag SkillType_Wind;

	inline static FGameplayTag Stack_Burn;
	inline static FGameplayTag Stack_Dark;
	inline static FGameplayTag Stack_Electric;
	inline static FGameplayTag Stack_Freeze;
	inline static FGameplayTag Stack_Light;
	inline static FGameplayTag Stack_Plauge;
	inline static FGameplayTag Stack_Rock;
	inline static FGameplayTag Stack_Wind;

	inline static void InitializeNativeTags()
	{
		UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

		Exorcist_Idle		= Manager.AddNativeGameplayTag(TEXT("State.Exorcist.Idle"));
		Exorcist_Moving		= Manager.AddNativeGameplayTag(TEXT("State.Exorcist.Moving"));
		Exorcist_Casting	= Manager.AddNativeGameplayTag(TEXT("State.Exorcist.Casting"));
		Exorcist_Dead		= Manager.AddNativeGameplayTag(TEXT("State.Exorcist.Dead"));

		Enemy_Idle			= Manager.AddNativeGameplayTag(TEXT("State.Enemy.Idle"));
		Enemy_Following		= Manager.AddNativeGameplayTag(TEXT("State.Enemy.Following"));
		Enemy_Attacking		= Manager.AddNativeGameplayTag(TEXT("State.Enemy.Attacking"));
		Enemy_Dead			= Manager.AddNativeGameplayTag(TEXT("State.Enemy.Dead"));

		Buff_Gaurd			= Manager.AddNativeGameplayTag(TEXT("State.Buff.Gaurd"));
		Buff_Heist			= Manager.AddNativeGameplayTag(TEXT("State.Buff.Heist"));
		Buff_Shield			= Manager.AddNativeGameplayTag(TEXT("State.Buff.Shield"));
		Buff_Tenacity		= Manager.AddNativeGameplayTag(TEXT("State.Buff.Tenacity"));

		DeBuff_Fear			= Manager.AddNativeGameplayTag(TEXT("State.Debuff.Fear"));
		DeBuff_Knockback	= Manager.AddNativeGameplayTag(TEXT("State.Debuff.Knockback"));
		DeBuff_Silence		= Manager.AddNativeGameplayTag(TEXT("State.Debuff.Silence"));
		DeBuff_Slow			= Manager.AddNativeGameplayTag(TEXT("State.Debuff.Slow"));
		DeBuff_Stun			= Manager.AddNativeGameplayTag(TEXT("State.Debuff.Stun"));
		DeBuff_Taunt		= Manager.AddNativeGameplayTag(TEXT("State.Debuff.Taunt"));

		SkillType_Burn		= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Burn"));
		SkillType_Dark		= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Dark"));
		SkillType_Electric	= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Electric"));
		SkillType_Freeze	= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Freeze"));
		SkillType_Light		= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Light"));
		SkillType_Plauge	= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Plague"));
		SkillType_Rock		= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Rock"));
		SkillType_Wind		= Manager.AddNativeGameplayTag(TEXT("State.SkillType.Wind"));

		Stack_Burn			= Manager.AddNativeGameplayTag(TEXT("State.Stack.Burn"));
		Stack_Dark			= Manager.AddNativeGameplayTag(TEXT("State.Stack.Dark"));
		Stack_Electric		= Manager.AddNativeGameplayTag(TEXT("State.Stack.Electric"));
		Stack_Freeze		= Manager.AddNativeGameplayTag(TEXT("State.Stack.Freeze"));
		Stack_Light			= Manager.AddNativeGameplayTag(TEXT("State.Stack.Light"));
		Stack_Plauge		= Manager.AddNativeGameplayTag(TEXT("State.Stack.Plague"));
		Stack_Rock			= Manager.AddNativeGameplayTag(TEXT("State.Stack.Rock"));
		Stack_Wind			= Manager.AddNativeGameplayTag(TEXT("State.Stack.Wind"));
	}
}

/**
 * 
 */
UCLASS()
class EXORCISEANDENVOY_API UEAEGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEAEGameInstance();

	virtual void Init() override
	{
		Super::Init();

		Tags::InitializeNativeTags();
	}

};

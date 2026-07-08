// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EAEGameInstance.h"

namespace Tags
{
	UE_DEFINE_GAMEPLAY_TAG(Exorcist_Idle, "State.Exorcist.Idle");
	UE_DEFINE_GAMEPLAY_TAG(Exorcist_Moving, "State.Exorcist.Moving");
	UE_DEFINE_GAMEPLAY_TAG(Exorcist_Casting, "State.Exorcist.Casting");
	UE_DEFINE_GAMEPLAY_TAG(Exorcist_Dead, "State.Exorcist.Dead");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Idle, "State.Enemy.Idle");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Following, "State.Enemy.Following");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Attacking, "State.Enemy.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Dead, "State.Enemy.Dead");

	UE_DEFINE_GAMEPLAY_TAG(Buff, "State.Buff");
	UE_DEFINE_GAMEPLAY_TAG(Buff_Gaurd, "State.Buff.Gaurd");
	UE_DEFINE_GAMEPLAY_TAG(Buff_Heist, "State.Buff.Heist");
	UE_DEFINE_GAMEPLAY_TAG(Buff_Shield, "State.Buff.Shield");
	UE_DEFINE_GAMEPLAY_TAG(Buff_Tenacity, "State.Buff.Tenacity");

	UE_DEFINE_GAMEPLAY_TAG(Debuff, "State.Debuff");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Fear, "State.Debuff.Fear");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Knockback, "State.Debuff.Knockback");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Root, "State.Debuff.Root");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Silence, "State.Debuff.Silence");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Slow, "State.Debuff.Slow");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Stun, "State.Debuff.Stun");
	UE_DEFINE_GAMEPLAY_TAG(Debuff_Taunt, "State.Debuff.Taunt");

	UE_DEFINE_GAMEPLAY_TAG(Block, "State.Block");
	
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Burn, "State.SkillType.Burn");
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Dark, "State.SkillType.Dark");
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Electric, "State.SkillType.Electric");
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Freeze, "State.SkillType.Freeze");
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Light, "State.SkillType.Light");
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Plauge, "State.SkillType.Plague");
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Rock, "State.SkillType.Rock");
	UE_DEFINE_GAMEPLAY_TAG(SkillType_Wind, "State.SkillType.Wind");

	UE_DEFINE_GAMEPLAY_TAG(Stack_Burn, "State.Stack.Burn");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Dark, "State.Stack.Dark");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Electric, "State.Stack.Electric");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Freeze, "State.Stack.Freeze");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Light, "State.Stack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Plauge, "State.Stack.Plague");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Rock, "State.Stack.Rock");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Wind, "State.Stack.Wind");

	UE_DEFINE_GAMEPLAY_TAG(Input_None, "Skill.Input.None");
	UE_DEFINE_GAMEPLAY_TAG(Input_A, "Skill.Input.A");
	UE_DEFINE_GAMEPLAY_TAG(Input_Q, "Skill.Input.Q");
	UE_DEFINE_GAMEPLAY_TAG(Input_E, "Skill.Input.E");
	UE_DEFINE_GAMEPLAY_TAG(Input_R, "Skill.Input.R");
}

UEAEGameInstance::UEAEGameInstance()
{
}

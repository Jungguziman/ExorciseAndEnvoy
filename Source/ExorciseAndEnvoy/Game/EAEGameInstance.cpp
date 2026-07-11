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


	UE_DEFINE_GAMEPLAY_TAG(Stack_Burn, "State.Stack.Burn");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Dark, "State.Stack.Dark");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Electric, "State.Stack.Electric");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Freeze, "State.Stack.Freeze");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Light, "State.Stack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Plauge, "State.Stack.Plague");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Rock, "State.Stack.Rock");
	UE_DEFINE_GAMEPLAY_TAG(Stack_Wind, "State.Stack.Wind");
	
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Burn, "Skill.Type.Burn");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Dark, "Skill.Type.Dark");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Electric, "Skill.Type.Electric");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Freeze, "Skill.Type.Freeze");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Light, "Skill.Type.Light");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Plauge, "Skill.Type.Plague");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Rock, "Skill.Type.Rock");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Type_Wind, "Skill.Type.Wind");

	UE_DEFINE_GAMEPLAY_TAG(Input_None, "Skill.Input.None");
	UE_DEFINE_GAMEPLAY_TAG(Input_A, "Skill.Input.A");
	UE_DEFINE_GAMEPLAY_TAG(Input_Q, "Skill.Input.Q");
	UE_DEFINE_GAMEPLAY_TAG(Input_E, "Skill.Input.E");
	UE_DEFINE_GAMEPLAY_TAG(Input_R, "Skill.Input.R");

	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Single, "Skill.Form.Targeting.Single");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Projectile, "Skill.Form.Targeting.Projectile");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Arrow, "Skill.Form.Area.Arrow");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Circle, "Skill.Form.Area.Circle");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Sector, "Skill.Form.Area.Sector");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Ultimate, "Skill.Form.Area.Ultimate");

	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Targeting, "Skill.Form.Targeting");
	UE_DEFINE_GAMEPLAY_TAG(Skill_Form_Area, "Skill.Form.Area");
}

UEAEGameInstance::UEAEGameInstance()
{
}

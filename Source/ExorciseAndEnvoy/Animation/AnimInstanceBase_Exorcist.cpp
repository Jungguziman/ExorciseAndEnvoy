// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase_Exorcist.h"

void UAnimInstanceBase_Exorcist::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	IAnimCallback* CallbackTarget = Cast<IAnimCallback>(GetOwningActor());

	if (CallbackTarget)
		CallbackTarget->GetMovementAnimData(Speed, Direction, IsDead);
}

void UAnimInstanceBase_Exorcist::AnimNotify_BeginA()
{
	BeginAnimCallBack(Tags::Input_A);
}

void UAnimInstanceBase_Exorcist::AnimNotify_EndA()
{
	EndAnimCallBack(Tags::Input_A);
}

void UAnimInstanceBase_Exorcist::AnimNotify_BeginQ()
{
	BeginAnimCallBack(Tags::Input_Q);
}

void UAnimInstanceBase_Exorcist::AnimNotify_EndQ()
{
	EndAnimCallBack(Tags::Input_Q);
}

void UAnimInstanceBase_Exorcist::AnimNotify_BeginE()
{
	BeginAnimCallBack(Tags::Input_E);
}

void UAnimInstanceBase_Exorcist::AnimNotify_EndE()
{
	EndAnimCallBack(Tags::Input_E);
}

void UAnimInstanceBase_Exorcist::AnimNotify_BeginR()
{
	BeginAnimCallBack(Tags::Input_R);
}

void UAnimInstanceBase_Exorcist::AnimNotify_EndR()
{
	EndAnimCallBack(Tags::Input_R);
}

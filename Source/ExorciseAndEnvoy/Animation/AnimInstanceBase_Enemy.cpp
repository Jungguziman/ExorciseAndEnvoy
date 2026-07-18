// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase_Enemy.h"
#include "AnimCallback.h"

void UAnimInstanceBase_Enemy::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	IAnimCallback* CallbackTarget = Cast<IAnimCallback>(GetOwningActor());

	if (CallbackTarget)
		CallbackTarget->GetMovementAnimData(Speed, Direction, IsDead);
}

void UAnimInstanceBase_Enemy::AnimNotify_Death()
{
	UE_LOG(LogTemp, Log, TEXT("ANIM NOTIFY DEATH"));

	if (GetOwningActor())
		GetOwningActor()->Destroy();
	
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class EXORCISEANDENVOY_API UAnimInstanceBase_Enemy : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void AnimNotify_Death();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	float Direction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	bool IsDead = false;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimCallback.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimCallback : public UInterface
{
	GENERATED_BODY()
};

class EXORCISEANDENVOY_API IAnimCallback
{
	GENERATED_BODY()

public:
	virtual void BeginCast(FGameplayTag Input) = 0;
	virtual void EndCast(FGameplayTag Input) = 0;

	virtual void GetMovementAnimData(float& OutSpeed, float& OutDirection, bool& OutIsDead) = 0;

};

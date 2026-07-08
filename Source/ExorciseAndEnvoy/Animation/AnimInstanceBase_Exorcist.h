// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "AnimCallback.h"

#include "AnimInstanceBase_Exorcist.generated.h"

class UAnimMontage;

UCLASS()
class EXORCISEANDENVOY_API UAnimInstanceBase_Exorcist : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	void BeginAnimCallBack(FGameplayTag Input)
	{
		IAnimCallback* CallbackTarget = Cast<IAnimCallback>(GetOwningActor());

		if (CallbackTarget) CallbackTarget->BeginCast(Input);
	}

	void EndAnimCallBack(FGameplayTag Input)
	{
		IAnimCallback* CallbackTarget = Cast<IAnimCallback>(GetOwningActor());

		if (CallbackTarget) CallbackTarget->EndCast(Input);
	}

protected:
	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_BeginA();

	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_EndA();

	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_BeginQ();

	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_EndQ();

	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_BeginE();

	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_EndE();

	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_BeginR();

	UFUNCTION(BlueprintCallable, Category = "Animation | Callback")
	void AnimNotify_EndR();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	float Speed = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	float Direction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
	bool IsDead = false;
};

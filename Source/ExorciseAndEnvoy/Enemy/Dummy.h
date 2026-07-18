// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimCallback.h"
#include "Damageable.h"

#include "Dummy.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UStatusAttribute;
class UWidgetComponent;
class UEnemyStatusWidget;
class UAnimInstanceBase_Enemy;

UCLASS()
class EXORCISEANDENVOY_API ADummy : public AActor, public IAnimCallback, public IDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ApplyDamage(const FSkillDamageEvent& DmgEvent);
	virtual UStatusAttribute* GetStatusAttribute() override { return StatusAttribute; }

public:
	virtual void BeginCast(FGameplayTag Input) override;
	virtual void EndCast(FGameplayTag Input) override;

	virtual void GetMovementAnimData(float& OutSpeed, float& OutDirection, bool& OutIsDead) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UEnemyStatusWidget> StatusWidget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	TObjectPtr<UStatusAttribute> StatusAttribute;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimInstanceBase_Enemy> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathMontage;


	UPROPERTY()
	bool IsDead = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damageable.h"

#include "Dummy.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UStatusAttribute;


UCLASS()
class EXORCISEANDENVOY_API ADummy : public AActor, public IDamageable
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

	virtual void ApplyDamage(const FSkillDamageEvent& DmgEvent, UStatusAttribute* AttackerStatus);
	virtual UStatusAttribute* GetStatusAttribute() override { return StatusAttribute; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	TObjectPtr<UStatusAttribute> StatusAttribute;

};

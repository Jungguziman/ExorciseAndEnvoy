// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class IDamageable;

UCLASS()
class EXORCISEANDENVOY_API ASkillProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	void SetDamageEvent(FSkillDamageEvent Value) { DmgEvent = Value; }
	void SetTarget(AActor* Enemy);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collider")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Movement")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UPROPERTY()
	FSkillDamageEvent DmgEvent;


	UPROPERTY()
	TObjectPtr<AActor> TargetActor;

	IDamageable* Target;
};

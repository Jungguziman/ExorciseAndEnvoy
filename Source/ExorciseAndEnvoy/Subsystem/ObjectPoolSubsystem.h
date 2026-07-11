// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class EXORCISEANDENVOY_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void RegisterActor(AActor* NewActor) { RegisteredActors.Add(NewActor); }
	void UnregisterActor(AActor* ExitActor) { RegisteredActors.Remove(ExitActor); }
	int32 GetRegisteredActorCount() { return RegisteredActors.Num(); }

public:
	void GetActorsInCircle(const FVector2D& CenterPos, const float& Radius, TArray<AActor*>& OutActors);
	void GetActorsInSector(const FVector2D& StartPos, const FVector& Direction, const float& Radius, const float& EulerAngle, TArray<AActor*> OutActors);
	void GetActorsInRect(const FVector2D& StartPos, const FVector& Direction, const FVector2D& Extent, TArray<AActor*> OutActors);

protected:
	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> RegisteredActors;

};

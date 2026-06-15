// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SkillBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXORCISEANDENVOY_API USkillBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Cast")
	float PreCastDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Cast")
	float PostCastDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Cast")
	float CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Power")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Tags")
	FGameplayTagContainer SkillTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Tags")
	FGameplayTagContainer SkillDebuffs;

};

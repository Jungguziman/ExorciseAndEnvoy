// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SkillBase.generated.h"

class UMaterialInterface;
class UNiagaraSystem;

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

	virtual void CastSkill(FVector Location);

	FVector2D GetSkillBound() { return Bound; }

	TObjectPtr<UMaterialInterface> GetDecalMaterial() { return SkillRangeDecalMaterial; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill | Visual")
	TObjectPtr<UNiagaraSystem> SkillFXAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill | Visual")
	TObjectPtr<UMaterialInterface> SkillRangeDecalMaterial;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float PreCastDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float PostCastDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float MPCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float HPCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float SpecialCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	FVector2D Bound = FVector2D(100.f, 100.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Tags")
	FGameplayTagContainer SkillTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Tags")
	FGameplayTagContainer SkillDebuffs;

};

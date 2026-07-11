// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SkillBase.generated.h"

class UMaterialInterface;
class UNiagaraSystem;
class ASkillProjectile;
class USkillDamageType;
class AExorcist;

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

public:
	virtual void CastSkill(FVector Location);

public:
	FVector2D GetSkillBound() { return Bound; }
	UMaterialInterface* GetDecalMaterial() { return SkillRangeDecalMaterial; }

	FORCEINLINE float GetMPCost() const { return MPCost; }
	FORCEINLINE float GetHPCost() const { return HPCost; }
	FORCEINLINE float GetSpecialCost() const { return SpecialCost; }

	FORCEINLINE float GetPreCastDelay() const { return PreCastDelay; }
	FORCEINLINE void SetPreCastDelay(float Value) { PreCastDelay = Value; }

	FORCEINLINE float GetPostCastDelay() const { return PostCastDelay; }
	FORCEINLINE void SetPostCastDelay(float Value) { PostCastDelay = Value; }

	FORCEINLINE float GetCoolTime() const { return CoolTime; }
	FORCEINLINE void SetCoolTime(float Value) { CoolTime = Value; }

	FORCEINLINE float GetCurrentCoolDown() const { return CoolDownTimer; }
	FORCEINLINE void SetCurrentCoolDown(float Value) { CoolDownTimer = Value; }

	FORCEINLINE bool IsInCoolDown() const { return CoolDownTimer > 0.0f; }
	FORCEINLINE void StartCoolDown() { CoolDownTimer = CoolTime; }

	FORCEINLINE bool IsPreCasting() const { return CoolDownTimer >= CoolTime - PreCastDelay; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill | Visual")
	TObjectPtr<UNiagaraSystem> SkillFXAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill | Visual")
	TObjectPtr<UMaterialInterface> SkillRangeDecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill | Projectile")
	TSubclassOf<ASkillProjectile> SkillProjectile_Class;

	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float PreCastDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float PostCastDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float CoolDownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Attribute")
	float CoolTime;

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
	FGameplayTag SkillForm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill Info | Tags")
	TArray<FActiveEffect> SkillEffects;

};

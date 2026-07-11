// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "StatusAttribute.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXORCISEANDENVOY_API UStatusAttribute : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusAttribute();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void ProcessApplyDamage(const FSkillDamageEvent& DmgEvent, UStatusAttribute* AttackerStatus);

	UFUNCTION(BlueprintCallable, Category = "Status Effect")
	void ApplyActiveEffect(FGameplayTag EffectTag, float Duration, float Value = 100.0f);
	UFUNCTION(BlueprintCallable, Category = "Status Effect")
	void RemoveActiveEffect(FGameplayTag EffectTag);

	TMap<FGameplayTag, FActiveEffect> GetActiveEffect() { return ActiveEffects; }

	FORCEINLINE FGameplayTagContainer GetBuffs() { return Buffs; }
	FORCEINLINE FGameplayTagContainer GetDeBuffs() { return Debuffs; }

public:
	FORCEINLINE int32 GetLevel() const { return Level; }
	FORCEINLINE void SetLevel(int32 NewLevel) { Level = FMath::Max(1, NewLevel); }

	FORCEINLINE float GetFinalMaxSpeed() const { return maxSpeed.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetMaxSpeedAttribute() { return maxSpeed; }
	FORCEINLINE void SetMaxSpeed(float NewBase) { maxSpeed.SetValue(NewBase); }
	FORCEINLINE void AddMaxSpeedBonus(float InBonus) { maxSpeed.AddBonusValue(InBonus); }
	FORCEINLINE void AddMaxSpeedRatio(float InRatio) { maxSpeed.AddFinalRatio(InRatio); }

	FORCEINLINE float GetFinalDefence() const { return Defence.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetDefenceAttribute() { return Defence; }
	FORCEINLINE void SetDefence(float NewBase) { Defence.SetValue(NewBase); }
	FORCEINLINE void AddDefenceBonus(float InBonus) { Defence.AddBonusValue(InBonus); }
	FORCEINLINE void AddDefenceRatio(float InRatio) { Defence.AddFinalRatio(InRatio); }

	FORCEINLINE float GetFinalAttackDamage() const { return AttackDamage.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetAttackDamageAttribute() { return AttackDamage; }
	FORCEINLINE void SetAttackDamage(float NewBase) { AttackDamage.SetValue(NewBase); }
	FORCEINLINE void AddAttackDamageBonus(float InBonus) { AttackDamage.AddBonusValue(InBonus); }
	FORCEINLINE void AddAttackDamageRatio(float InRatio) { AttackDamage.AddFinalRatio(InRatio); }

	FORCEINLINE float GetFinalAttackSpeed() const { return AttackSpeed.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetAttackSpeedAttribute() { return AttackSpeed; }
	FORCEINLINE void SetAttackSpeed(float NewBase) { AttackSpeed.SetValue(NewBase); }
	FORCEINLINE void AddAttackSpeedBonus(float InBonus) { AttackSpeed.AddBonusValue(InBonus); }
	FORCEINLINE void AddAttackSpeedRatio(float InRatio) { AttackSpeed.AddFinalRatio(InRatio); }

	FORCEINLINE float GetFinalMaxHP() const { return MaxHP.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetMaxHPAttribute() { return MaxHP; }
	FORCEINLINE void SetMaxHP(float NewBase) { MaxHP.SetValue(NewBase); }
	FORCEINLINE void AddMaxHPBonus(float InBonus) { MaxHP.AddBonusValue(InBonus); }
	FORCEINLINE void AddMaxHPRatio(float InRatio) { MaxHP.AddFinalRatio(InRatio); }

	FORCEINLINE float GetHP() const { return HP; }
	FORCEINLINE void SetHP(float NewHP) { HP = FMath::Clamp(NewHP, 0.0f, GetFinalMaxHP()); }

	FORCEINLINE float GetFinalHPRegen() const { return HPRegen.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetHPRegenAttribute() { return HPRegen; }
	FORCEINLINE void SetHPRegen(float NewBase) { HPRegen.SetValue(NewBase); }
	FORCEINLINE void AddHPRegenBonus(float InBonus) { HPRegen.AddBonusValue(InBonus); }
	FORCEINLINE void AddHPRegenRatio(float InRatio) { HPRegen.AddFinalRatio(InRatio); }


	FORCEINLINE float GetFinalMaxMP() const { return MaxMP.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetMaxMPAttribute() { return MaxMP; }
	FORCEINLINE void SetMaxMP(float NewBase) { MaxMP.SetValue(NewBase); }
	FORCEINLINE void AddMaxMPBonus(float InBonus) { MaxMP.AddBonusValue(InBonus); }
	FORCEINLINE void AddMaxMPRatio(float InRatio) { MaxMP.AddFinalRatio(InRatio); }

	FORCEINLINE float GetMP() const { return MP; }
	FORCEINLINE void SetMP(float NewMP) { MP = FMath::Clamp(NewMP, 0.0f, GetFinalMaxMP()); }

	FORCEINLINE float GetFinalMPRegen() const { return MPRegen.GetFinalValue(); }
	FORCEINLINE FValueAttribute& GetMPRegenAttribute() { return MPRegen; }
	FORCEINLINE void SetMPRegen(float NewBase) { MPRegen.SetValue(NewBase); }
	FORCEINLINE void AddMPRegenBonus(float InBonus) { MPRegen.AddBonusValue(InBonus); }
	FORCEINLINE void AddMPRegenRatio(float InRatio) { MPRegen.AddFinalRatio(InRatio); }


	FORCEINLINE float GetBarrier() const { return barrier; }
	FORCEINLINE void SetBarrier(float NewBarrier) { barrier = FMath::Max(0.0f, NewBarrier); }

	// speed
	FORCEINLINE float GetSpeed() const { return speed; }
	FORCEINLINE void SetSpeed(float NewSpeed) { speed = NewSpeed; }

	// Damage (시전하는 데미지)
	FORCEINLINE float GetDamage() const { return Damage; }
	FORCEINLINE void SetDamage(float NewDamage) { Damage = NewDamage; }

	FORCEINLINE float GetPenetrationRate() const { return PenetrationRate; }
	FORCEINLINE void SetPenetrationRate(float NewPenetration)  { PenetrationRate = NewPenetration; }

protected:
	// Effect
	UPROPERTY()
	TMap<FGameplayTag, FActiveEffect> ActiveEffects;

	UPROPERTY(EditAnywhere, Category = "Effect Tags")
	FGameplayTagContainer Buffs;

	UPROPERTY(EditAnywhere, Category = "Effect Tags")
	FGameplayTagContainer Debuffs;


	// Status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float HP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute HPRegen = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute MaxMP = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MP = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute MPRegen = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute maxSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute Defence = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float barrier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute AttackDamage = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FValueAttribute AttackSpeed = 0.78f; // per seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Damage = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float PenetrationRate = 0.f;

};

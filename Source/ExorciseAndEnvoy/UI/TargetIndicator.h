// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TargetIndicator.generated.h"

class UStaticMeshComponent;
class UDecalComponent;
class UNiagaraComponent;
class USkillBase;

UCLASS()
class EXORCISEANDENVOY_API ATargetIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetIndicator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleCursorLock() { bCursorLock = bCursorLock ? false : true; }

	void ShowSkillRange(USkillBase* Skill);
	void HideSkillRange();

	AActor* GetCurrentTarget() { return CurrentTarget; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> ConeMesh; // ¿ª»ï°¢Çü ´ë¿ë ¿ø»Ô ¸Þ½Ã

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	TObjectPtr<UDecalComponent> TargetDecal;   // ¹Ù´Ú Å¸°Ù ¿ø

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	TObjectPtr<UDecalComponent> SkillRangeDecal;   // ½ºÅ³ ¹Ù´Ú Å¸°Ù ¿ø

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	TObjectPtr<UDecalComponent> SkillRangeDecalComponent;   // ½ºÅ³ ¹Ù´Ú Å¸°Ù ¿ø

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	TObjectPtr<UNiagaraComponent> LineEffect;  // »¡·Áµé¾î°¡´Â Á¡¼± ·¹ÀÌÀú

	UPROPERTY(EditDefaultsOnly, Category = "Visual|Curve")
	TObjectPtr<UCurveFloat> OffsetCurve;

private:
	UPROPERTY()
	TObjectPtr<AActor> CurrentTarget;

	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> FloorObjTypes;
	TArray<TEnumAsByte<EObjectTypeQuery>> HoverObjTypes;

	UPROPERTY()
	float OffsetTimer = 0.0f;

	UPROPERTY()
	bool bCursorLock = false;

	UPROPERTY()
	FVector LastCursorLocation;

	UPROPERTY()
	bool bShowSkillRange = false;
	
};

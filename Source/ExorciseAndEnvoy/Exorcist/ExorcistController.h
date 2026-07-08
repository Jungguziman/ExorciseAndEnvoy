// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TargetIndicator.h"

#include "ExorcistController.generated.h"

class UInputMappingContext;
class USkillBase;

UCLASS()
class EXORCISEANDENVOY_API AExorcistController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

public:
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;

	TObjectPtr<ATargetIndicator> GetIndicator() { return Indicator_Instance; }

	TObjectPtr<AActor> GetLockedTarget() { return Indicator_Instance->GetCurrentTarget(); }
	TArray<TObjectPtr<AActor>> GetTargetsInSkillArea() { return Indicator_Instance->GetTargetsInSkillArea(); }

	void ShowSkillRange(TObjectPtr<USkillBase> Skill);
	void HideSkillRange();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach|InputAction")
	TObjectPtr<UInputAction> CursorBindAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bCursorBind = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<ATargetIndicator> Indicator_Class;

	UPROPERTY()
	FVector CharacterOldPos;
	UPROPERTY()
	FVector CharacterCurPos;

private:
	UPROPERTY()
	TObjectPtr<ATargetIndicator> Indicator_Instance;

};

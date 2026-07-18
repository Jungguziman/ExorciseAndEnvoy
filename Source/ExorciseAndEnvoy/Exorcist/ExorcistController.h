// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TargetIndicator.h"

#include "ExorcistController.generated.h"

class UInputMappingContext;
class USkillBase;
class UHUDWidget;

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

	ATargetIndicator* GetIndicator() { return Indicator_Instance; }

	AActor* GetCurrentTarget() { return Indicator_Instance->GetCurrentTarget(); }

	void ShowSkillRange(USkillBase* Skill);
	void HideSkillRange();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach|InputAction")
	TObjectPtr<UInputAction> CursorBindAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<ATargetIndicator> Indicator_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHUDWidget> HUD_Class;

private:
	UPROPERTY()
	TObjectPtr<ATargetIndicator> Indicator_Instance;

	UPROPERTY()
	TObjectPtr<UHUDWidget> HUD_Instance;


};

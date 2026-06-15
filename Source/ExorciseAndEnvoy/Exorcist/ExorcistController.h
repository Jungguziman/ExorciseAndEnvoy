// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExorcistController.generated.h"

class UInputMappingContext;

/**
 * 
 */
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



};

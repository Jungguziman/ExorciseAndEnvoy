// Fill out your copyright notice in the Description page of Project Settings.

#include "ExorcistController.h"
#include "InputMappingContext.h"
#include "GameFramework/Pawn.h"
#include "TargetIndicator.h"
#include "SkillBase.h"
#include "HUDWidget.h"


void AExorcistController::BeginPlay()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	

	if (Indicator_Class)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetPawn();

		Indicator_Instance = GetWorld()->SpawnActor<ATargetIndicator>(Indicator_Class, FVector::ZeroVector, FRotator::ZeroRotator, Params);
	}

	if (HUD_Class)
	{
		HUD_Instance = CreateWidget<UHUDWidget>(this, HUD_Class);

		if (HUD_Instance)
		{
			HUD_Instance->AddToViewport();
		}
	}

}

void AExorcistController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindActionInstanceLambda(CursorBindAction, ETriggerEvent::Completed, [this](const FInputActionInstance& I)
	{
		Indicator_Instance->ToggleCursorLock();
	});
}

void AExorcistController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	

}

void AExorcistController::ShowSkillRange(USkillBase* Skill)
{
	Indicator_Instance->ShowSkillRange(Skill);
}

void AExorcistController::HideSkillRange()
{
	Indicator_Instance->HideSkillRange();
}


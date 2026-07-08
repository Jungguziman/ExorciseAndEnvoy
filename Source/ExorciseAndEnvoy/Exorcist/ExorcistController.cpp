// Fill out your copyright notice in the Description page of Project Settings.

#include "ExorcistController.h"
#include "InputMappingContext.h"
#include "GameFramework/Pawn.h"
#include "TargetIndicator.h"
#include "SkillBase.h"


void AExorcistController::BeginPlay()
{
	bShowMouseCursor = false;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	if (Indicator_Class)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = GetPawn();

		Indicator_Instance = GetWorld()->SpawnActor<ATargetIndicator>(Indicator_Class, FVector::ZeroVector, FRotator::ZeroRotator, Params);
	}

	CharacterOldPos = FVector(0.0f, 0.f, 0.f);
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
		bCursorBind = bCursorBind ? false : true;
		Indicator_Instance->ToggleCursorLock();
	});
}

void AExorcistController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	

}

void AExorcistController::ShowSkillRange(TObjectPtr<USkillBase> Skill)
{
	Indicator_Instance->ShowSkillRange(Skill);
}

void AExorcistController::HideSkillRange()
{
	Indicator_Instance->HideSkillRange();
}


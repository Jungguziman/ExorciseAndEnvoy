// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SkillBase.h"
#include "Exorcist.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ASkillBase;

UCLASS(Blueprintable)
class EXORCISEANDENVOY_API AExorcist : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExorcist();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	void Move(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Skill_Q(const FInputActionValue& Value);
	void Skill_E(const FInputActionValue& Value);
	void Skill_R(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Debug | Test")
	void DebugApplyChanges();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCamera;

	/** WASD 이동 입력 액션 (IA_Move) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SkillQ_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SkillE_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SkillR_Action;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Camera")
	float DefaultArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Camera")
	FRotator DefaultCameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Movement")
	FRotator DefaultRotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Camera")
	FVector DefaultCameraPosition;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	FGameplayTagContainer State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float HP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float HPRegen = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float MaxMP = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float MP = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float MPRegen = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float maxSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float SpeedRatio = 100.0f;

	

};

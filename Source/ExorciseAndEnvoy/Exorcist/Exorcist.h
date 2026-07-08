// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AnimCallback.h"

#include "Exorcist.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USkillManager;
class UStatusAttribute;
class UAnimInstance;
class UAnimInstanceBase_Exorcist;
class AExorcistController;

UCLASS(Blueprintable)
class EXORCISEANDENVOY_API AExorcist : public ACharacter, public IAnimCallback
{
	GENERATED_BODY()

public:
	AExorcist();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	// 인풋액션 -> 애니메이션
	void Move(const FInputActionValue& Value);
	//void Attack();
	void Casting(FGameplayTag Input);

	void ReleaseInput(FGameplayTag Input);

	// 회전 처리
	void FollowingCursor(float DeltaTime = 15.f);

public:
	// DEBUG YONG HAMSU
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Debug")
	void DebugApplyChanges();

	// 애니메이션 -> 실제 스킬 사용 | 순수가상함수 구현
	virtual void BeginCast(FGameplayTag Input);
	virtual void EndCast(FGameplayTag Input);

	virtual void GetMovementAnimData(float& OutSpeed, float& OutDirection, bool& OutIsDead);

public:
	TObjectPtr<USkillManager> GetSkillManager() { return SkillManager; }

	TObjectPtr<AExorcistController> GetExorcistController() { return PC; }

	TObjectPtr<UStatusAttribute> GetStatusAttribute() { return StatusAttribute; }

	void SetShowSkillRange(bool Value) { bShowSkillRange = Value; }

	FGameplayTagContainer GetStateTags() { return State; }

	TObjectPtr<UAnimMontage> GetCastMontage(FGameplayTag Input) { return CastMontages[Input]; }

protected: // 블루프린트에서 연결할 것들
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attach|InputAction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach|InputAction")
	TMap<FGameplayTag, TObjectPtr<UInputAction>> CastActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach|InputAction")
	TObjectPtr<UInputAction> ShowSkillRangeAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach|InputAction")
	TObjectPtr<UInputAction> ReleaseSkillAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimInstanceBase_Exorcist> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach|Animation")
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> CastMontages;


protected: // 캐릭터 카메라 구조
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Camera")
	float DefaultArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Camera")
	FRotator DefaultCameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Movement")
	FRotator DefaultRotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup|Camera")
	FVector DefaultCameraPosition;

protected: // 액터 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|SkillManager")
	TObjectPtr<USkillManager> SkillManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|StatusAttribute")
	TObjectPtr<UStatusAttribute> StatusAttribute;

	UPROPERTY()
	TObjectPtr<AExorcistController> PC;

protected: // 캐릭터 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Stats")
	FGameplayTagContainer State;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Casting")
	//TMap<FGameplayTag, bool> IsCastings;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	//FGameplayTag CurrentInput;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	//FGameplayTag CurrentAimingInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bShowSkillRange = false;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
	//bool bReleaseSkill = false;

};

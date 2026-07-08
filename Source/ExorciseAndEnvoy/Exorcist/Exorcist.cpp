// Fill out your copyright notice in the Description page of Project Settings.


#include "Exorcist.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

#include "AnimInstanceBase_Exorcist.h"
#include "ExorcistController.h"
#include "SkillManager.h"
#include "StatusAttribute.h"
#include "TargetIndicator.h"

// Sets default values
AExorcist::AExorcist()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultArmLength = 650.f;
	DefaultCameraRotation = FRotator(-50.f, 0.f, 0.f);
	DefaultCameraPosition = FVector(0.0f, 0.0f, 600.0f);
	DefaultRotationRate = FRotator(0.f, 640.f, 0.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->RotationRate = DefaultRotationRate;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = DefaultArmLength;       
	CameraBoom->SetRelativeRotation(DefaultCameraRotation); 
	CameraBoom->SetRelativeLocation(DefaultCameraPosition);
	CameraBoom->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	GetCapsuleComponent()->SetCapsuleRadius(35.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	SkillManager = CreateDefaultSubobject<USkillManager>(TEXT("SkillManager"));
	StatusAttribute = CreateDefaultSubobject<UStatusAttribute>(TEXT("StatusAttribute"));

	// Set StatusAttribute At Derived Classes

	StatusAttribute->SetMaxSpeed(500.0f);

	IsCastings.Add(Tags::Input_A, false);
	IsCastings.Add(Tags::Input_Q, false);
	IsCastings.Add(Tags::Input_E, false);
	IsCastings.Add(Tags::Input_R, false);
}

void AExorcist::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetMesh())
		AnimInstance = Cast<UAnimInstanceBase_Exorcist>(GetMesh()->GetAnimInstance());
	else
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance Not Selected"));

	if (!StatusAttribute)
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);

	State.AddTag(Tags::Exorcist_Idle);
}

void AExorcist::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PC = Cast<AExorcistController>(GetController());

	if (!PC)
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void AExorcist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (!State.HasTag(Tags::Exorcist_Casting))
		FollowingCursor(DeltaTime);

	StatusAttribute->SetSpeed(GetVelocity().Length());
}

void AExorcist::Move(const FInputActionValue& Value)
{
	if (StatusAttribute->GetDeBuffs().HasTag(Tags::Block) ||		// 강력 CC 시 이동 불가
		StatusAttribute->GetDeBuffs().HasTag(Tags::Debuff_Root))	// 속박 시 이동 불가
		return;


	State.RemoveTag(Tags::Exorcist_Idle);
	State.AddTag(Tags::Exorcist_Moving);

	FVector2D MovementVector = Value.Get<FVector2D>();

	float speed = StatusAttribute->GetFinalMaxSpeed();

	if (StatusAttribute->GetDeBuffs().HasTag(Tags::Debuff_Slow))
	{
		speed *= StatusAttribute->GetActiveEffect().Find(Tags::Debuff_Slow)->Value / 100.0f;
	}

	if (AnimInstance->IsAnyMontagePlaying())
	{
		speed *= 0.75f;
		GetCharacterMovement()->ForceReplicationUpdate();
	}

	GetCharacterMovement()->MaxWalkSpeed = speed;

	if (Controller != nullptr)
	{
		// 컨트롤러나 카메라가 바라보는 회전값 중 수평(Yaw) 방향만 추출
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		// 롤 시점 기준으로 화면 위쪽(정북향) 벡터 계산
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// 롤 시점 기준으로 화면 오른쪽(정동향) 벡터 계산
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 계산된 절대 방향 벡터에 키보드 입력 가중치만큼 이동 명령 전달
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AExorcist::Attack()
{
	//if (PC->)
	bShowSkillRange = false;
	PC->HideSkillRange();
	CurrentAimingInput = FGameplayTag::EmptyTag;
	CurrentInput = FGameplayTag::EmptyTag;

	if (!PC->GetLockedTarget())
		return;

	if (State.HasTag(Tags::Exorcist_Casting)) // 스킬 시전중 기본공격 불가
		return;

	if (StatusAttribute->GetDeBuffs().HasTag(Tags::Block)) // 강력 CC 시 기본공격불가
		return;
	
	if (AnimInstance->IsAnyMontagePlaying())
	{
		UE_LOG(LogTemp, Warning, TEXT("Montage Playing"));
	}

	if (!AnimInstance->IsAnyMontagePlaying() && !IsCastings[Tags::Input_A])
	{
		State.RemoveTag(Tags::Exorcist_Idle);
		State.AddTag(Tags::Exorcist_Casting);

		CurrentInput = Tags::Input_A;
		IsCastings[Tags::Input_A] = true;

		AnimInstance->Montage_Play(CastMontages[Tags::Input_A], 1.38f * StatusAttribute->GetFinalAttackSpeed());
	}
}

void AExorcist::Casting(FGameplayTag Input)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *Input.ToString());

	if (Input.MatchesTagExact(Tags::Input_A))
	{
		Attack();
		
		return;
	}

	if (StatusAttribute->GetDeBuffs().HasTag(Tags::Block) ||
		StatusAttribute->GetDeBuffs().HasTag(Tags::Debuff_Silence))
		return;

	TObjectPtr<USkillBase> Skill = SkillManager->GetSkill(Input);
	if (!Skill) return;

	// [수정] Shift를 누른 채 스킬 키를 누른 경우 -> 사거리 표시 모드 돌입
	if (bShowSkillRange)
	{
		CurrentAimingInput = Input; // 현재 조준 중인 스킬 기억
		PC->ShowSkillRange(Skill);
		return;
	}

	// [수정] 일반 시전 (Shift 없이 그냥 누른 경우) -> 즉시 시전
	//bool IsAttacking = CurrentInput.MatchesTagExact(Tags::Input_A);

	if (!State.HasTag(Tags::Exorcist_Casting) || IsCastings[Tags::Input_A])
	{
		if (IsCastings[Tags::Input_A])
		{
			EndCast(Tags::Input_A);
		}

		State.RemoveTag(Tags::Exorcist_Idle);
		State.AddTag(Tags::Exorcist_Casting);

		CurrentInput = Input;
		SkillManager->SetSkillCastLocation(PC->GetIndicator()->GetActorLocation());
		//IsCastings[Input] = true;

		AnimInstance->Montage_Play(CastMontages[Input]);
	}
	else if (State.HasTag(Tags::Exorcist_Casting))
	{
		for (auto Casts : IsCastings)
		{
			if (Casts.Value)
			{
				UE_LOG(LogTemp, Error, TEXT("캔슬 성공 : %s -> %s"), *Casts.Key.ToString(), *Input.ToString());
				EndCast(Casts.Key);

				State.RemoveTag(Tags::Exorcist_Idle);
				State.AddTag(Tags::Exorcist_Casting);

				CurrentInput = Input;
				SkillManager->SetSkillCastLocation(PC->GetIndicator()->GetActorLocation());
				//IsCastings[Input] = true;

				AnimInstance->Montage_Play(CastMontages[Input]);
			}
		}

		
	}

	UE_LOG(LogTemp, Warning, TEXT("선딜 시작 : %s"), *Input.ToString());
}

void AExorcist::ReleaseInput(FGameplayTag Input)
{
	PC->HideSkillRange(); // 사거리 끄기
	bShowSkillRange = false; // 플래그 초기화
	
	if (Input.MatchesTagExact(Tags::Input_A))
	{
		Attack();
	}
	// 만약 이 스킬로 사거리를 조준 중이었다면 키를 뗄 때 발사
	else if (CurrentAimingInput.MatchesTagExact(Input))
	{
		Casting(Input);
	}
	else if (CurrentAimingInput.IsValid())
	{
		Casting(CurrentAimingInput);
	}

	CurrentAimingInput = FGameplayTag::EmptyTag;
}

void AExorcist::FollowingCursor(float DeltaTime)
{
	FVector TargetLocation = PC->GetIndicator()->GetActorLocation();
	FVector StartLocation = GetActorLocation();
	TargetLocation.Z = StartLocation.Z;
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 15.0f);

	SetActorRotation(NewRotation);
}

void AExorcist::DebugApplyChanges()
{
	StatusAttribute->SetMaxSpeed(GetCharacterMovement()->MaxWalkSpeed);
}

void AExorcist::BeginCast(FGameplayTag Input)
{
	UE_LOG(LogTemp, Warning, TEXT("선딜 끝 : %s"), *Input.ToString());

	UE_LOG(LogTemp, Warning, TEXT("발사 : %s"), *Input.ToString());
	SkillManager->TryCast(Input);
	UE_LOG(LogTemp, Warning, TEXT("발사 완료 : %s"), *Input.ToString());

	UE_LOG(LogTemp, Warning, TEXT("후딜 시작 : %s"), *Input.ToString());
	
	IsCastings[Input] = true;
}

void AExorcist::EndCast(FGameplayTag Input)
{
	UE_LOG(LogTemp, Warning, TEXT("후딜 끝 : %s"), *Input.ToString());

	State.RemoveTag(Tags::Exorcist_Casting);
	State.AddTag(Tags::Exorcist_Idle);

	if (CurrentInput.MatchesTagExact(Input))
	{
	}
	CurrentInput = FGameplayTag::EmptyTag;

	AnimInstance->Montage_Stop(0.01f);

	IsCastings[Input] = false;
}

void AExorcist::GetMovementAnimData(float& OutSpeed, float& OutDirection, bool& OutIsDead)
{
	FVector Velocity = GetVelocity();

	OutSpeed = StatusAttribute->GetSpeed();
	OutDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, GetActorRotation());
	OutIsDead = StatusAttribute->GetHP() <= 0.f ? true : false;
}

void AExorcist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExorcist::Move);
			EnhancedInputComponent->BindActionInstanceLambda(MoveAction, ETriggerEvent::Completed, [this](const FInputActionInstance& I)
			{
				State.RemoveTag(Tags::Exorcist_Moving);
				State.AddTag(Tags::Exorcist_Idle);
			});
		}

		// [수정] 스킬 입력 이벤트 분리 처리
		for (auto Iter : CastActions)
		{
			if (Iter.Value)
			{
				// 1. 키를 누르고 있을 때 (Triggered) -> Casting 함수 내부에서 사거리를 켤지 즉시 시전할지 판단
				EnhancedInputComponent->BindAction(Iter.Value, ETriggerEvent::Started, this, &AExorcist::Casting, Iter.Key);

				// 2. 스킬 키에서 손을 뗐을 때 (Completed) -> 사거리 표시 중이었다면 즉시 스킬 시전!
				EnhancedInputComponent->BindAction(Iter.Value, ETriggerEvent::Completed, this, &AExorcist::ReleaseInput, Iter.Key);
			}
		}

		// Shift 키 입력 설정
		EnhancedInputComponent->BindActionInstanceLambda(ShowSkillRangeAction, ETriggerEvent::Started, [this](const FInputActionInstance& I)
		{
			bShowSkillRange = true;
		});
		EnhancedInputComponent->BindActionInstanceLambda(ShowSkillRangeAction, ETriggerEvent::Completed, [this](const FInputActionInstance& I)
		{
			//bCancelSkill = true;
			// Shift를 먼저 떼버렸을 때 조준선 제거 처리
			//{
			//	PC->HideSkillRange();
			//	CurrentAimingInput = FGameplayTag::EmptyTag;
			//}
			//else
			if (!CurrentAimingInput.IsValid())
				bShowSkillRange = false;
		});

		// 마우스 좌클릭 (ReleaseSkillAction) 설정
		//EnhancedInputComponent->BindActionInstanceLambda(ReleaseSkillAction, ETriggerEvent::Started, [this](const FInputActionInstance& I)
		//{
		//	//bShowSkillRange = false;
		//	//bCancelSkill = true;
		//	// Shift를 먼저 떼버렸을 때 조준선 제거 처리
		//	//if (CurrentAimingInput.IsValid())
		//	{
		//		//PC->HideSkillRange();
		//		//CurrentAimingInput = FGameplayTag::EmptyTag;
		//	}
		//});
		EnhancedInputComponent->BindAction(ReleaseSkillAction, ETriggerEvent::Started, this, &AExorcist::ReleaseInput, CurrentAimingInput);
	}
}


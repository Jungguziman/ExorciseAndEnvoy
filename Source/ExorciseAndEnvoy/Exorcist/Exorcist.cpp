// Fill out your copyright notice in the Description page of Project Settings.


#include "Exorcist.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AExorcist::AExorcist()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// --- 1. 자식들이 변경하기 쉬운 기본값 설정 변수 초기화 ---
	DefaultArmLength = 1000.f;
	DefaultCameraRotation = FRotator(-30.f, 0.f, 0.f);
	DefaultCameraPosition = FVector(0.0f, 0.0f, 300.0f);
	DefaultRotationRate = FRotator(0.f, 640.f, 0.f);

	// --- 2. 롤 스타일 기본 회전 규칙 잠금 ---
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// --- 3. 이동 컴포넌트 기본 세팅 ---
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = DefaultRotationRate; // 변수 대입
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	

	// --- 4. 카메라 붐 및 카메라 조립 ---
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = DefaultArmLength;       // 변수 대입
	CameraBoom->SetRelativeRotation(DefaultCameraRotation); // 변수 대입
	CameraBoom->SetRelativeLocation(DefaultCameraPosition);
	CameraBoom->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;
	
	State.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.Exorcist.Idle")));
}

// Called when the game starts or when spawned
void AExorcist::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExorcist::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AExorcist::Move(const FInputActionValue& Value)
{
	// WASD 입력값 (X: 좌우 이동 A/D, Y: 전후 이동 W/S) 벡터 추출
	FVector2D MovementVector = Value.Get<FVector2D>();

	State.AddTag(FGameplayTag::RequestGameplayTag(TEXT("State.Exorcist.Idle")));

	if (Controller != nullptr)
	{
		// 컨트롤러나 카메라가 바라보는 회전값 중 수평(Yaw) 방향만 추출
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 롤 시점 기준으로 화면 위쪽(정북향) 벡터 계산
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// 롤 시점 기준으로 화면 오른쪽(정동향) 벡터 계산
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 계산된 절대 방향 벡터에 키보드 입력 가중치만큼 이동 명령 전달
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

	}
}

void AExorcist::Attack(const FInputActionValue& Value)
{
	auto idle = FGameplayTag::RequestGameplayTag(TEXT("State.Exorcist.Idle"));
	auto casting = FGameplayTag::RequestGameplayTag(TEXT("State.Exorcist.Casting"));

	if (State.HasTag(casting))
		return;
	
	State.RemoveTag(idle);
	State.AddTag(casting);

	// 애님 노티파이 ( 어케 하는 지 알려주삼 )

	// 헤더에 있는 Skill에서 CastSpell 함수 호출 ( Skill TObjPtr 로 저장해 놓는거 맞는지 궁금 )
	// ㄴ 나머지 스킬 작동은 스킬 에서 연산

	// 내 캐릭터 마나 감소
	// 1번째 스킬칸 스킬 쿨타임 돌리기 (이 쿨타임은 AExorcist 에서 계산하는거 맞겠지)

}

void AExorcist::Skill_Q(const FInputActionValue& Value)
{
}

void AExorcist::Skill_E(const FInputActionValue& Value)
{
}

void AExorcist::Skill_R(const FInputActionValue& Value)
{
}

void AExorcist::DebugApplyChanges()
{
	GetCharacterMovement()->MaxWalkSpeed = maxSpeed;
}


// Called every frame
void AExorcist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	speed = GetVelocity().Length();
}

// Called to bind functionality to input
void AExorcist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExorcist::Move);
		}

		if (AttackAction)
		{
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AExorcist::Attack);
		}
		if (SkillQ_Action)
		{
			EnhancedInputComponent->BindAction(SkillQ_Action, ETriggerEvent::Triggered, this, &AExorcist::Skill_Q);
		}
		if (SkillE_Action)
		{
			EnhancedInputComponent->BindAction(SkillE_Action, ETriggerEvent::Triggered, this, &AExorcist::Skill_E);
		}
		if (SkillR_Action)
		{
			EnhancedInputComponent->BindAction(SkillR_Action, ETriggerEvent::Triggered, this, &AExorcist::Skill_R);
		}
	}

}


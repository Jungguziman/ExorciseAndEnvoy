// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USkillBase::USkillBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkillBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillBase::CastSkill(FVector Location)
{
	if (SkillFXAsset)
	{
		UNiagaraComponent* SpawnedFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			SkillFXAsset,
			Location,
			FRotator::ZeroRotator,
			FVector(Bound.X, Bound.Y, 10.0f), // Scale 주입
			true
		);

		if (SpawnedFX)
		{
			// 시스템이 실행된 지 정확히 1.0초 후에 비활성화(Deactivate)되도록 수명 락을 겁니다.
			// 나이아가라 자체 설정이 이미 1초 단발성(Burst Once)이라면 이 코드조차 필요 없습니다.
		}
	}
}


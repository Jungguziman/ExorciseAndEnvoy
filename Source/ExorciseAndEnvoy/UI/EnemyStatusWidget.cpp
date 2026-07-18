// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyStatusWidget.h"

#include "Components/ProgressBar.h"
#include "Damageable.h"
#include "StatusAttribute.h"

void UEnemyStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UEnemyStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
}

void UEnemyStatusWidget::SetCachedEnemyActor(AActor* EnemyActor)
{
	if (!CachedEnemyActor)
		CachedEnemyActor = EnemyActor;

}

void UEnemyStatusWidget::UpdateHPBar(float CurrentHP, float MaxHP)
{
	float Value = FMath::GetRangePct(0.f, MaxHP, CurrentHP);
	Value = FMath::Clamp(Value, 0.f, 1.f);

	HPProgressBar->SetPercent(Value);
}

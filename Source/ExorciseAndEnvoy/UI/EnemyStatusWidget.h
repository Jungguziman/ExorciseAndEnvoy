// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyStatusWidget.generated.h"

class UProgressBar;
class IDamageable;

UCLASS()
class EXORCISEANDENVOY_API UEnemyStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 위젯이 생성될 때 1회 초기화 구역 (C++의 BeginPlay 격)
	virtual void NativeConstruct() override;

	// 위젯의 프레임 연산 구역 (C++의 Tick 격)
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetCachedEnemyActor(AActor* EnemyActor);
	
	UFUNCTION(BlueprintCallable)
	void UpdateHPBar(float CurrentHP, float MaxHP);


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPProgressBar;
	
protected:
	TObjectPtr<AActor> CachedEnemyActor;
};

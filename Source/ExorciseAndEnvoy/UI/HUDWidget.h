// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "GameplayTagContainer.h"
#include "HUDWidget.generated.h"

class UProgressBar;
class UTextBlock;
class AExorcist;

UCLASS()
class EXORCISEANDENVOY_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// 체력 및 마나 UI 라인
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_HP_Current;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_HP_DmgFading; // 롤식 닳는 잔상 바

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_HP_Text;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_MP_Current;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_MP_Text;

	// 스킬 쿨타임 원형 프로그레스 바 라인 (Q, E, R 순정 3개)
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Skill_Q;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Skill_E;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Skill_R;

	// 스킬 쿨타임 숫자 가시성용 텍스트 라인
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Timer_Q;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Timer_E;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Timer_R;

protected:
	// 위젯이 생성될 때 1회 초기화 구역 (C++의 BeginPlay 격)
	virtual void NativeConstruct() override;

	// 위젯의 프레임 연산 구역 (C++의 Tick 격)
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	// 단일 스킬 슬롯의 내부 그래픽 피드백을 연산하는 캡슐화 헬퍼 함수
	void UpdateSkillSlot(FGameplayTag SkillTag, UProgressBar* TargetProgressBar, UTextBlock* TargetTimerText);

	UPROPERTY()
	TObjectPtr<AExorcist> CachedPlayerCharacter;

	// 롤식 피격 잔상 바가 스르륵 닳게 만들기 위한 보간(Interpolation) 수치 속도
	float HPFadeSpeed = 5.0f;
};

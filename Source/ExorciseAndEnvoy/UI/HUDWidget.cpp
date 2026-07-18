// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Exorcist.h"
#include "StatusAttribute.h"
#include "SkillManager.h"
#include "SkillBase.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		CachedPlayerCharacter = Cast<AExorcist>(PlayerPawn);
	}
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 방어 코드 세워 기습 크래시 원천 원치 차단
	if (!CachedPlayerCharacter || !CachedPlayerCharacter->GetStatusAttribute()) return;

	UStatusAttribute* Status = CachedPlayerCharacter->GetStatusAttribute();

	float CurrentHP = Status->GetHP();
	float MaxHP = Status->GetFinalMaxHP(); // 질문자님 코드 명세 기준 (MaxHP 속성 가져오기)

	if (MaxHP > 0.0f)
	{
		float HPPercent = CurrentHP / MaxHP;

		// 맨 앞 빨간색 체력바는 딜레이 없이 즉시 즉시 대입
		if (ProgressBar_HP_Current)
		{
			ProgressBar_HP_Current->SetPercent(HPPercent);
		}

		// [롤 스타일 피격 연출의 핵심]: 중간 암적색/회색 바는 FInterpTo를 타고 부드럽게 늦게 쫓아옵니다!
		if (ProgressBar_HP_DmgFading)
		{
			float CurrentFadePercent = ProgressBar_HP_DmgFading->GetPercent();
			float NewFadePercent = FMath::FInterpTo(CurrentFadePercent, HPPercent, InDeltaTime, HPFadeSpeed);
			ProgressBar_HP_DmgFading->SetPercent(NewFadePercent);
		}

		// 컴공식 정석 문자열 가공 인터페이스 ("현재체력 / 최대체력")
		if (TextBlock_HP_Text)
		{
			FString HPString = FString::Printf(TEXT("%d / %d"), FMath::TruncToInt(CurrentHP), FMath::TruncToInt(MaxHP));
			TextBlock_HP_Text->SetText(FText::FromString(HPString));
		}
	}

	// 마나 바 처리 (마나는 롤식 잔상이 없으므로 깔끔하게 다이렉트 주입)
	float CurrentMP = Status->GetMP(); // 마나 관련 함수가 정의되어 있다는 가정
	float MaxMP = Status->GetFinalMaxMP();

	if (MaxMP > 0.0f && ProgressBar_MP_Current)
	{
		ProgressBar_MP_Current->SetPercent(CurrentMP / MaxMP);

		if (TextBlock_MP_Text)
		{
			FString MPString = FString::Printf(TEXT("%d / %d"), FMath::TruncToInt(CurrentMP), FMath::TruncToInt(MaxMP));
			TextBlock_MP_Text->SetText(FText::FromString(MPString));
		}
	}

	UpdateSkillSlot(Tags::Input_Q, ProgressBar_Skill_Q, TextBlock_Timer_Q);
	UpdateSkillSlot(Tags::Input_E, ProgressBar_Skill_E, TextBlock_Timer_E);
	UpdateSkillSlot(Tags::Input_R, ProgressBar_Skill_R, TextBlock_Timer_R);
}

void UHUDWidget::UpdateSkillSlot(FGameplayTag SkillTag, UProgressBar* TargetProgressBar, UTextBlock* TargetTimerText)
{
	if (!CachedPlayerCharacter->GetSkillManager()) return;

	USkillManager* SkillMgr = CachedPlayerCharacter->GetSkillManager();
	USkillBase* Skill = SkillMgr->GetSkill(SkillTag);

	if (!Skill)
	{
		// 스킬이 아직 없거나 해금되지 않았다면 쿨타임 바를 통째로 반투명하게 덮어서 비활성화 연출
		if (TargetProgressBar) TargetProgressBar->SetPercent(1.0f);
		if (TargetTimerText) TargetTimerText->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	if (Skill->IsInCoolDown())
	{
		float RemainingTime = Skill->GetCurrentCoolDown();
		float MaxCoolDown = Skill->GetCoolTime();

		if (MaxCoolDown > 0.0f)
		{
			// 남은 시간 비중($0.0 \sim 1.0$)만큼 시계방향 쿨타임 음영 차오르게 주입
			if (TargetProgressBar) TargetProgressBar->SetPercent(RemainingTime / MaxCoolDown);

			if (TargetTimerText)
			{
				TargetTimerText->SetVisibility(ESlateVisibility::Visible);
				// 소수점 1자리(예: 4.5)까지만 이쁘게 잘라서 쿨타임 초 갱신

				FString TimerString;
				if (RemainingTime >= 1.f)
					TimerString = FString::Printf(TEXT("%.0f"), RemainingTime);
				else
					TimerString = FString::Printf(TEXT("%.1f"), RemainingTime);
				TargetTimerText->SetText(FText::FromString(TimerString));
			}
		}
	}
	else
	{
		// 쿨타임이 끝났다면 완전 투명 상태(0.0)로 만들어 스킬 아이콘 원본이 100% 진하게 노출되도록 클리어
		if (TargetProgressBar) TargetProgressBar->SetPercent(0.0f);
		if (TargetTimerText) TargetTimerText->SetVisibility(ESlateVisibility::Collapsed);
	}
}

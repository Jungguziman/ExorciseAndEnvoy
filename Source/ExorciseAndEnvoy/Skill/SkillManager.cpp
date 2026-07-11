#include "Skill/SkillManager.h"
#include "CircleShapeSkill.h"

#include "Components/SkeletalMeshComponent.h"
#include "StatusAttribute.h"
#include "Exorcist.h"
#include "ExorcistController.h"

USkillManager::USkillManager()
{
	PrimaryComponentTick.bCanEverTick = true;


	IsCastings.Add(Tags::Input_A, false);
	IsCastings.Add(Tags::Input_Q, false);
	IsCastings.Add(Tags::Input_E, false);
	IsCastings.Add(Tags::Input_R, false);
}

// Called when the game starts
void USkillManager::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AExorcist>(GetOwner());

	if (OwnerCharacter && OwnerCharacter->GetMesh())
	{
		OwnerAnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	}

	Skill_Instances.Empty();

	for (auto& Pair : Skill_Classes)
	{
		if (!Pair.Value)
			continue;

		USkillBase* Skill = NewObject<USkillBase>(this, Pair.Value);
		
		if (Skill)
		{
			Skill->PrimaryComponentTick.bCanEverTick = false;
			Skill->RegisterComponent();
		
			if (HasBegunPlay() && !Skill->HasBegunPlay())
			{
				Skill->RegisterComponentWithWorld(GetWorld());
			}
		}

		Skill_Instances.Add(Pair.Key, Skill);
	}

	
}

void USkillManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto& Pair : Skill_Instances)
	{
		if (USkillBase* Skill = Pair.Value)
		{
			if (Skill->GetCurrentCoolDown() > 0.0f)
			{
				float NewCoolDown = Skill->GetCurrentCoolDown() - DeltaTime;
				Skill->SetCurrentCoolDown(NewCoolDown < 0.0f ? 0.0f : NewCoolDown);
			}
		}
	}
}

void USkillManager::ProcessSkillCast(FGameplayTag Input, bool bShiftPressed)
{
	if (!OwnerCharacter || !OwnerAnimInstance) return;

	if (Input.MatchesTagExact(Tags::Input_A))
	{
		ExecuteAttack();
		return;
	}

	if (OwnerCharacter->GetStatusAttribute()->GetDeBuffs().HasTag(Tags::Block) ||
		OwnerCharacter->GetStatusAttribute()->GetDeBuffs().HasTag(Tags::Debuff_Silence))
		return;

	USkillBase* Skill = GetSkill(Input);
	if (!Skill) return;

	if (OwnerCharacter->GetStatusAttribute()->GetMP() < Skill->GetMPCost()) return;

	if (OwnerCharacter->GetStatusAttribute()->GetHP() < Skill->GetHPCost()) return;

	if (Skill->IsInCoolDown()) return;

	if (bShiftPressed)
	{
		CurrentAimingInput = Input;
		OwnerCharacter->GetExorcistController()->GetIndicator()->ShowSkillRange(Skill);
		
		return;
	}

	for (auto Pair : Skill_Instances)
	{
		if (!Pair.Key.MatchesTagExact(Tags::Input_A) && Pair.Value->IsPreCasting())
			return;
	}

	// ---------------------------------------------------------------------------
	// 몽타주 노티파이 타임라인 역산 구역 (정석 API 적용 버전)
	// ---------------------------------------------------------------------------
	float TargetPlayRate = 1.0f;
	UAnimMontage* CastMontage = OwnerCharacter->GetCastMontage(Input);

	if (CastMontage && Skill->GetPreCastDelay() > 0.0f)
	{
		float OriginalNotifyTriggerTime = -1.0f;
	
		for (const FAnimNotifyEvent& NotifyEvent : CastMontage->Notifies)
		{
			FString NotifyNameStr = NotifyEvent.NotifyName.ToString();

			if (NotifyNameStr.Contains(TEXT("Begin")) && NotifyNameStr.Contains(Input.ToString().Right(1).ToUpper()))
			{
				OriginalNotifyTriggerTime = NotifyEvent.GetTriggerTime();
				break;
			}
		}

		if (OriginalNotifyTriggerTime > 0.0f)
		{
			TargetPlayRate = OriginalNotifyTriggerTime / Skill->GetPreCastDelay();

			UE_LOG(LogTemp, Log, TEXT("[선딜레이 변속 완료] 원본 선딜 노티파이 : %f초 | 목표 선딜시간: %f초 -> 변경된 선딜 배속: %f"),
			OriginalNotifyTriggerTime, Skill->GetPreCastDelay(), TargetPlayRate);
		}
	}

	if (!OwnerCharacter->GetStateTags().HasTag(Tags::Exorcist_Casting) || IsCastings[Tags::Input_A])
	{
		if (IsCastings[Tags::Input_A]) { EndCast(Tags::Input_A); }

		OwnerCharacter->GetStateTags().RemoveTag(Tags::Exorcist_Idle);
		OwnerCharacter->GetStateTags().AddTag(Tags::Exorcist_Casting);

		CurrentInput = Input;
		if (OwnerCharacter->GetExorcistController())
		{
			SetSkillCastLocation(OwnerCharacter->GetExorcistController()->GetIndicator()->GetActorLocation());
		}

		GetSkill(Input)->StartCoolDown();

		OwnerAnimInstance->Montage_Play(CastMontage, TargetPlayRate);
	}
	else if (OwnerCharacter->GetStateTags().HasTag(Tags::Exorcist_Casting))
	{
		for (auto Casts : IsCastings)
		{
			if (Casts.Value)
			{
				UE_LOG(LogTemp, Error, TEXT("후딜레이 캔슬 성공 : %s -> %s"), *Casts.Key.ToString(), *Input.ToString());
				EndCast(Casts.Key);

				OwnerCharacter->GetStateTags().RemoveTag(Tags::Exorcist_Idle);
				OwnerCharacter->GetStateTags().AddTag(Tags::Exorcist_Casting);

				CurrentInput = Input;
				if (OwnerCharacter->GetExorcistController())
				{
					SetSkillCastLocation(OwnerCharacter->GetExorcistController()->GetIndicator()->GetActorLocation());
				}

				GetSkill(Input)->StartCoolDown();
				OwnerAnimInstance->Montage_Play(CastMontage, TargetPlayRate);

				break; // 불필요한 루프 오버헤드를 막기 위한 break 배선 마감
			}
		}
	}
}

void USkillManager::ProcessSkillRelease(FGameplayTag Input)
{
	if (!OwnerCharacter) return;

	if (OwnerCharacter->GetExorcistController())
	{
		OwnerCharacter->GetExorcistController()->GetIndicator()->HideSkillRange();
	}
	OwnerCharacter->SetShowSkillRange(false);

	if (Input.MatchesTagExact(Tags::Input_A))
	{
		ExecuteAttack();
	}
	else if (CurrentAimingInput.MatchesTagExact(Input))
	{
		ProcessSkillCast(Input, false); // 조준 끝났으니 조준 플래그(false)로 즉시 시전 전환!
	}
	else if (CurrentAimingInput.IsValid())
	{
		ProcessSkillCast(CurrentAimingInput, false);
	}

	CurrentAimingInput = FGameplayTag::EmptyTag;
}

void USkillManager::ExecuteAttack()
{
	// 기존 평타 로직을 매니저 소유 기반으로 그대로 이식
	OwnerCharacter->SetShowSkillRange(false);

	if (OwnerCharacter->GetExorcistController())
	{
		OwnerCharacter->GetExorcistController()->GetIndicator()->HideSkillRange();
	}
	CurrentAimingInput = FGameplayTag::EmptyTag;
	CurrentInput = FGameplayTag::EmptyTag;

	if (!OwnerCharacter->GetExorcistController()->GetLockedTarget()) return;
	if (OwnerCharacter->GetStateTags().HasTag(Tags::Exorcist_Casting)) return;
	if (OwnerCharacter->GetStatusAttribute()->GetDeBuffs().HasTag(Tags::Block)) return;

	if (!OwnerAnimInstance->IsAnyMontagePlaying() && !IsCastings[Tags::Input_A])
	{
		OwnerCharacter->GetStateTags().RemoveTag(Tags::Exorcist_Idle);
		OwnerCharacter->GetStateTags().AddTag(Tags::Exorcist_Casting);

		CurrentInput = Tags::Input_A;
		IsCastings[Tags::Input_A] = true;

		OwnerAnimInstance->Montage_Play(OwnerCharacter->GetCastMontage(Tags::Input_A), 1.38f * OwnerCharacter->GetStatusAttribute()->GetFinalAttackSpeed());
	}
}

USkillBase* USkillManager::GetSkill(FGameplayTag Input)
{
	TObjectPtr<USkillBase>* SkillPtr = Skill_Instances.Find(Input);

	return *SkillPtr;
}

bool USkillManager::IsSkillInCoolTime(FGameplayTag Input)
{
	return GetSkill(Input)->IsInCoolDown();
}

void USkillManager::TryCast(FGameplayTag Input)
{
	if (!Input.MatchesTagExact(Tags::Input_A))
	{
		if (GetSkill(Input))
			GetSkill(Input)->CastSkill(NextSkillCastLocation);
	}
}

void USkillManager::BeginCast(FGameplayTag Input)
{
	TryCast(Input);

	IsCastings[Input] = true;

	if (Input.MatchesTagExact(Tags::Input_A))
		return;

	USkillBase* Skill = GetSkill(Input);
	if (Skill && OwnerAnimInstance && Skill->GetPostCastDelay() > 0.0f)
	{
		UAnimMontage* ActiveMontage = OwnerAnimInstance->GetCurrentActiveMontage();
		UAnimMontage* CastMontage = OwnerCharacter->GetCastMontage(Input);

		// 현재 재생 중인 몽타주가 이 스킬의 몽타주가 맞는지 안전 검증
		if (ActiveMontage && ActiveMontage == CastMontage)
		{
			float TotalLength = ActiveMontage->GetPlayLength(); // 몽타주 순정 총 길이 (예: 3.0초)
			float CurrentPos = OwnerAnimInstance->Montage_GetPosition(ActiveMontage); // 현재 Begin 노티파이 위치 (예: 0.5초)

			// 팩트: 애니메이션의 남은 순정 분량을 역산 (예: 3.0 - 0.5 = 2.5초)
			float RemainingOriginalTime = TotalLength - CurrentPos;

			if (RemainingOriginalTime > 0.0f)
			{
				// 공식: 남은 순정 시간 / 내가 C++에 설정한 목표 후딜 시간 = 후딜레이 전용 재생 배속
				float PostPlayRate = RemainingOriginalTime / Skill->GetPostCastDelay();

				// [핵심 API]: 재생 중인 몽타주의 재생 속도만 후딜레이 기어로 부드럽게 스위칭합니다!
				OwnerAnimInstance->Montage_SetPlayRate(ActiveMontage, PostPlayRate);

				UE_LOG(LogTemp, Log, TEXT("[후딜레이 변속 완료] 남은 원본 분량: %f초 | 목표 후딜시간: %f초 -> 변경된 후딜 배속: %f"),
					RemainingOriginalTime, Skill->GetPostCastDelay(), PostPlayRate);
			}
		}
	}
}

void USkillManager::EndCast(FGameplayTag Input)
{
	if (OwnerCharacter)
	{
		OwnerCharacter->GetStateTags().RemoveTag(Tags::Exorcist_Casting);
		OwnerCharacter->GetStateTags().AddTag(Tags::Exorcist_Idle);
	}

	CurrentInput = FGameplayTag::EmptyTag;

	if (OwnerAnimInstance)
	{
		OwnerAnimInstance->Montage_Stop(0.01f);
	}

	IsCastings[Input] = false;
}

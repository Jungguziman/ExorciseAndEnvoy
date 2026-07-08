// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillManager.h"
#include "CircleShapeSkill.h"

// Sets default values for this component's properties
USkillManager::USkillManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	
	//Skills.Add(Tags::Input_Q, NewSkill);
	//Skills.Add(Tags::Input_E, NewSkill);
	//Skills.Add(Tags::Input_R, NewSkill);
}


// Called when the game starts
void USkillManager::BeginPlay()
{
	Super::BeginPlay();

	for (auto SkillClass : Skill_Classes)
	{
		if (!SkillClass.Value)
			break;

		TObjectPtr<USkillBase> Skill = NewObject<USkillBase>(this, SkillClass.Value);
		
		if (Skill)
		{
			Skill->RegisterComponent();
		
			if (HasBegunPlay() && !Skill->HasBegunPlay())
			{
				Skill->RegisterComponentWithWorld(GetWorld());
			}
		}

		Skill_Instances.Add(SkillClass.Key, Skill);
	}

	
}

void USkillManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USkillManager::TryCast(FGameplayTag Input)
{
	if (!Input.MatchesTagExact(Tags::Input_A))
	{
		if (Skill_Instances[Input])
			Skill_Instances[Input]->CastSkill(NextSkillCastLocation);
	}
}

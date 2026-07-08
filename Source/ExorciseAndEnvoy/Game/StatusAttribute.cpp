// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/StatusAttribute.h"

#include "TimerManager.h"

// Sets default values for this component's properties
UStatusAttribute::UStatusAttribute()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UStatusAttribute::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UStatusAttribute::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatusAttribute::ApplyActiveEffect(FGameplayTag EffectTag, float Duration, float Value)
{
	if (ActiveEffects.Contains(EffectTag))
	{
		GetWorld()->GetTimerManager().ClearTimer(ActiveEffects[EffectTag].TimerHandle);
	}

	FActiveEffect Effect = FActiveEffect(EffectTag, Duration, Value);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, EffectTag]()
	{
		RemoveActiveEffect(EffectTag);
	});

	GetWorld()->GetTimerManager().SetTimer(Effect.TimerHandle, TimerDelegate, Duration, false);


	if (EffectTag.MatchesTagExact(Tags::Debuff_Fear) ||
		EffectTag.MatchesTagExact(Tags::Debuff_Knockback) ||
		EffectTag.MatchesTagExact(Tags::Debuff_Stun) ||
		EffectTag.MatchesTagExact(Tags::Debuff_Taunt))
		ApplyActiveEffect(Tags::Block, Duration);

	ActiveEffects.Add(EffectTag, Effect);

	if (EffectTag.MatchesTag(Tags::Buff))
		Buffs.AddTag(EffectTag);
	else
		Debuffs.AddTag(EffectTag);
}

void UStatusAttribute::RemoveActiveEffect(FGameplayTag EffectTag)
{
	if (!ActiveEffects.Contains(EffectTag))
		return;

	GetWorld()->GetTimerManager().ClearTimer(ActiveEffects[EffectTag].TimerHandle);

	ActiveEffects.Remove(EffectTag);

	if (EffectTag.MatchesTag(Tags::Buff))
		Buffs.RemoveTag(EffectTag);
	else
		Debuffs.RemoveTag(EffectTag);
}


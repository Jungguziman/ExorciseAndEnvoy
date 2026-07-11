// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ObjectPoolSubsystem.h"

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UObjectPoolSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UObjectPoolSubsystem::GetActorsInCircle(const FVector2D& CenterPos, const float& Radius, TArray<AActor*>& OutActors)
{
	OutActors.Empty();

	// 팩트: 적 캐릭터의 캡슐 반지름 보너스(50.f) 감안하여 제곱 거리 한계선 구축
	float RadiusWithBonus = Radius + 50.0f;
	float MaxDistanceSq = RadiusWithBonus * RadiusWithBonus;

	for (const TWeakObjectPtr<AActor>& WeakActor : RegisteredActors)
	{
		if (!WeakActor.IsValid()) continue;

		AActor* TargetActor = WeakActor.Get();
		FVector2D TargetPos = FVector2D(TargetActor->GetActorLocation());

		float DistSquare = FVector2D::DistSquared(CenterPos, TargetPos);
		if (DistSquare <= MaxDistanceSq)
		{
			OutActors.Add(TargetActor);
		}
	}
}

void UObjectPoolSubsystem::GetActorsInSector(const FVector2D& StartPos, const FVector& Direction, const float& Radius, const float& EulerAngle, TArray<AActor*> OutActors)
{
	OutActors.Empty();

	FVector2D ForwardVector = FVector2D(Direction.X, Direction.Y).GetSafeNormal();

	float HalfAngleRad = FMath::DegreesToRadians(EulerAngle) / 2.f;
	float MaxAllowedCos = FMath::Cos(HalfAngleRad);

	float MaxDistSqaure = powf(Radius, 2);

	for (const TWeakObjectPtr<AActor>& WeakActor : RegisteredActors)
	{
		if (!WeakActor.IsValid())
			continue;

		AActor* TargetActor = WeakActor.Get();

		FVector2D TargetPos = FVector2D(TargetActor->GetActorLocation());

		float DistanceSq = FVector2D::DistSquared(StartPos, TargetPos);
		if (DistanceSq > MaxDistSqaure)
		{
			continue;
		}

		FVector2D DirToTarget = (TargetPos - StartPos).GetSafeNormal();
		float DotResult = FVector2D::DotProduct(ForwardVector, DirToTarget);

		if (DotResult >= MaxAllowedCos)
		{
			OutActors.Add(TargetActor);
		}
	}
}

void UObjectPoolSubsystem::GetActorsInRect(const FVector2D& StartPos, const FVector& Direction, const FVector2D& Extent, TArray<AActor*> OutActors)
{
	OutActors.Empty();

	FVector2D ForwardAxis = FVector2D(Direction.X, Direction.Y).GetSafeNormal();
	FVector2D RightAxis = FVector2D(-ForwardAxis.Y, ForwardAxis.X);

	float MaxForwardDist = Extent.X; // 앞뒤 세로 한계선
	float MaxRightDist = Extent.Y;   // 좌우 가로 한계선

	for (const TWeakObjectPtr<AActor>& WeakActor : RegisteredActors)
	{
		if (!WeakActor.IsValid()) continue;

		AActor* TargetActor = WeakActor.Get();
		FVector2D TargetPos = FVector2D(TargetActor->GetActorLocation());

		FVector2D DirToTarget = TargetPos - StartPos;

		float ForwardProjectedDist = FVector2D::DotProduct(DirToTarget, ForwardAxis);

		if (FMath::Abs(ForwardProjectedDist) > MaxForwardDist)
		{
			continue; // 세로 범위 벗어나면 탈락
		}

		float RightProjectedDist = FVector2D::DotProduct(DirToTarget, RightAxis);

		if (FMath::Abs(RightProjectedDist) > MaxRightDist)
		{
			continue; // 가로 범위 벗어나면 탈락
		}

		OutActors.Add(TargetActor);
	}
}

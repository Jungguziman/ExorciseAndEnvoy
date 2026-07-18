// Fill out your copyright notice in the Description page of Project Settings.


#include "Exorcist/Hyunjin.h"
#include "Hyunjin.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "StatusAttribute.h"

AHyunjin::AHyunjin()
{
	ArtTube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArtTube"));
	ArtTube->SetupAttachment(GetMesh(), TEXT("Spine01"));
	ArtTube->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArtTube->bReceivesDecals = false;

	Slipper_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slipper_Left"));
	Slipper_L->SetupAttachment(GetMesh(), TEXT("LeftToeBase"));
	Slipper_L->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Slipper_L->bReceivesDecals = false;

	Slipper_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slipper_Right"));
	Slipper_R->SetupAttachment(GetMesh(), TEXT("RightToeBase"));
	Slipper_R->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Slipper_R->bReceivesDecals = false;

	Brush = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brush"));
	Brush->SetupAttachment(GetMesh(), TEXT("RightHand"));
	Brush->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Brush->bReceivesDecals = false;
	
	StatusAttribute->SetMaxSpeed(600.f);
	StatusAttribute->SetAttackSpeed(1.5f);
	StatusAttribute->SetAttackDamage(5.f);

}

void AHyunjin::BeginPlay()
{
	Super::BeginPlay();

}

void AHyunjin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

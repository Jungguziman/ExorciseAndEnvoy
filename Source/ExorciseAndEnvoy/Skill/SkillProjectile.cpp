// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillProjectile.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Damageable.h"
#include "StatusAttribute.h"

// Sets default values
ASkillProjectile::ASkillProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	Projectile->SetupAttachment(Sphere);
	Projectile->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->UpdatedComponent = RootComponent;
	

	Movement->InitialSpeed = 4000.f;
	Movement->MaxSpeed = 4000.f;

	Movement->ProjectileGravityScale = 0.f;

	Movement->bIsHomingProjectile = true;
	Movement->HomingAccelerationMagnitude = 2000.f;
	Movement->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ASkillProjectile::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ASkillProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(TargetActor))
	{
		Destroy();
		return;
	}

	if (Target == nullptr)
		Destroy();
	
}

void ASkillProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogTemp, Log, TEXT("[%s] : Ouch"), *OtherActor->GetName());

	if (OtherActor == TargetActor)
	{
		Target->ApplyDamage(DmgEvent);
		Destroy();
	}
		
}

void ASkillProjectile::SetTarget(AActor* Enemy)
{
	if (Enemy)
	{
		Target = Cast<IDamageable>(Enemy);
		TargetActor = Enemy;
		
		Movement->HomingTargetComponent = TargetActor->GetRootComponent();
	}
	else
	{
		Target = nullptr;
		TargetActor = nullptr;
	}
	
}


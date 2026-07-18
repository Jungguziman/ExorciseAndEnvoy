// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exorcist/Exorcist.h"
#include "Hyunjin.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class EXORCISEANDENVOY_API AHyunjin : public AExorcist
{
	GENERATED_BODY()
	
public:
	AHyunjin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> ArtTube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> Slipper_L;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> Slipper_R;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> Brush;



};

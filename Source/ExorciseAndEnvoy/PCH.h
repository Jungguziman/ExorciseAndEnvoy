#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

#include "Logging/LogMacros.h"

#include "GameplayTagContainer.h"
#include "GameplayTagsClasses.h"

#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputActionValue.h"

#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AnimationCoreClasses.h"

#include "EAEGameInstance.h"

#include "ObjectPoolSubsystem.h"

#define ECC_Floor ECC_GameTraceChannel1
#define ECC_Enemy ECC_GameTraceChannel2

#define GetOBJPool GetWorld()->GetSubsystem<UObjectPoolSubsystem>()
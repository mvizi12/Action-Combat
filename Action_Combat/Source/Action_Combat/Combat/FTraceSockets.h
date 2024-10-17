// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTraceSockets.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ACTION_COMBAT_API FTraceSockets
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Name of the socket where the weapon trace should begin"))
	FName socketStart;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Name of the socket where the weapon trace should end"))
	FName socketEnd;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Rotation of the weapon trace"))
	FName socketRotation;
};

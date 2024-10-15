// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EEnemyState
{
	Charge UMETA(DisplayName = "Charge"),
	Dead UMETA(DisplayName = "Dead"),
	Idle UMETA(DisplayName = "Idle"),
	Melee UMETA(DisplayName = "Melee"),
	Range UMETA(DisplayName = "Range")
};
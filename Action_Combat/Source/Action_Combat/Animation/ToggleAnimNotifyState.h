// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ToggleAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_COMBAT_API UToggleAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent*, UAnimSequenceBase*, float, const FAnimNotifyEventReference&) override;
	virtual void NotifyEnd(USkeletalMeshComponent*, UAnimSequenceBase*, const FAnimNotifyEventReference&) override;

};

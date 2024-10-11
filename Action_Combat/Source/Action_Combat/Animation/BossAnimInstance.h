// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_COMBAT_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	//Unreal doesn't suggest private variables be exposed to blueprint
	private:
		APawn* characterPawn;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float currentSpeed {0.0f};

		UFUNCTION(BlueprintCallable)
		void UpdateCharacterPawn();
	
};

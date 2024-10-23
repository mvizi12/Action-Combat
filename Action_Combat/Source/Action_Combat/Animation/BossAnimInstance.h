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

	private:
		APawn* bossPawn;

		void UpdateVelocity();

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector currentVeloctiy{0.0f, 0.0f, 0.0f};

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float currentSpeed {0.0f};

		UFUNCTION(BlueprintCallable)
		void UpdateBossPawn();

		UFUNCTION(BlueprintCallable)
		void UpdateCurrentSpeed();
	
	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isCharing {false};
	
};

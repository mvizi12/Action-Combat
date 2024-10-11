// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EStat.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	bool canRegenStamina {true};

	UPROPERTY(EditAnywhere)
	float staminaRegenDelay {2.0f};

	UPROPERTY(EditAnywhere)
	double staminaRegenRate {10};

	virtual void BeginPlay() override;

	UFUNCTION()
	void EnableStaminaRegen();

public:
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStat>, float> stats;
	
	UStatsComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float damage);

	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float amount);

	UFUNCTION(BlueprintCallable)
	void RegenStamina();

		
};

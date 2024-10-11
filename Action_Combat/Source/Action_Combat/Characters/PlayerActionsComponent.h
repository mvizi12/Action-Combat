// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnRunSignature, UPlayerActionsComponent, OnRunDelegate, float, cost);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	ACharacter* characterRef;
	class IMainPlayerInterface* iPlayerRef;
	class UCharacterMovementComponent* movementComp;

protected:
	UPROPERTY(EditAnywhere)
	float walkSpeed {600.0f};

	UPROPERTY(EditAnywhere)
	float runSpeed {1200.0f};

	UPROPERTY(EditAnywhere)
	float staminaCostRun {0.1f};

	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnRunSignature OnRunDelegate;

	UPlayerActionsComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StartRun();

	UFUNCTION(BlueprintCallable)
	void StopRun();

		
};

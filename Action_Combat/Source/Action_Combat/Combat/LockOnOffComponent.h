// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnOffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API ULockOnOffComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	//Making this a character instead of an actor because we want access to some functions in the "ACharacter" class
	ACharacter* ownerRef; //Reference to the owner of this component
	APlayerController* playerController;
	class UCharacterMovementComponent* characterMovementComponent;
	class USpringArmComponent* springArmComponent;

	void LockOn(float radius, FVector cameraOffset);
	void LockOff();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool lockedOn {false};

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Positive number will tilt the camera up when locked on and negative number will tilt down"))
	float lockedOnCameraTiltZ {0.0f};

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ToggleLockOnOff(float radius, FVector cameraOffset);

public:
	AActor* currentTargetActor;

	// Sets default values for this component's properties
	ULockOnOffComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnOffComponent.h"

// Sets default values for this component's properties
ULockOnOffComponent::ULockOnOffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockOnOffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void ULockOnOffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*Private Functions*/

/*Protected Functions*/
void ULockOnOffComponent::ToggleLockOnOff()
{
	if (lockedOn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Locking off"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Locking on"));
	}
}

/*Public Functions*/


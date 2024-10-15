// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtPlayerComponent.h"
#include "Boss.h"
#include "EEnemyState.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULookAtPlayerComponent::ULookAtPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	ownerRef = GetOwner<ABoss>();
	
}


// Called every frame
void ULookAtPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(ownerRef) || !canRotate) {return;}

	FRotator currentRotation {ownerRef->GetActorRotation()};
	FVector currentLocation {ownerRef->GetActorLocation()};

	FVector targetLocation {GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()};
	FRotator desiredRotation {UKismetMathLibrary::FindLookAtRotation(currentLocation, targetLocation)};
	FRotator newRotation {UKismetMathLibrary::RInterpTo_Constant(currentRotation, desiredRotation, DeltaTime, rotationSpeed)};
	//Only need the enemy to rotate left and right, meaning the z-axis
	//Yaw = z-axis
	//Pitch = y-axis
	//Roll = x-axis
	FRotator newYawOnlyRotation {currentRotation.Pitch, newRotation.Yaw, currentRotation.Roll};
	ownerRef->SetActorRotation(newYawOnlyRotation);


}


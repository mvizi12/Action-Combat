// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnOffComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	ownerRef = GetOwner<ACharacter>();
	if (ownerRef == nullptr) {return;}
	playerController = ownerRef->GetController<APlayerController>();
	characterMovementComponent = ownerRef->GetCharacterMovement();
	springArmComponent = ownerRef->FindComponentByClass<USpringArmComponent>();
}

// Called every frame
void ULockOnOffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(currentTargetActor)) {return;}
	if (!IsValid(playerController)) {return;}

	FVector currentLocation {ownerRef->GetActorLocation()};
	FVector targetLocation {currentTargetActor->GetActorLocation()};
	targetLocation.Z += lockedOnCameraTiltZ;
	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(currentLocation, targetLocation);
	playerController->SetControlRotation(newRotation);
}

/*Private Functions*/
void ULockOnOffComponent::LockOn(float radius, FVector cameraOffset)
{
	FHitResult outHitResult;
	FVector currentLocation {ownerRef->GetActorLocation()};
	FCollisionShape sphere {FCollisionShape::MakeSphere(radius)};
	FCollisionQueryParams ignoreParams {FName {TEXT("Ignore Collision Parameters")}, false, ownerRef};

	//Trace a sphere around the owner of this component looking through the "Fighting" channel while ignoring the owner
	if (!GetWorld()->SweepSingleByChannel(outHitResult, currentLocation, currentLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, sphere, ignoreParams)) {return;}

	UE_LOG(LogTemp, Warning, TEXT("Locking on to: %s"), *outHitResult.GetActor()->GetName());
	currentTargetActor = outHitResult.GetActor();

	playerController->SetIgnoreLookInput(true); //Player can't controll the camer anymore
	ownerRef->bUseControllerRotationYaw = false;
	characterMovementComponent->bUseControllerDesiredRotation = true;

	springArmComponent->TargetOffset = cameraOffset;
}

void ULockOnOffComponent::LockOff()
{
	UE_LOG(LogTemp, Warning, TEXT("Locking off"));
}

/*Protected Functions*/
void ULockOnOffComponent::ToggleLockOnOff(float radius, FVector cameraOffset)
{
	if (lockedOn)
	{
		LockOff();
	}
	else
	{
		LockOn(radius, cameraOffset);
	}
}

/*Public Functions*/


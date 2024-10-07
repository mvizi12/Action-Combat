// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnOffComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\Enemy.h"

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

	GetReferences();
}

// Called every frame
void ULockOnOffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(currentTargetActor)) {return;}
	if (!IsValid(playerController)) {return;}

	SetPlayerControlRotation();
}

/*Private Functions*/
void ULockOnOffComponent::GetReferences()
{
	ownerRef = GetOwner<ACharacter>();
	if (ownerRef == nullptr) {return;}
	playerController = ownerRef->GetController<APlayerController>();
	characterMovementComponent = ownerRef->GetCharacterMovement();
	springArmComponent = ownerRef->FindComponentByClass<USpringArmComponent>();
}

void ULockOnOffComponent::LockOn(float radius, FVector cameraOffset)
{
	//Sphere trace around this component's owner looking through the "Fighting" channel while ignoring the owner
	FHitResult outHitResult;
	FVector currentLocation {ownerRef->GetActorLocation()};
	FCollisionShape sphere {FCollisionShape::MakeSphere(radius)};
	FCollisionQueryParams ignoreParams {FName {TEXT("Ignore Collision Parameters")}, false, ownerRef};

	if (!GetWorld()->SweepSingleByChannel(outHitResult, currentLocation, currentLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, sphere, ignoreParams)) {return;}
	if (!outHitResult.GetActor()->Implements<UEnemy>()) {return;} //If hit actor doesn't implement "Enemy" interface, return

	UE_LOG(LogTemp, Warning, TEXT("Locking on to: %s"), *outHitResult.GetActor()->GetName());
	currentTargetActor = outHitResult.GetActor();

	SetLockOnSettings(cameraOffset);
	lockedOn = true;
	IEnemy::Execute_OnSelect(currentTargetActor);
}

void ULockOnOffComponent::LockOff()
{
	UE_LOG(LogTemp, Warning, TEXT("Locking off"));
	IEnemy::Execute_OnDeselect(currentTargetActor);
	currentTargetActor = nullptr;

	playerController->ResetIgnoreLookInput();
	
	//ownerRef->bUseControllerRotationYaw = true;

	characterMovementComponent->bOrientRotationToMovement = true;
	characterMovementComponent->bUseControllerDesiredRotation = false;

	springArmComponent->TargetOffset = FVector::ZeroVector;
	lockedOn = false;
}

void ULockOnOffComponent::SetLockOnSettings(FVector cameraOffset)
{
	//Set new player control settings
	playerController->SetIgnoreLookInput(true); //Player can't control the camera anymore

	//ownerRef->bUseControllerRotationYaw = false;

	characterMovementComponent->bOrientRotationToMovement = false;
	characterMovementComponent->bUseControllerDesiredRotation = true;

	//Move the camera to a desirable positions while locked on to target
	springArmComponent->TargetOffset = cameraOffset;
}

void ULockOnOffComponent::SetPlayerControlRotation()
{
	//Tilt the player controller to a desirable rotation
	FVector currentLocation {ownerRef->GetActorLocation()};
	FVector targetLocation {currentTargetActor->GetActorLocation()};

	//Can't lock on to target if they're out of range
	double distance {FVector::Distance(currentLocation, targetLocation)};
	if (distance > breakDistance)
	{
		LockOff();
		return;
	}

	targetLocation.Z += lockedOnCameraTiltZ;
	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(currentLocation, targetLocation);
	playerController->SetControlRotation(newRotation);
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


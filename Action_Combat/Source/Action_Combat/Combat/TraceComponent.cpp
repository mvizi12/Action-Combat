// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	GetReferences();
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(skeletalMeshComp)) {return;}

	FVector socketStartLocation {skeletalMeshComp->GetSocketLocation(socketStart)};
	FVector socketEndLocation {skeletalMeshComp->GetSocketLocation(socketEnd)};
	FQuat socketShapeRotation {skeletalMeshComp->GetSocketQuaternion(socketRotation)};

	float socketShapeHeight {static_cast<float>(FVector::Distance(socketStartLocation, socketEndLocation))};
	FVector socketBoxHalfExtent {socketBoxLength, socketBoxLength, socketShapeHeight};
	socketBoxHalfExtent /= 2;

	TArray<FHitResult> outHits;
	FCollisionShape box {FCollisionShape::MakeBox(socketBoxHalfExtent)};
	//FCollisionShape capsule {FCollisionShape::MakeCapsule(socketCapsauleRadius, socketShapeHeight / 2)};
	FCollisionQueryParams ignoreParams {FName {TEXT("Ignore Collision Parameters")}, false, ownerRef};

	bool targetFound = GetWorld()->SweepMultiByChannel(outHits, socketStartLocation, socketEndLocation, socketShapeRotation, ECollisionChannel::ECC_GameTraceChannel1, box, ignoreParams);

	if (debugModeEnabled)
	{
		FVector centerPoint {UKismetMathLibrary::VLerp(socketStartLocation, socketEndLocation, 0.5f)};
		//DrawDebugCapsule(GetWorld(), socketMidLocation, socketShapeHeight / 2, socketCapsauleRadius, socketShapeRotation, FColor::Red, false, 0.1f, 0U, 1.0f);
		UKismetSystemLibrary::DrawDebugBox(GetWorld(), centerPoint, box.GetExtent(), targetFound ? FColor::Green : FColor::Red, socketShapeRotation.Rotator(), 0.1f, 1.0f);
	}

	if (!targetFound) {return;}

	UE_LOG(LogTemp, Warning, TEXT("Target(s) found"));
}

/************************************Private Functions************************************/
void UTraceComponent::GetReferences()
{
	ownerRef = GetOwner();
	if (!IsValid(ownerRef)) {return;}
	skeletalMeshComp = ownerRef->FindComponentByClass<USkeletalMeshComponent>();
}
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
/************************************Public Functions************************************/


// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DamageEvents.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\Fighter.h"

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

	TArray<FHitResult> outHits;
	WeaponTrace(outHits);
	if (!isAttacking || outHits.Num() == 0) {return;}
	HandleDamage(outHits);
}

/************************************Private Functions************************************/
void UTraceComponent::GetReferences()
{
	ownerRef = GetOwner();
	if (!IsValid(ownerRef)) {return;}
	skeletalMeshComp = ownerRef->FindComponentByClass<USkeletalMeshComponent>();
}

void UTraceComponent::WeaponTrace(TArray<FHitResult> &outHits)
{
	if (!IsValid(skeletalMeshComp)) {return;}

	FVector socketStartLocation {skeletalMeshComp->GetSocketLocation(socketStart)};
	FVector socketEndLocation {skeletalMeshComp->GetSocketLocation(socketEnd)};
	//FQuat socketShapeRotation {skeletalMeshComp->GetSocketQuaternion(socketRotation)};
	FQuat boneRotation {skeletalMeshComp->GetBoneQuaternion(boneRot)};

	float socketShapeHeight {static_cast<float>(FVector::Distance(socketStartLocation, socketEndLocation))};
	FVector socketBoxHalfExtent {socketBoxLength, socketBoxLength, socketShapeHeight};
	socketBoxHalfExtent /= 2;

	FCollisionShape box {FCollisionShape::MakeBox(socketBoxHalfExtent)};
	FCollisionQueryParams ignoreParams {FName {TEXT("Ignore Collision Parameters")}, false, ownerRef};

	bool targetFound = GetWorld()->SweepMultiByChannel(outHits, socketStartLocation, socketEndLocation, boneRotation, ECollisionChannel::ECC_GameTraceChannel1, box, ignoreParams);

	if (debugModeEnabled)
	{
		FVector centerPoint {UKismetMathLibrary::VLerp(socketStartLocation, socketEndLocation, 0.5f)};
		UKismetSystemLibrary::DrawDebugBox(GetWorld(), centerPoint, box.GetExtent(), targetFound ? FColor::Green : FColor::Red, boneRotation.Rotator(), 0.1f, 1.0f);
	}
}

void UTraceComponent::HandleDamage(TArray<FHitResult> &outHits)
{
	float characterDamage {0.0f};
	IFighter* fighterRef {Cast<IFighter>(ownerRef)};

	if (fighterRef == nullptr) {return;}
	characterDamage = fighterRef->GetDamage();

	FDamageEvent targetAttackedEvent;
	for (const FHitResult& hitResult : outHits)
	{
		AActor* targetActor {hitResult.GetActor()};
		if (actorsToIgnore.Contains(targetActor)) {continue;}
		targetActor->TakeDamage(characterDamage, targetAttackedEvent, ownerRef->GetInstigatorController(), ownerRef);
		actorsToIgnore.AddUnique(targetActor);
	}
}
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
void UTraceComponent::HandleResetAttack()
{
	actorsToIgnore.Empty();
}
/************************************Public Functions************************************/


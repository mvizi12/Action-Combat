// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\MainPlayerInterface.h"

// Sets default values for this component's properties
UPlayerActionsComponent::UPlayerActionsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	characterRef = GetOwner<ACharacter>();
	movementComp = characterRef->GetCharacterMovement();

	if (!characterRef->Implements<UMainPlayerInterface>()) {return;}
	iPlayerRef = Cast<IMainPlayerInterface>(characterRef);
	
}


// Called every frame
void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
void UPlayerActionsComponent::StartRun()
{
	if (iPlayerRef == nullptr || !iPlayerRef->HasEnoughStamina(staminaCostRun))
	{
		StopRun();
		return;
	}
	if (movementComp->Velocity.Equals(FVector::ZeroVector, 1)) {return;}

	movementComp->MaxWalkSpeed = runSpeed;
	OnRunDelegate.Broadcast(staminaCostRun);
}

void UPlayerActionsComponent::StopRun()
{
	movementComp->MaxWalkSpeed = walkSpeed;
}
/************************************Public Functions************************************/

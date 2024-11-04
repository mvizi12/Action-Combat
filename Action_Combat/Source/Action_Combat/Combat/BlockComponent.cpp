// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockComponent.h"
#include "GameFramework/Character.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\MainPlayerInterface.h"

// Sets default values for this component's properties
UBlockComponent::UBlockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBlockComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBlockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
bool UBlockComponent::Check(AActor *opponent)
{
	//True = Can't block damage
	//False = Can block damage
	//Only going to block the attack if the player and enemy are facing each other
	//Use a "Dot Product" to determine if they're facing each other

	ACharacter* characterRef {GetOwner<ACharacter>()};
	if (!characterRef->Implements<UMainPlayerInterface>()) {return true;}
	IMainPlayerInterface* playerRef {Cast<IMainPlayerInterface>(characterRef)};

	FVector opponentForward {opponent->GetActorForwardVector()};
	FVector playerForward {characterRef->GetActorForwardVector()};

	//double dotProduct = opponentForward.Dot(playerForward);
	double dotProduct {FVector::DotProduct(opponentForward, playerForward)}; //If negative, actors are facing each other and vice versa
	if (dotProduct > 0 || !playerRef->HasEnoughStamina(staminaCost)) {return true;}

	OnBlockDelegate.Broadcast(staminaCost);
	
	return false;
}
/************************************Public Functions************************************/

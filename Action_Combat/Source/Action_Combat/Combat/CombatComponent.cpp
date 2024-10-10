// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\MainPlayerInterface.h"

UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	ownerRef = GetOwner<ACharacter>();
	
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
void UCombatComponent::ComboAttack()
{
	//If the owner is the main player, but doesn't have enough stamina to attack
	if (ownerRef->Implements<UMainPlayerInterface>())
	{
		IMainPlayerInterface* iOwnerRef {Cast<IMainPlayerInterface>(ownerRef)};

		if (iOwnerRef && !iOwnerRef->HasEnoughStamina(staminaCost)) {return;}
	}

	if (!canAttack) {return;} //"canAttack" is modified by an animation notify

	canAttack = false;

	ownerRef->PlayAnimMontage(meleeMontages[comboCounter]);
	++comboCounter;
	int maxCombo {meleeMontages.Num()};
	comboCounter = UKismetMathLibrary::Wrap(comboCounter, -1, maxCombo - 1);
	OnAttackPerformedDelegate.Broadcast(staminaCost);

}

/************************************Protected Functions************************************/

/************************************Public Functions************************************/
void UCombatComponent::HandleResetAttack()
{
	canAttack = true;
}

void UCombatComponent::ResetCombo()
{
	comboCounter = 0;
}

/************************************Public Functions************************************/


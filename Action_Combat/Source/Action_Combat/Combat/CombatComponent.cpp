// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

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
	if (!IsValid(ownerRef) || !canAttack) {return;}

	canAttack = false;

	ownerRef->PlayAnimMontage(meleeMontages[comboCounter]);
	++comboCounter;
	int maxCombo {meleeMontages.Num()};
	comboCounter = UKismetMathLibrary::Wrap(comboCounter, -1, maxCombo - 1);

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


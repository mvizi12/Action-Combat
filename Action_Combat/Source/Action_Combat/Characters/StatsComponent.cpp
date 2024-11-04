// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\Fighter.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
void UStatsComponent::EnableStaminaRegen()
{
	canRegenStamina = true;
}

float UStatsComponent::GetStatPercentage(EStat current, EStat max) const
{
    return stats[current] / stats[max];
}
/************************************Protected Functions************************************/

/************************************Public Functions************************************/

void UStatsComponent::ReduceHealth(float damage, AActor* opponent)
{
	if (EStat::Health <= 0) {return;}

	IFighter* fighterRef {GetOwner<IFighter>()};

	if (!fighterRef->CanTakeDamage(opponent)) {return;} //If false, can't damage the actor because they're blocking

	stats[EStat::Health] -= damage;
	stats[EStat::Health] = UKismetMathLibrary::FClamp(stats[EStat::Health], 0, stats[EStat::MaxHealth]);

	OnHealthPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Health, EStat::MaxHealth));

	if (stats[EStat::Health] <= 0) {OnZeroHealthUpdateDelegate.Broadcast();} //If health hits zero
}

void UStatsComponent::ReduceStamina(float amount)
{
	stats[EStat::Stamina] -= amount;
	stats[EStat::Stamina] = UKismetMathLibrary::FClamp(stats[EStat::Stamina], 0, stats[EStat::MaxStamina]);

	canRegenStamina = false;

	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Stamina, EStat::MaxStamina));
	//0 - Because we don't need to worry about resuming this function if it's been interrupted
	//100 - A unique id
	FLatentActionInfo staminaRegenInfo {0, 100, TEXT("EnableStaminaRegen"), this};
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), staminaRegenDelay, staminaRegenInfo);
}

void UStatsComponent::RegenStamina()
{
	if (!canRegenStamina) {return;}

	stats[EStat::Stamina] = UKismetMathLibrary::FInterpTo_Constant(stats[EStat::Stamina],
	stats[EStat::MaxStamina], GetWorld()->DeltaTimeSeconds, staminaRegenRate);

	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(EStat::Stamina, EStat::MaxStamina));
}

/************************************Public Functions************************************/

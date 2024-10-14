// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyProjectileComponent.h"

// Sets default values for this component's properties
UEnemyProjectileComponent::UEnemyProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UEnemyProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
void UEnemyProjectileComponent::SpawnProjectile(FName componentName, TSubclassOf<AActor> projectileClass)
{
	USceneComponent* spawnPointComp {Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(componentName))};
	
	//Returns the location of the component in the world, NOT relative to its owning actor
	FVector spawnLocation {spawnPointComp->GetComponentLocation()};
	GetWorld()->SpawnActor(projectileClass, &spawnLocation);
}
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
/************************************Public Functions************************************/


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API UEnemyProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/**
	* Spawn a projectile from the enemy
	* @param componentName Name of the component where the Projectile will spawn
	* @param projectileClass Projectile to spawn
	*/
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(FName componentName, TSubclassOf<AActor> projectileClass);

public:
	UEnemyProjectileComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};

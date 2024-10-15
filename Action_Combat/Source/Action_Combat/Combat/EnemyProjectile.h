// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class ACTION_COMBAT_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	float damage {10.0f};

	UPROPERTY(EditAnywhere)
	float lifeTime {0.5f};

	UFUNCTION()
	void DestroyProjectile();

	UPROPERTY(EditAnywhere)
	UParticleSystem* hitTemplate;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* otherActor);

public:	
	AEnemyProjectile();
	virtual void Tick(float DeltaTime) override;

};

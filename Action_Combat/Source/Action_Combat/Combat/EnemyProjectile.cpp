// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}

void AEnemyProjectile::HandleBeginOverlap(AActor *otherActor)
{
	APawn* pawnRef {Cast<APawn>(otherActor)};

	if (!pawnRef->IsPlayerControlled()) {return;}

	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(hitTemplate);
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();
	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FDamageEvent projectileAttackEvent;
	pawnRef->TakeDamage(damage, projectileAttackEvent, pawnRef->GetController(), this);

	FTimerHandle projectileDeathTimerHandle {};
	GetWorldTimerManager().SetTimer(projectileDeathTimerHandle, this, &AEnemyProjectile::DestroyProjectile, lifeTime);
}
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
/************************************Public Functions************************************/


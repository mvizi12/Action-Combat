// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Combat\CombatComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\StatsComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\MainPlayer.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\MainPlayerInterface.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	combatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	statsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	controllerRef = GetController<AAIController>();
	blackBoardComp = controllerRef->GetBlackboardComponent();
	ChangeState(initialState);

	GetWorld()->GetFirstPlayerController()->GetPawn<AMainPlayer>()->statsComponent->OnZeroHealthUpdateDelegate.AddDynamic(this, &ABoss::HandlePlayerDeath);
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
void ABoss::ChangeState(EEnemyState newState)
{
	blackBoardComp->SetValueAsEnum(TEXT("currentState"), newState);
}

void ABoss::Attack()
{
	combatComponent->RandomAttack();
}

float ABoss::GetAnimationDuration()
{
	return combatComponent->animationDuration;
}

float ABoss::GetDamage()
{
    return statsComponent->stats[EStat::Strength];
}

float ABoss::GetMeleeRange()
{
    return statsComponent->stats[EStat::MeleeRange];
}

void ABoss::HandleDeath()
{
	/*******************Play death animation, stop the AI's brain, and disable************************/
	ChangeState(EEnemyState::Dead);
	float duration {PlayAnimMontage(deathAnimMontage)};
	controllerRef->GetBrainComponent()->StopLogic("Defeated");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	/*******************Play death animation and stop the AI's brain************************/

	FTimerHandle destroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(destroyTimerHandle, this, &ABoss::FinishDeathAnim, duration, false);
	
	/***************End the player's lock on to this enemy if they're locked on to them*******************/
	IMainPlayerInterface* playerRef {GetWorld()->GetFirstPlayerController()->GetPawn<IMainPlayerInterface>()};
	if (!playerRef) {return;}
	playerRef->EndLockOnWithActor(this);
	/***************End the player's lock on to this enemy if they're locked on to them*******************/
}

void ABoss::HandlePlayerDeath()
{
	ChangeState(EEnemyState::Victory);
}

void ABoss::FinishDeathAnim()
{
	Destroy();
}
/************************************Public Functions************************************/

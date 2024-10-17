// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\StatsComponent.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	statsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	blackBoardComp = GetController<AAIController>()->GetBlackboardComponent();
	ChangeState(initialState);
	
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
float ABoss::GetDamage()
{
    return statsComponent->stats[EStat::Strength];
}
/************************************Public Functions************************************/

// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Combat\BlockComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Combat\CombatComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\EStat.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Combat\LockOnOffComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\PlayerActionsComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\StatsComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Combat\TraceComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Animation\MainPlayerAnimInstance.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Doing this here because "BeginPlay()" only runs when the game starts
	//However, we want these components to be avilable during development
	blockComponent = CreateDefaultSubobject<UBlockComponent>(TEXT("Block"));
	combatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	lockOnOffComponent = CreateDefaultSubobject<ULockOnOffComponent>(TEXT("LockOnOff"));
	playerActionsComponent = CreateDefaultSubobject<UPlayerActionsComponent>(TEXT("PlayerActions"));
	statsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	traceComponent = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace"));

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerAnim = Cast<UMainPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/************************************Private Functions************************************/
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
bool AMainPlayer::CanTakeDamage(AActor *opponent)
{
	if (playerAnim->isBlocking)
	{
		return blockComponent->Check(opponent);
	}
    return true;
}

void AMainPlayer::EndLockOnWithActor(AActor *actorRef)
{
	if (!IsValid(lockOnOffComponent->currentTargetActor) || lockOnOffComponent->currentTargetActor != actorRef) {return;}

	lockOnOffComponent->LockOff();
}

float AMainPlayer::GetDamage()
{
    return statsComponent->stats[EStat::Strength];
}

void AMainPlayer::HandleDeath()
{
	PlayAnimMontage(deathAnimMontage);
	DisableInput(GetController<APlayerController>());
}

bool AMainPlayer::HasEnoughStamina(float staminaCost)
{
    return statsComponent->stats[EStat::Stamina] >= staminaCost;
}

void AMainPlayer::PlayHurtAnimation()
{
	PlayAnimMontage(hurtAnimMontage);
}
/************************************Public Functions************************************/
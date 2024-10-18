// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h" //Need for the "MoveTo" function for some reason
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Animation\BossAnimInstance.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\EEnemyState.h"

UBTT_ChargeAttack::UBTT_ChargeAttack()
{
    bNotifyTick = true;
    MoveCompletedDelegate.BindUFunction(this, "HandleMoveCompleted");
}

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    bool isReadyToCharge {OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("isReadyToCharge?"))};

    if (isReadyToCharge)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("isReadyToCharge?"), false);
        ChargeAtPlayer();
    }

    if (!isFinished) {return;}

    //The whole point of the charge state is to get close to the player
    //So that means the boss will transition to the melee state after charging
    OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("currentState"), EEnemyState::Melee);
    controllerRef->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    controllerRef = OwnerComp.GetAIOwner();
    characterRef = controllerRef->GetCharacter();
    bossAnim = Cast<UBossAnimInstance>(characterRef->GetMesh()->GetAnimInstance());
    bossAnim->isCharing = true;

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("isReadyToCharge?"), false); //Boss won't move before their run animation plays

    isFinished = false;

    return EBTNodeResult::InProgress;
}

/************************************Private Functions************************************/
void UBTT_ChargeAttack::ChargeAtPlayer()
{
    APawn* playerRef {GetWorld()->GetFirstPlayerController()->GetPawn()};
    FVector playerLocation {playerRef->GetActorLocation()};

    FAIMoveRequest moveRequest {playerLocation};
    moveRequest.SetUsePathfinding(true);
    moveRequest.SetAcceptanceRadius(acceptanceRadius);

    controllerRef->MoveTo(moveRequest);
    controllerRef->SetFocus(playerRef);
    controllerRef->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate);

    originalSpeed = characterRef->GetCharacterMovement()->MaxWalkSpeed;
    characterRef->GetCharacterMovement()->MaxWalkSpeed = chargeSpeed;
}
/************************************Private Functions************************************/

/************************************Protected Functions************************************/
void UBTT_ChargeAttack::HandleMoveCompleted()
{
    bossAnim->isCharing = false;

    FTimerHandle attackTimerHandle;
    characterRef->GetWorldTimerManager().SetTimer(attackTimerHandle, this, &UBTT_ChargeAttack::FinishAttackTask, 1.0f, false);
    
    characterRef->GetCharacterMovement()->MaxWalkSpeed = originalSpeed;
}

void UBTT_ChargeAttack::FinishAttackTask()
{
    isFinished = true;
}
/************************************Protected Functions************************************/

/************************************Public Functions************************************/
/************************************Public Functions************************************/
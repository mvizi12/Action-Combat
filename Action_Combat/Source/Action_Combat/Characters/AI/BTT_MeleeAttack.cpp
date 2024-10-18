// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_MeleeAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h" //Need for the "MoveTo" function for some reason

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
    bNotifyTick = true;
    MoveCompletedDelegate.BindUFunction(this, "HandleMoveCompleted");
}

void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    if (!isFinished) {return;}
    controllerRef->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    isFinished = false;
    controllerRef = OwnerComp.GetAIOwner();
    float distanceToPlayer = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("distanceToPlayer"));
    if (distanceToPlayer > attackRadius)
    {
        APawn* playerRef {GetWorld()->GetFirstPlayerController()->GetPawn()};
        FAIMoveRequest moveRequest {playerRef};
        moveRequest.SetUsePathfinding(true);
        moveRequest.SetAcceptanceRadius(acceptanceRadius);

        controllerRef->MoveTo(moveRequest);
        controllerRef->SetFocus(playerRef);
        controllerRef->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate);
    }

    return EBTNodeResult::InProgress;
}

void UBTT_MeleeAttack::HandleMoveCompleted()
{
    isFinished = true;
}
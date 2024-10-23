// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_MeleeAttack.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h" //Need for the "MoveTo" function for some reason
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\Fighter.h"

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
    bNotifyTick = true;
    FinishAttackDelegate.BindUFunction(this, "FinishAttackTask");
}

void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    if (!isFinished) {return;}
    controllerRef->ReceiveMoveCompleted.Remove(FinishAttackDelegate);
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    isFinished = false;
    controllerRef = OwnerComp.GetAIOwner();
    float distanceToPlayer {OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("distanceToPlayer"))};
    UE_LOG(LogTemp, Warning, TEXT("BTT_MeleeAttack: Distance to player = %f"), distanceToPlayer);
    if (distanceToPlayer > attackRadius)
    {
        APawn* playerRef {GetWorld()->GetFirstPlayerController()->GetPawn()};
        FAIMoveRequest moveRequest {playerRef};
        moveRequest.SetUsePathfinding(true);
        moveRequest.SetAcceptanceRadius(acceptanceRadius);

        controllerRef->MoveTo(moveRequest);
        controllerRef->SetFocus(playerRef);
        controllerRef->ReceiveMoveCompleted.AddUnique(FinishAttackDelegate);
    }
    else
    {
        IFighter* iFighterRef {Cast<IFighter>(controllerRef->GetCharacter())};
        if (iFighterRef == nullptr) {return EBTNodeResult::Aborted;}
        iFighterRef->Attack();

        FTimerHandle AttackTimerHandle;
        controllerRef->GetCharacter()->GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &UBTT_MeleeAttack::FinishAttackTask, iFighterRef->GetAnimationDuration(), false);
    }

    return EBTNodeResult::InProgress;
}

void UBTT_MeleeAttack::FinishAttackTask()
{
    isFinished = true;
}
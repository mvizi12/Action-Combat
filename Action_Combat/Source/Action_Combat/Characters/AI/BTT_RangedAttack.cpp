// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\EEnemyState.h"

EBTNodeResult::Type UBTT_RangedAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    ACharacter* ownerCharacterRef {OwnerComp.GetAIOwner()->GetPawn<ACharacter>()}; //Method 1
    //ACharacter* ownerCharacterRef {OwnerComp.GetAIOwner()->GetCharacter()}; Method 2
    if (!IsValid(ownerCharacterRef)) {return EBTNodeResult::Failed;}

    float distanceToPlayer {OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("distanceToPlayer"))};
    if (distanceToPlayer <= meleeAttackRange) //If enemy is in melee attack range, switch to melee state & abort this task
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("currentState"), EEnemyState::Melee);
        AbortTask(OwnerComp, NodeMemory); //Cleans up any memory related to this task
        return EBTNodeResult::Aborted; //Actually aborts the task
    }

    ownerCharacterRef->PlayAnimMontage(rangedAttackMontage);

    double randomValue {UKismetMathLibrary::RandomFloat()};

    if (randomValue > threshold)
    {
        threshold = 0.9;
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("currentState"), EEnemyState::Charge);
    }
    else {threshold -= 0.1;}
    return EBTNodeResult::Succeeded;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\EEnemyState.h"

EBTNodeResult::Type UBTT_RangedAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    ACharacter* ownerCharacterRef {OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};
    if (!IsValid(ownerCharacterRef)) {return EBTNodeResult::Failed;}
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
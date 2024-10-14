// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UBTT_RangedAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    ACharacter* ownerCharacterRef {OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};
    if (!IsValid(ownerCharacterRef)) {return EBTNodeResult::Failed;}
    ownerCharacterRef->PlayAnimMontage(rangedAttackMontage);
    return EBTNodeResult::Succeeded;
}
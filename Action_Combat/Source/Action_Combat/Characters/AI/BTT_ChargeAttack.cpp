// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Animation\BossAnimInstance.h"

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    controllerRef = OwnerComp.GetAIOwner();
    characterRef = controllerRef->GetCharacter();
    bossAnim = Cast<UBossAnimInstance>(characterRef->GetMesh()->GetAnimInstance());
    bossAnim->isCharing = true;
    return EBTNodeResult::InProgress;
}

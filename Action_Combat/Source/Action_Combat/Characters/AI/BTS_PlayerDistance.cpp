// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_PlayerDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    FVector ownerLocation {OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()};
    FVector playerLocation {GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()};

    float distance {static_cast<float>(FVector::Distance(ownerLocation, playerLocation))};
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("distanceToPlayer"), distance);
}

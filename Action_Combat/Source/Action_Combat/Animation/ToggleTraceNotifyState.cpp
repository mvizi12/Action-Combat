// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleTraceNotifyState.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Combat\TraceComponent.h"

void UToggleTraceNotifyState::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration, const FAnimNotifyEventReference& eventReference)
{
    UTraceComponent* traceComponent {meshComp->GetOwner()->FindComponentByClass<UTraceComponent>()};

    if (!IsValid(traceComponent)) {return;}

    traceComponent->isAttacking = true;
}

void UToggleTraceNotifyState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
    UTraceComponent* traceComponent {meshComp->GetOwner()->FindComponentByClass<UTraceComponent>()};

    if (!IsValid(traceComponent)) {return;}

    traceComponent->isAttacking = false;
}


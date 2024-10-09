// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleAnimNotifyState.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Combat\TraceComponent.h"

void UToggleAnimNotifyState::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration, const FAnimNotifyEventReference& eventReference)
{
	UTraceComponent* traceComp {meshComp->GetOwner()->FindComponentByClass<UTraceComponent>()};

	if (!IsValid(traceComp)) { return; }

	traceComp->isAttacking = true;

}

void UToggleAnimNotifyState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
	UTraceComponent* traceComp {meshComp->GetOwner()->FindComponentByClass<UTraceComponent>()};

	if (!IsValid(traceComp)) { return; }

	traceComp->isAttacking = false;
}

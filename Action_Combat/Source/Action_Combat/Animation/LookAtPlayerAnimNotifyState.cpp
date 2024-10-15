// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtPlayerAnimNotifyState.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Characters\LookAtPlayerComponent.h"

void ULookAtPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, float totalDuration, const FAnimNotifyEventReference& eventReference)
{
    AActor* ownerRef {meshComp->GetOwner()};
    if (!IsValid(ownerRef)) {return;}
    ULookAtPlayerComponent* lookAtPlayerComp {ownerRef->FindComponentByClass<ULookAtPlayerComponent>()};
    if (!IsValid(lookAtPlayerComp)) {return;}

    lookAtPlayerComp->canRotate = true;
}

void ULookAtPlayerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation, const FAnimNotifyEventReference& eventReference)
{
    AActor* ownerRef {meshComp->GetOwner()};
    if (!IsValid(ownerRef)) {return;}
    ULookAtPlayerComponent* lookAtPlayerComp {ownerRef->FindComponentByClass<ULookAtPlayerComponent>()};
    if (!IsValid(lookAtPlayerComp)) {return;}

    lookAtPlayerComp->canRotate = false;
}

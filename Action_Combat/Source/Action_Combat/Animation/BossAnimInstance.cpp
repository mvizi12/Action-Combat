// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAnimInstance.h"

/*PRIVATE FUNCTIONS*/
void UBossAnimInstance::UpdateVelocity()
{
    if (!IsValid(bossPawn)) {return;}

    currentVeloctiy = bossPawn->GetVelocity();
}

/*PROTECTED FUNCTIONS*/
void UBossAnimInstance::UpdateBossPawn()
{
    bossPawn = TryGetPawnOwner();
}

void UBossAnimInstance::UpdateCurrentSpeed()
{
    if (!IsValid(bossPawn)) {return;}

    UpdateVelocity();
    currentSpeed = static_cast<float>(currentVeloctiy.Length());
}
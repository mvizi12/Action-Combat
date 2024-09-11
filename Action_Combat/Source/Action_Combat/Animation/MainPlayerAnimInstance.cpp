// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerAnimInstance.h"

/*PRIVATE FUNCTIONS*/
void UMainPlayerAnimInstance::UpdateVelocity()
{
    if (!IsValid(playerPawn)) {return;}

    currentVeloctiy = playerPawn->GetVelocity();
}


/*PROTECTED FUNCTIONS*/
void UMainPlayerAnimInstance::UpdatePlayerPawn()
{
    playerPawn = TryGetPawnOwner();
}

void UMainPlayerAnimInstance::UpdateCurrentAngle()
{
    if (!IsValid(playerPawn)) {return;}

    UpdateVelocity();
    FRotator currentRotation = playerPawn->GetActorRotation();
    currentAngle = CalculateDirection(currentVeloctiy, currentRotation);
}

void UMainPlayerAnimInstance::UpdateCurrentSpeed()
{
    if (!IsValid(playerPawn)) {return;}

    UpdateVelocity();
    currentSpeed = static_cast<float>(currentVeloctiy.Length());
}

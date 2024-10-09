// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayerInterface.h"
#include "Interfaces/Fighter.h"
#include "MainPlayer.generated.h"

UCLASS()
class ACTION_COMBAT_API AMainPlayer : public ACharacter, public IMainPlayerInterface, public IFighter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "How much damage the player's attacks will do"))
	int damage;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AMainPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C:\Users\mvizi\Documents\Unreal Projects\Action-Combat\Action_Combat\Source\Action_Combat\Interfaces\Enemy.h"
#include "EEnemyState.h"
#include "Boss.generated.h"

UCLASS()
class ACTION_COMBAT_API ABoss : public ACharacter, public IEnemy
{
	GENERATED_BODY()

private:
	class UBlackboardComponent* blackBoardComp;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> initialState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* statsComponent;

	ABoss();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeState(EEnemyState newState);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_COMBAT_API UBTT_ChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	private:
		AAIController* controllerRef;
		ACharacter* characterRef;
		class UBossAnimInstance* bossAnim;

		FScriptDelegate MoveCompletedDelegate; //Special type for storing a function in a variable

		bool isFinished;

		float originalSpeed;

		void ChargeAtPlayer();
	
	protected:
		UPROPERTY(EditAnywhere)
		float chargeSpeed {2000.0f};

		UPROPERTY(EditAnywhere)
		float acceptanceRadius {100.0f};

		virtual void TickTask(UBehaviorTreeComponent&, uint8*, float) override;

		UFUNCTION()
		void HandleMoveCompleted();

		UFUNCTION()
		void FinishAttackTask();

	public:
		UBTT_ChargeAttack();
		virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent&, uint8*) override;
	
};

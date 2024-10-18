// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_COMBAT_API UBTT_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	private:
		AAIController* controllerRef;
		FScriptDelegate MoveCompletedDelegate; //Special type for storing a function in a variable

		bool isFinished;

	protected:
		UPROPERTY(EditAnywhere)
		float attackRadius {200.0f};

		UPROPERTY(EditAnywhere, meta = (ToolTip = "Make sure this is less than the attack radius"))
		float acceptanceRadius {100.0f};

		virtual void TickTask(UBehaviorTreeComponent&, uint8*, float) override;

		UFUNCTION()
		void HandleMoveCompleted();

	public:
		UBTT_MeleeAttack();
		virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent&, uint8*) override;
	
};

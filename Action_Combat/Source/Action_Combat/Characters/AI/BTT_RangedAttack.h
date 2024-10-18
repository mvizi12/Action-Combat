// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_COMBAT_API UBTT_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

	protected:
		UPROPERTY(EditAnywhere)
		UAnimMontage* rangedAttackMontage;

		UPROPERTY(EditAnywhere)
		double threshold {0.9};

		UPROPERTY(EditAnywhere, meta = (ToolTip = "Max range allowed for the enemy to perform melee attacks"))
		float meleeAttackRange {1250.0f};

	public:
		virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent&, uint8*) override;
	
};

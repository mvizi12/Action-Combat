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

	public:
		virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent&, uint8*) override;
	
};

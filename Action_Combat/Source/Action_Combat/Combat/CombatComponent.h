// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	ACharacter* ownerRef;

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UAnimMontage*> meleeMontages;

	UPROPERTY(VisibleAnywhere)
	int comboCounter {0};

	UPROPERTY(VisibleAnywhere)
	bool canAttack {true};
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ComboAttack();

public:
	UCombatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) //Public so animations can call it
	void HandleResetAttack();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();
		
};

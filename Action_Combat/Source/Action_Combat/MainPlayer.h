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

private:
	class UMainPlayerAnimInstance* playerAnim;

protected:
	UPROPERTY(EditAnywhere)
	UAnimMontage* deathAnimMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* hurtAnimMontage;

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlockComponent* blockComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* combatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULockOnOffComponent* lockOnOffComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerActionsComponent* playerActionsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatsComponent* statsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTraceComponent* traceComponent;

	AMainPlayer();

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool CanTakeDamage(AActor* opponent) override;

	virtual void EndLockOnWithActor(AActor* actorRef) override;

	virtual float GetDamage() override;

	UFUNCTION(BlueprintCallable)
	virtual void HandleDeath() override;

	virtual bool HasEnoughStamina(float) override;

	UFUNCTION(BlueprintCallable)
	void PlayHurtAnimation();

};

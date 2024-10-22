// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FTraceSockets.h"
#include "TraceComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FOnReportDamageSignature, UTraceComponent, OnReportDamageDelegate, float, damage, AActor*, actor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AActor* ownerRef; //Reference to the owner of this component

	USkeletalMeshComponent* skeletalMeshComp;

	TArray<AActor*> actorsToIgnore; //To prevent from damaing the same enemy multiple times from 1 attack

	void GetReferences();

	void WeaponTrace(TArray<FHitResult>&);

	void HandleDamage(TArray<FHitResult>&);

protected:
	UPROPERTY(EditAnywhere)
	bool debugModeEnabled;

	UPROPERTY(EditAnywhere)
	TArray<FTraceSockets> sockets;

	UPROPERTY(EditDefaultsOnly)
	float socketBoxLength;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnReportDamageSignature OnReportDamageDelegate;

	UPROPERTY(VisibleAnywhere)
	bool isAttacking {false};
	
	// Sets default values for this component's properties
	UTraceComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

		
};

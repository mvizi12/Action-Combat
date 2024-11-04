// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnBlockSignature, UBlockComponent, OnBlockDelegate, float, staminaCost);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API UBlockComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	float staminaCost {10.0f};

	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnBlockSignature OnBlockDelegate;
	
	UBlockComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Check(AActor* opponent);
		
};

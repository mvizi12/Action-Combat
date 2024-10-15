// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LookAtPlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API ULookAtPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class ABoss* ownerRef;

protected:
	UPROPERTY(EditAnywhere)
	float rotationSpeed {400.0f};

	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	bool canRotate {false};
	
	ULookAtPlayerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

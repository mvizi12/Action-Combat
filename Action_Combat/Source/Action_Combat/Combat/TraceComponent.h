// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTION_COMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AActor* ownerRef; //Reference to the owner of this component

	USkeletalMeshComponent* skeletalMeshComp;

	void GetReferences();

protected:
	UPROPERTY(EditAnywhere)
	bool debugModeEnabled;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Name of the socket where the weapon trace should begin"))
	FName socketStart;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Name of the socket where the weapon trace should end"))
	FName socketEnd;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Rotation of the weapon trace"))
	FName socketRotation;

	UPROPERTY(EditDefaultsOnly)
	float socketBoxLength;

	UPROPERTY(EditDefaultsOnly)
	float socketCapsauleRadius;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UTraceComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

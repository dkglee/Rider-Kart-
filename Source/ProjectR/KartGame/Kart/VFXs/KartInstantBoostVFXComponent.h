// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KartBasicBoosterVFXComponent.h"
#include "KartInstantBoostVFXComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTR_API UKartInstantBoostVFXComponent : public UKartBasicBoosterVFXComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKartInstantBoostVFXComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	virtual void ServerRPC_ActivateBoosterVFX_Implementation(float BoosterTime) override;
	virtual void MulticastRPC_ActivateBoosterVFX_Implementation(float BoosterTime) override;

	virtual void ServerRPC_DeactivateBoosterVFX_Implementation() override;
	virtual void MulticastRPC_DeactivateBoosterVFX_Implementation() override;

	virtual void OnBoosterActivated(float BoosterTime) override;
	virtual void OnBoosterDeactivated() override;

private:
	UPROPERTY()
	FVector InstantBoostLength{100, 0, 0};
};

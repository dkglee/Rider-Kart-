// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KartSuspensionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTR_API UKartSuspensionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKartSuspensionComponent();

	bool ProcessSuspension(FVector& LineLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

private:
	UPROPERTY()
	class AKart* Kart = nullptr;
	UPROPERTY()
	class UBoxComponent* KartBody = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	float SpringStrength = 4000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	int SuspensionLength = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	float DamperScale = 1000.0f;
};

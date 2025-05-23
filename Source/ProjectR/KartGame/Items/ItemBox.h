﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTable/ItemTable.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

UCLASS()
class PROJECTR_API AItemBox : public AActor
{
	GENERATED_BODY()

public:
	AItemBox();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void InitComponents();

	UFUNCTION()
	void ItemBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UFUNCTION()
	void MakeRandomItem(class UItemInventoryComponent* ItemInventoryComponent, class AKart* player);

	UFUNCTION(Server, Reliable)
	void Server_MakeRandomItem(class UItemInventoryComponent* ItemInventoryComponent, class AKart* player);

	UFUNCTION(NetMulticast, Reliable)
	void NetMultiCast_MakeRandomItem(class UItemInventoryComponent* ItemInventoryComponent, const FItemTable Item);

	void ApplyRankBasedWeightAdjustments(TMap<int32, FItemTable>& ItemMapToAdjust, int32 PlayerRank);

	int32 CalculateTotalWeight(const TMap<int32, FItemTable>& ItemMapToCalculate);
	
	void RotateBody();
	
private:
	UPROPERTY()
	FTimerHandle ItemBoxRespawnTimerHandle;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class UBoxComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class UStaticMeshComponent* Mesh;
};

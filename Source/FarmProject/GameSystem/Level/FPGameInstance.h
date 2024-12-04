// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameSystem/Data/DataForm/BuildingDataCSV.h"
#include "GameSystem/Data/DataForm/SeedDataCSV.h"
#include "GameSystem/Data/DataForm/AnimalDataCSV.h"
#include "FPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UFPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFPGameInstance();

	void GameStart();
	void AddItemToInventory(TObjectPtr<class UItemDataBase> item);
	void EditItemCount(TObjectPtr<class UItemDataBase> item, int32 Num);

	void SaveGame();

	UFUNCTION()
	void TimeCheckTimer();

	void AddTimeCheckArray(TWeakObjectPtr<class UFieldItemData> Target);
	void RemoveTimeCheckArray(TWeakObjectPtr<class UFieldItemData> Target);

	FORCEINLINE TMap<int32, TObjectPtr<class UBuildingItemData>> GetBuildingArray() { return BuildingDataArray; }
	FORCEINLINE TMap<int32, TObjectPtr<class USeedDataBase>> GetSeedArray() { return SeedDataArray; }

public:
	TArray<TObjectPtr<class UBuildingItemData>> BuildingInventory;
	TArray<TObjectPtr<class USeedDataBase>> SeedInventory;

protected:
	UFUNCTION()
	void LoadBuildingCSVData();
	UFUNCTION()
	void LoadSeedCSVData();
	UFUNCTION()
	void LoadAnimalCSVData();

	void LoadInven();
	void LoadField();

protected:
	UPROPERTY()
	TArray<TObjectPtr<class UItemDataBase>> ItemInventory;

	//...

	UPROPERTY()
	TArray<TWeakObjectPtr<class UFieldItemData>> TimeCheckArray;

	FTimerHandle TimeCheckHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> SeedTable;
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, TObjectPtr<class USeedDataBase>>  SeedDataArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> BuildingTable;
	UPROPERTY(BlueprintReadOnly)
	TMap<int32, TObjectPtr<class UBuildingItemData>> BuildingDataArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<FAnimalDataCSV> AnimalDataArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UClickableComponent> ClickableComponentREF;

private:
	void SortItem(TObjectPtr<class UItemDataBase> item);
};

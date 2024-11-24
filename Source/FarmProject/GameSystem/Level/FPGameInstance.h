// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

	UFUNCTION()
	void TimeCheckTimer();

	void AddTimeCheckArray(TObjectPtr<class UFieldItemData> Target);
	void RemoveTimeCheckArray(TObjectPtr<class UFieldItemData> Target);
public:
	TArray<TObjectPtr<class UBuildingItemData>> BuildingInventory;
	TArray<TObjectPtr<class USeedDataBase>> SeedInventory;

protected:
	UPROPERTY()
	TArray<TObjectPtr<class UItemDataBase>> ItemInventory;

	//...

	UPROPERTY()
	TArray<TObjectPtr<class UFieldItemData>> TimeCheckArray;

	FTimerHandle TimeCheckHandle;




private:
	void SortItem(TObjectPtr<class UItemDataBase> item);
};

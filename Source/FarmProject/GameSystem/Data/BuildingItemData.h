// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "BuildingItemData.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API UBuildingItemData : public UItemDataBase
{
	GENERATED_BODY()
	
public:
	virtual void Copy(const UItemDataBase& Other) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UObject> BlueprintUI;
};

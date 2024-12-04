// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Data/BuildingItemData.h"

void UBuildingItemData::Copy(const UItemDataBase& Other)
{
	Super::Copy(Other);
	if (const UBuildingItemData* OtherWeapon = Cast<UBuildingItemData>(&Other))
	{
		BlueprintUI = OtherWeapon->BlueprintUI;
	}
}

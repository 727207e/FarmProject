// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Data/AnimalDataBase.h"

void UAnimalDataBase::Copy(const UItemDataBase& Other)
{
	Super::Copy(Other);
	if (const UAnimalDataBase* OtherWeapon = Cast<UAnimalDataBase>(&Other))
	{
	}
}

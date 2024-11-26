// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Data/ItemDataBase.h"

void UItemDataBase::Copy(const UItemDataBase& Other)
{
	Id = Other.Id;
	CurrentCount = Other.CurrentCount;
	MaxCount = Other.MaxCount;
	Image = Other.Image;
	Name = Other.Name;
	BlueprintObject = Other.BlueprintObject;

}

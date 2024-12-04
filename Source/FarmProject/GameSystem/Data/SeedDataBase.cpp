// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Data/SeedDataBase.h"

void USeedDataBase::Copy(const UItemDataBase& Other)
{
	Super::Copy(Other);
	if (const USeedDataBase* OtherWeapon = Cast<USeedDataBase>(&Other))
	{
		NeedMTime = OtherWeapon->NeedMTime;
		NeedLTime = OtherWeapon->NeedLTime;
		MStaticMesh = OtherWeapon->MStaticMesh;
		LStaticMesh = OtherWeapon->LStaticMesh;
	}
}

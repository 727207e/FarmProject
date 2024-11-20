// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/FPBuilding.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"

AFPBuilding::AFPBuilding()
{
}

void AFPBuilding::UpdateClickInfo()
{
	UClickableComponent* ClickComp = GetComponentByClass<UClickableComponent>();
	if (ClickComp == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("%s : Can't Get ClickableComp"), *__FUNCTION__);
		return;
	}
	else
	{
		ClickComp->OnClicked.BindUObject(this, &AFPBuilding::ShowBuildingUI);
	}
}

void AFPBuilding::ShowBuildingUI()
{
	UE_LOG(LogTemp, Error, TEXT("1"));
}

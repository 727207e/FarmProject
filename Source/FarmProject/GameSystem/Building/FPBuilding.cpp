// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/FPBuilding.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "Blueprint/UserWidget.h"

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
	if (BuildingUI == nullptr && BuildingUIClass != nullptr)
	{
		BuildingUI = CreateWidget<UUserWidget>(GetWorld(), BuildingUIClass);
		if (BuildingUI)
		{
			BuildingUI->AddToViewport();
			BuildingUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
	if (BuildingUI)
	{
		if (BuildingUI->IsVisible())
		{
			BuildingUI->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			BuildingUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

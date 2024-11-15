// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Building/FPEditBuildingUI.h"
#include "Components/Button.h"

#define LeftButtonUIName TEXT("LeftButton_UI")
#define RightButtonUIName TEXT("RightButton_UI")
#define GoInventoryButtonUIName TEXT("GoInventoryButton_UI")
#define MoveButtonUIName TEXT("MoveButton_UI")
#define CancelButtonUIName TEXT("CancelButton_UI")

UFPEditBuildingUI::UFPEditBuildingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPEditBuildingUI::ActiveEditBuildUI(class UClickableComponent* ClickableComponent)
{
	if (LeftButton == nullptr)
	{
		LeftButton = Cast<UButton>(GetWidgetFromName(LeftButtonUIName));
	}
	if (RightButton == nullptr)
	{
		RightButton = Cast<UButton>(GetWidgetFromName(RightButtonUIName));
	}
	if (GoInventoryButton == nullptr)
	{
		GoInventoryButton = Cast<UButton>(GetWidgetFromName(GoInventoryButtonUIName));
	}
	if (MoveButton == nullptr)
	{
		MoveButton = Cast<UButton>(GetWidgetFromName(MoveButtonUIName));
	}	
	if (CancelButton == nullptr)
	{
		CancelButton = Cast<UButton>(GetWidgetFromName(CancelButtonUIName));
	}

	CurTargetClickable = ClickableComponent;
	if (CurTargetClickable != nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("11"));
	}
}

void UFPEditBuildingUI::DeactiveEditBuildUI()
{
}

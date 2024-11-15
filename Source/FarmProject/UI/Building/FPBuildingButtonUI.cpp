// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Building/FPBuildingButtonUI.h"
#include "Components/Button.h"
#include "PaperSprite.h"
#include "Components/TextBlock.h"

#define BuildingButtonUIName TEXT("BuildingButton_UI")
#define CountTextUIName TEXT("CountText_UI")
#define BuildingNameTextUIName TEXT("BuildingNameText_UI")

UFPBuildingButtonUI::UFPBuildingButtonUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPBuildingButtonUI::ButtonInit(FBuildingInfo BuildingInfo)
{
	FindUI();

	FButtonStyle ButtonStyle = BuildingButton->WidgetStyle;
	FSlateBrush NormalBrush = ButtonStyle.Normal;
	FSlateBrush HoveredBrush = ButtonStyle.Hovered;
	FSlateBrush PressedBrush = ButtonStyle.Pressed;

	NormalBrush.SetResourceObject(BuildingInfo.Image);
	HoveredBrush.SetResourceObject(BuildingInfo.Image);
	PressedBrush.SetResourceObject(BuildingInfo.Image);

	ButtonStyle.Normal = NormalBrush;
	ButtonStyle.Hovered = HoveredBrush;
	ButtonStyle.Pressed = PressedBrush;

	BuildingButton->SetStyle(ButtonStyle);
	BuildingNameText->SetText(BuildingInfo.BuildingName);
	CountText->SetText(FText::AsNumber(BuildingInfo.BuildingCount));
}

void UFPBuildingButtonUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFPBuildingButtonUI::OnButtonClicked()
{
	bIsOn = !bIsOn;

	if (bIsOn)
	{
		if (OnBuildingButtonActive.IsBound())
		{
			OnBuildingButtonActive.Execute(*this);
		}
	}
	else
	{
		if (OnBuildingButtonDeactive.IsBound())
		{
			OnBuildingButtonDeactive.Execute(*this);
		}
	}
}

void UFPBuildingButtonUI::FindUI()
{
	BuildingButton = Cast<UButton>(GetWidgetFromName(BuildingButtonUIName));
	if (BuildingButton)
	{
		BuildingButton->OnClicked.AddDynamic(this, &UFPBuildingButtonUI::OnButtonClicked);
	}

	CountText = Cast<UTextBlock>(GetWidgetFromName(CountTextUIName));
	BuildingNameText = Cast<UTextBlock>(GetWidgetFromName(BuildingNameTextUIName));
}

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

void UFPBuildingButtonUI::ButtonInit(int32 CurrentCount, UTexture2D* Image, FText Name)
{
	FindUI();

	FButtonStyle ButtonStyle = BuildingButton->WidgetStyle;
	FSlateBrush NormalBrush = ButtonStyle.Normal;
	FSlateBrush HoveredBrush = ButtonStyle.Hovered;
	FSlateBrush PressedBrush = ButtonStyle.Pressed;

	NormalBrush.SetResourceObject(Image);
	HoveredBrush.SetResourceObject(Image);
	PressedBrush.SetResourceObject(Image);

	ButtonStyle.Normal = NormalBrush;
	ButtonStyle.Hovered = HoveredBrush;
	ButtonStyle.Pressed = PressedBrush;

	BuildingButton->SetStyle(ButtonStyle);
	BuildingNameText->SetText(Name);
	CountText->SetText(FText::AsNumber(CurrentCount));
}

void UFPBuildingButtonUI::DeactiveUI()
{
	bIsOn = false;
}

void UFPBuildingButtonUI::AddBuildingCount(int32 AddValue)
{
	FText CurrentText = CountText->GetText();
	int32 CurrentValue = FCString::Atoi(*CurrentText.ToString());
	int32 NewValue = CurrentValue + AddValue;

	CountText->SetText(FText::AsNumber(NewValue));
}

void UFPBuildingButtonUI::SetBuildingCount(int32 SetValue)
{
	CountText->SetText(FText::AsNumber(SetValue));
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
			OnBuildingButtonActive.Execute();
		}
	}
	else
	{
		if (OnBuildingButtonDeactive.IsBound())
		{
			OnBuildingButtonDeactive.Execute();
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Building/FPBuildingButtonUI.h"
#include "Components/Button.h"
#include "PaperSprite.h"
#include "Components/TextBlock.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Level/MainFPLevelScript.h"
#include "UI/FPHud.h"
#include "UI/Setting/FPStylingUI.h"

#define BuildingButtonUIName TEXT("BuildingButton_UI")
#define CountTextUIName TEXT("CountText_UI")
#define BuildingNameTextUIName TEXT("BuildingNameText_UI")

UFPBuildingButtonUI::UFPBuildingButtonUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPBuildingButtonUI::ButtonInit(const TObjectPtr<UBuildingItemData> Data)
{
	if (Data == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Data is null"), __func__);
		return;
	}

	BuildingData = Data;
	
	FindUI();

	FButtonStyle ButtonStyle = BuildingButton->GetStyle();
	FSlateBrush NormalBrush = ButtonStyle.Normal;
	FSlateBrush HoveredBrush = ButtonStyle.Hovered;
	FSlateBrush PressedBrush = ButtonStyle.Pressed;

	NormalBrush.SetResourceObject(BuildingData->Image);
	HoveredBrush.SetResourceObject(BuildingData->Image);
	PressedBrush.SetResourceObject(BuildingData->Image);

	ButtonStyle.Normal = NormalBrush;
	ButtonStyle.Hovered = HoveredBrush;
	ButtonStyle.Pressed = PressedBrush;

	BuildingButton->SetStyle(ButtonStyle);
	BuildingNameText->SetText(BuildingData->Name);
	CountText->SetText(FText::AsNumber(BuildingData->CurrentCount));
	
	OnBuildingButtonActive.BindUObject(this, &ThisClass::OnButtonActive);
	OnBuildingButtonDeactive.BindUObject(this, &ThisClass::OnButtonDeactive);
}

void UFPBuildingButtonUI::DeactiveUI()
{
	OnBuildingButtonActive.Unbind();
	OnBuildingButtonDeactive.Unbind();
	
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

void UFPBuildingButtonUI::OnButtonActive()
{
	if (BuildingData.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : No BuildingData"), __func__);
		return;
	}

	if (AMainFPLevelScript* FPLevel = Cast<AMainFPLevelScript>(GetWorld()->GetLevelScriptActor()))
	{
		FPLevel->SetPlacementModeEnable(true, BuildingData.Get());
		FPLevel->OnSpawnBuilding.BindUObject(this, &ThisClass::SpawnBuilding);
	}
}

void UFPBuildingButtonUI::OnButtonDeactive()
{
	if (BuildingData.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : No BuildingData"), __func__);
		return;
	}
	
	if (AMainFPLevelScript* FPLevel = Cast<AMainFPLevelScript>(GetWorld()->GetLevelScriptActor()))
	{
		FPLevel->SetPlacementModeEnable(false, BuildingData.Get());
		FPLevel->OnSpawnBuilding.Unbind();
	}
}

void UFPBuildingButtonUI::SpawnBuilding()
{
	if (BuildingData.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : No BuildingData"), __func__);
		return;
	}

	UFPGameInstance* GameInst = Cast<UFPGameInstance>(GetGameInstance());
	if (GameInst == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Can't Get GameInst"), __func__);
		return;
	}

	AMainFPLevelScript* FPLevel = Cast<AMainFPLevelScript>(GetWorld()->GetLevelScriptActor());
	if (FPLevel == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs : Can't Get FPLevel"), __func__);
		return;
	}

	AddBuildingCount(-1);
	int32 curCount = BuildingData->CurrentCount - 1;

	GameInst->EditItemCount(BuildingData.Get(), -1);

	if (curCount <= 0)
	{
		FPLevel->SetPlacementModeEnable(false);

		if (AFPHud* MyHud = Cast<AFPHud>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			TWeakObjectPtr<class UFPStylingUI> StylingUI = MyHud->GetStylingUI();
			if (StylingUI.IsValid())
			{
				StylingUI->RemoveBuildingButton(this);
			}
		}
	}
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

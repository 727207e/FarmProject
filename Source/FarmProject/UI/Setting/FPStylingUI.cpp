// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting/FPStylingUI.h"
#include "GameSystem/Level/MainFPLevelScript.h"
#include "Components/ScrollBox.h"
#include "PaperSprite.h"
#include "UI/Building/FPBuildingButtonUI.h"

#define BuildingScrollBoxUIName TEXT("BuildingScrollBox_UI")

UFPStylingUI::UFPStylingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPStylingUI::NativeConstruct()
{
	if (FPLevel == nullptr)
	{
		FPLevel = Cast<AMainFPLevelScript>(GetWorld()->GetLevelScriptActor());
	}
	BuildingScrollBox = Cast<UScrollBox>(GetWidgetFromName(BuildingScrollBoxUIName));
}

void UFPStylingUI::ActiveStylingUI()
{
	if (FPLevel)
	{
		FPLevel->SetPlacementModeEnable(true);
	}

	GetInventory();
	GenerateBuildingButtonUI();
}

void UFPStylingUI::DeactiveStylingUI()
{
	if (FPLevel)
	{
		FPLevel->SetPlacementModeEnable(false);
	}
}

void UFPStylingUI::GetInventory()
{
	UPaperSprite* LoadedSprite = LoadObject<UPaperSprite>(nullptr, TEXT("/Game/DownloadAsset/Ground_Game_UI/Sprites/Buttons/Active/Button__14__Sprite.Button__14__Sprite"));
	UTexture2D* SpriteTexture = LoadedSprite->GetBakedTexture(); 
	InfoArray.Add(FBuildingInfo(FText::FromString("TESTBuild"), 1, SpriteTexture));
}

void UFPStylingUI::GenerateBuildingButtonUI()
{
	for (int32 i = 0; i < InfoArray.Num(); ++i)
	{
		UFPBuildingButtonUI* NewButton = CreateWidget<UFPBuildingButtonUI>(this, BuildingButtonREF);

		if (NewButton)
		{
			NewButton->ButtonInit(InfoArray[i]);
			BuildingButtonArray.Add(NewButton);
			if (BuildingScrollBox)
			{
				BuildingScrollBox->AddChild(NewButton);
			}
		}
	}
}

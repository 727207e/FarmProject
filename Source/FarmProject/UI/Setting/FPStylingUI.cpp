// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting/FPStylingUI.h"
#include "GameSystem/Level/MainFPLevelScript.h"
#include "Components/ScrollBox.h"
#include "PaperSprite.h"
#include "Components/Button.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "UI/Building/FPEditBuildingUI.h"
#include "UI/Building/FPBuildingButtonUI.h"

#define BuildingScrollBoxUIName TEXT("BuildingScrollBox_UI")
#define EditBuildingUIName TEXT("EditBuilding_UI")
#define StylingUIShutDownName TEXT("StylingUIShutDown_UI")

UFPStylingUI::UFPStylingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPStylingUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (FPLevel == nullptr)
	{
		FPLevel = Cast<AMainFPLevelScript>(GetWorld()->GetLevelScriptActor());
	}
	BuildingScrollBox = Cast<UScrollBox>(GetWidgetFromName(BuildingScrollBoxUIName));
	CancelButton = Cast<UButton>(GetWidgetFromName(StylingUIShutDownName));
	EditBuildingUI = Cast<UFPEditBuildingUI>(GetWidgetFromName(EditBuildingUIName));
	if (EditBuildingUI != nullptr)
	{
		EditBuildingUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UFPStylingUI::ActiveStylingUI()
{
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

void UFPStylingUI::ActiveEditBuildMode(UClickableComponent* ClickableComponent)
{
	if (FPLevel->GetIsBuildMode())
	{
		if (!FPLevel->GetIsPlacementMode())
		{
			EditBuildingUI->ActiveEditBuildUI(ClickableComponent);
		}
	}
}

void UFPStylingUI::GetInventory()
{
	UPaperSprite* LoadedSprite = LoadObject<UPaperSprite>(nullptr, TEXT("/Game/DownloadAsset/Ground_Game_UI/Sprites/Buttons/Active/Button__14__Sprite.Button__14__Sprite"));
	UTexture2D* SpriteTexture = LoadedSprite->GetBakedTexture(); 
	AddInfoArray(FBuildingInfo(FText::FromString("TESTBuild"), 1, SpriteTexture));
}

void UFPStylingUI::GenerateBuildingButtonUI()
{
	for (int32 i = 0; i < InfoArray.Num(); ++i)
	{
		UFPBuildingButtonUI* NewButton = CreateWidget<UFPBuildingButtonUI>(this, BuildingButtonREF);

		if (NewButton)
		{
			NewButton->ButtonInit(InfoArray[i]);

			NewButton->OnBuildingButtonActive.BindLambda([this](UFPBuildingButtonUI& ButtonUI)
				{
					if (FPLevel)
					{
						FPLevel->SetPlacementModeEnable(true);
					}
				});
			NewButton->OnBuildingButtonDeactive.BindLambda([this](UFPBuildingButtonUI& ButtonUI)
				{
					if (FPLevel)
					{
						FPLevel->SetPlacementModeEnable(false);
					}
				});

			BuildingButtonArray.Add(NewButton);
			if (BuildingScrollBox)
			{
				BuildingScrollBox->AddChild(NewButton);
			}
		}
	}
}
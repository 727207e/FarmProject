// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting/FPStylingUI.h"
#include "GameSystem/Level/MainFPLevelScript.h"
#include "Components/ScrollBox.h"
#include "PaperSprite.h"
#include "Components/Button.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Building/ActorComponent/FPBuildingInfoComponent.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "UI/Building/FPEditBuildingUI.h"

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
		EditBuildingUI->OnBuildingJustDelete.BindUObject(this, &UFPStylingUI::DeleteBuilding);
		EditBuildingUI->OnBuildingDeleteAndMove.BindUObject(this, &UFPStylingUI::BuildingMoveSelect);
	}
}

void UFPStylingUI::DeleteBuilding(AActor* Target)
{
	UFPBuildingInfoComponent* BuildingInfo = Target->GetComponentByClass<UFPBuildingInfoComponent>();
	if (BuildingInfo == nullptr)
	{
		return;
	}
	FString BuildingName = BuildingInfo->Name;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->ChangeBuildingCount(1);
			break;
		}
	}
}

void UFPStylingUI::BuildingMoveSelect(AActor* Target)
{
	UFPBuildingInfoComponent* BuildingInfo = Target->GetComponentByClass<UFPBuildingInfoComponent>();
	if (BuildingInfo == nullptr)
	{
		return;
	}
	FString BuildingName = BuildingInfo->Name;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->ChangeBuildingCount(1);
			Button->OnButtonClicked();
			break;
		}
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
		FPLevel->SetPlacementModeEnable(false, nullptr);
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
	GameInst = Cast<UFPGameInstance>(GetGameInstance());

///////테스트 코드 - 인벤토리에 강제로 아이템 주입
	TWeakObjectPtr<UBuildingItemData> NewItemData = NewObject<UBuildingItemData>(this);
	NewItemData->CurrentCount = 1;
	NewItemData->MaxCount = 1;
	UPaperSprite* LoadedSprite = LoadObject<UPaperSprite>(nullptr, TEXT("/Game/DownloadAsset/Ground_Game_UI/Sprites/Buttons/Active/Button__14__Sprite.Button__14__Sprite"));
	UTexture2D* SpriteTexture = LoadedSprite->GetBakedTexture();
	NewItemData->Image = SpriteTexture;
	NewItemData->Name = FText::FromString("TESTBuild");
	NewItemData->BlueprintObject = ttttt;
	GameInst->AddInventory(NewItemData);
}

void UFPStylingUI::GenerateBuildingButtonUI()
{
	for (int32 i = 0; i < GameInst->BuildingInventory.Num(); ++i)
	{
		UFPBuildingButtonUI* NewButton = CreateWidget<UFPBuildingButtonUI>(this, BuildingButtonREF);
		TWeakObjectPtr<UBuildingItemData> data = GameInst->BuildingInventory[i];
		if (NewButton)
		{
			NewButton->ButtonInit(data->CurrentCount, data->Image, data->Name);

			NewButton->OnBuildingButtonActive.BindLambda([this, data, NewButton]()
				{
					if (FPLevel)
					{
						FPLevel->SetPlacementModeEnable(true, data);
						FPLevel->OnSpawnBuilding.BindLambda([this, data, NewButton]()
							{
								NewButton->ChangeBuildingCount(-1);
								data->CurrentCount--;
							});
					}
				});
			NewButton->OnBuildingButtonDeactive.BindLambda([this, data]()
				{
					if (FPLevel)
					{
						FPLevel->SetPlacementModeEnable(false, data);
						FPLevel->OnSpawnBuilding.Unbind();
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
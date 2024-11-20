// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Setting/FPStylingUI.h"
#include "GameSystem/Level/MainFPLevelScript.h"
#include "Components/ScrollBox.h"
#include "PaperSprite.h"
#include "Components/Button.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "GameSystem/Data/ItemDataBase.h"
#include "GameSystem/Data/BuildingItemData.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Building/FPBuilding.h"
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
	AFPBuilding* BuildingInfo = Cast<AFPBuilding>(Target);
	if (BuildingInfo == nullptr)
	{
		return;
	}
	FString BuildingName = BuildingInfo->Name;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->AddBuildingCount(1);
			break;
		}
	}
}

void UFPStylingUI::BuildingMoveSelect(AActor* Target)
{
	AFPBuilding* BuildingInfo = Cast<AFPBuilding>(Target);
	if (BuildingInfo == nullptr)
	{
		return;
	}
	FString BuildingName = BuildingInfo->Name;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->AddBuildingCount(1);
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

///////테스트 코드 - 인벤토리에 강제로 아이템 주입 (GameInst 에서 생성하는 로직도 만들어야 할듯 - 삭제가 안됨)
	TObjectPtr<UBuildingItemData> NewItemData = NewObject<UBuildingItemData>(this);
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
		TObjectPtr<UBuildingItemData> data = GameInst->BuildingInventory[i];

		bool bIsFind = false;
		for (UFPBuildingButtonUI* ButtonUI : BuildingButtonArray)
		{
			//이미 UI가 배치된 경우
			if (data->Name.ToString().Equals(ButtonUI->GetBuildingName()))
			{
				UE_LOG(LogTemp, Error, TEXT("%d"), data->CurrentCount);
				ButtonUI->SetBuildingCount(data->CurrentCount);
				bIsFind = true;
				break;
			}
		}

		if (bIsFind)
		{
			continue;
		}

		//새로운 UI를 배치해야하는 경우
		UFPBuildingButtonUI* NewButton = CreateWidget<UFPBuildingButtonUI>(this, BuildingButtonREF);
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
								NewButton->AddBuildingCount(-1);
								int32 curCount = data->CurrentCount - 1;

								GameInst->EditInventoryItem(data, -1);

								if (curCount <= 0)
								{
									FPLevel->SetPlacementModeEnable(false);
									RemoveBuildingButton(NewButton);
								}
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

void UFPStylingUI::RemoveBuildingButton(UFPBuildingButtonUI* ButtonToRemove)
{
	if (BuildingScrollBox && ButtonToRemove)
	{
		BuildingScrollBox->RemoveChild(ButtonToRemove);
	}

	BuildingButtonArray.Remove(ButtonToRemove);

	ButtonToRemove->RemoveFromParent();
	ButtonToRemove = nullptr;
}
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
#include "GameSystem/Building/GridCell.h"

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
	FString BuildingName = BuildingInfo->BuildingData->Name.ToString();

	bool bIsFind = false;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->AddBuildingCount(1);
			GameInst->EditItemCount(BuildingInfo->BuildingData, 1);
			bIsFind = true;

			TArray<AActor*> OverlappingActors;
			BuildingInfo->GetOverlappingActors(OverlappingActors, AGridCell::StaticClass());

			for (AActor* Actor : OverlappingActors)
			{
				if (AGridCell* GridCellActor = Cast<AGridCell>(Actor))
				{
					GridCellActor->ResetGridState();
				}
			}
			break;
		}
	}

	if (!bIsFind)
	{
		BuildingInfo->BuildingData->CurrentCount = 1;
		GameInst->AddItemToInventory(BuildingInfo->BuildingData);
		GenerateBuildingButtonUI(BuildingInfo->BuildingData);
	}
}

void UFPStylingUI::BuildingMoveSelect(AActor* Target)
{
	AFPBuilding* BuildingInfo = Cast<AFPBuilding>(Target);
	if (BuildingInfo == nullptr)
	{
		return;
	}
	FString BuildingName = BuildingInfo->BuildingData->Name.ToString();
	BuildingInfo->BuildingData->CurrentCount += 1;

	bool bIsFind = false;
	for (TObjectPtr<UFPBuildingButtonUI> Button : BuildingButtonArray)
	{
		if (BuildingName.Equals(Button->GetBuildingName()))
		{
			Button->AddBuildingCount(1);
			GameInst->EditItemCount(BuildingInfo->BuildingData, 1);
			Button->OnButtonClicked();
			bIsFind = true;

			TArray<AActor*> OverlappingActors;
			BuildingInfo->GetOverlappingActors(OverlappingActors, AGridCell::StaticClass());

			for (AActor* Actor : OverlappingActors)
			{
				if (AGridCell* GridCellActor = Cast<AGridCell>(Actor))
				{
					GridCellActor->ResetGridState();
				}
			}
			break;
		}
	}

	if (!bIsFind)
	{
		BuildingInfo->BuildingData->CurrentCount = 1;
		GameInst->AddItemToInventory(BuildingInfo->BuildingData);
		GenerateBuildingButtonUI(BuildingInfo->BuildingData)->OnButtonClicked();
	}
}

void UFPStylingUI::ActiveStylingUI()
{
	GetInventory();
	ScrollBoxSetup();
}

void UFPStylingUI::DeactiveStylingUI()
{
	if (FPLevel)
	{
		FPLevel->SetPlacementModeEnable(false, nullptr);
		EditBuildingUI->DeactiveEditBuildUI();
	}

	for (UFPBuildingButtonUI* ButtonUI : BuildingButtonArray)
	{
		ButtonUI->DeactiveUI();
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
}

void UFPStylingUI::ScrollBoxSetup()
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
		GenerateBuildingButtonUI(data);
	}
}

TObjectPtr<class UFPBuildingButtonUI> UFPStylingUI::GenerateBuildingButtonUI(TObjectPtr<UBuildingItemData> Data)
{
	UFPBuildingButtonUI* NewButton = CreateWidget<UFPBuildingButtonUI>(this, BuildingButtonREF);
	if (NewButton)
	{
		NewButton->ButtonInit(Data->CurrentCount, Data->Image, Data->Name);

		NewButton->OnBuildingButtonActive.BindLambda([this, Data, NewButton]()
			{
				if (FPLevel)
				{
					FPLevel->SetPlacementModeEnable(true, Data);
					FPLevel->OnSpawnBuilding.BindLambda([this, &Data, NewButton]()
						{
							NewButton->AddBuildingCount(-1);
							int32 curCount = Data->CurrentCount - 1;

							GameInst->EditItemCount(Data, -1);

							if (curCount <= 0)
							{
								FPLevel->SetPlacementModeEnable(false);
								RemoveBuildingButton(NewButton);
							}
						});
				}
			});
		NewButton->OnBuildingButtonDeactive.BindLambda([this, &Data]()
			{
				if (FPLevel)
				{
					FPLevel->SetPlacementModeEnable(false, Data);
					FPLevel->OnSpawnBuilding.Unbind();
				}
			});

		BuildingButtonArray.Add(NewButton);
		if (BuildingScrollBox)
		{
			BuildingScrollBox->AddChild(NewButton);
		}
	}

	return NewButton;
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
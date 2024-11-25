// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPDownInfoWidget.h"
#include "GameSystem/Data/FieldItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameSystem/Level/FPGameInstance.h"
#include "GameSystem/Data/SeedDataBase.h"

#define PropertyUIName TEXT("Property_UI")
#define MainImageUIName TEXT("MainImage_UI")
#define TitleTextUIName TEXT("TitleText_UI")
#define ContentTextUIName TEXT("ContentText_UI")
#define SeedButtonUIName TEXT("SeedButton_UI")
#define SeedComboBoxUIName TEXT("SeedComboBox_UI")
#define SeedComboBoxHintTextUIName TEXT("SeedComboBoxHintText_UI")

UFPDownInfoWidget::UFPDownInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UFPDownInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PropertyUI = Cast<UImage>(GetWidgetFromName(PropertyUIName));
	MainImageUI = Cast<UImage>(GetWidgetFromName(MainImageUIName));
	TitleTextUI = Cast<UTextBlock>(GetWidgetFromName(TitleTextUIName));
	ContentTextUI = Cast<UTextBlock>(GetWidgetFromName(ContentTextUIName));
	SeedButtonUI = Cast<UButton>(GetWidgetFromName(SeedButtonUIName));

	SeedComboBoxUI = Cast<UComboBoxString>(GetWidgetFromName(SeedComboBoxUIName));
	SeedComboBoxHintTextUI = Cast<UTextBlock>(GetWidgetFromName(SeedComboBoxHintTextUIName));
	if (SeedComboBoxUI && SeedComboBoxHintTextUI)
	{
		SeedComboBoxUI->OnSelectionChanged.AddDynamic(this, &UFPDownInfoWidget::SeedSelectionChanged);
		SeedComboBoxUI->OnOpening.AddDynamic(this, &UFPDownInfoWidget::SeedOpening);
	}
}

void UFPDownInfoWidget::SeedSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	SeedComboBoxHintTextUI->SetVisibility(ESlateVisibility::Hidden);

	TObjectPtr<USeedDataBase> SelectedObject = nullptr;
	for (TObjectPtr<USeedDataBase> SeedData : SeedInven)
	{
		if (FString::Printf(TEXT("%s (%d)"), *SeedData->Name.ToString(), SeedData->CurrentCount) == SelectedItem)
		{
			SelectedObject = SeedData;
			break;
		}
	}

	if (SelectedObject != nullptr)
	{
		if (CurData->ECurState != EFieldState::None)
		{
			GameIns->RemoveTimeCheckArray(CurData);
		}

		SelectedObject->CurrentCount--;

		CurData->Name = SelectedObject->Name;
		CurData->Image = SelectedObject->Image;
		CurData->NeedMTime = SelectedObject->NeedMTime;
		CurData->NeedLTime = SelectedObject->NeedLTime;
		CurData->MStaticMesh = SelectedObject->MStaticMesh.GetClass();
		CurData->LStaticMesh = SelectedObject->LStaticMesh.GetClass();
		CurData->ECurState = EFieldState::S;

		CurData->InitStartTime();

		GameIns->AddTimeCheckArray(CurData);
		DataChangeUI();
	}
}

void UFPDownInfoWidget::SeedOpening()
{
	if (GameIns == nullptr)
	{
		GameIns = Cast<UFPGameInstance>(GetGameInstance());
	}

	if (GameIns)
	{
		SeedInven = GameIns->SeedInventory;
		SeedComboBoxUI->ClearOptions();

		for(TObjectPtr<USeedDataBase> SeedData : SeedInven)
		{
			FString Title = FString::Printf(TEXT("%s (%d)"), *SeedData->Name.ToString(), SeedData->CurrentCount);
			SeedComboBoxUI->AddOption(Title);
		}
	}
}

void UFPDownInfoWidget::SettingRemainTimeText()
{    
	FDateTime Now = FDateTime::Now();
	FTimespan ElapsedTime = Now - CurData->NextNeedTime;

	if (CurData->ECurState == EFieldState::L)
	{
		ContentTextUI->SetText(FText::FromString(TEXT("Finish")));
		return;
	}

	int32 RemainingSeconds = -ElapsedTime.GetTotalSeconds();

	int32 Hours = RemainingSeconds / 3600;
	int32 Minutes = (RemainingSeconds % 3600) / 60;
	int32 Seconds = RemainingSeconds % 60;

	UEnum* EnumPtr = StaticEnum<EFieldState>();
	FString EnumAsString = EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(CurData->ECurState)).ToString();
	FString ResultText = FString::Printf(TEXT("Current State : %s\nRemain Time : %02d:%02d:%02d"), *EnumAsString, Hours, Minutes, Seconds);
	ContentTextUI->SetText(FText::FromString(ResultText));
}

void UFPDownInfoWidget::ActiveUI()
{
	this->SetVisibility(ESlateVisibility::Visible);
	DataChangeUI();
}

void UFPDownInfoWidget::DeactiveUI()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	if (GetWorld()->GetTimerManager().IsTimerActive(PlantTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(PlantTimerHandle);
	}
}

void UFPDownInfoWidget::DataChangeUI()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(PlantTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(PlantTimerHandle);
	}

	if (CurData->ECurState != EFieldState::None)
	{
		MainImageUI->SetBrushFromTexture(CurData->Image);
		TitleTextUI->SetText(CurData->Name);
		SettingRemainTimeText();
		GetWorld()->GetTimerManager().SetTimer(PlantTimerHandle, this, &UFPDownInfoWidget::SettingRemainTimeText, 0.1f, true);
	}
	else
	{
		MainImageUI->SetBrushFromTexture(nullptr);
		TitleTextUI->SetText(FText::FromString(""));
		ContentTextUI->SetText(FText::FromString(""));
	}
}

void UFPDownInfoWidget::CurUISetting(TObjectPtr<UFieldItemData> FieldData)
{

	if (CurData == nullptr)
	{
		CurData = FieldData;
		ActiveUI();
	}
	else if (CurData.Get() == FieldData)
	{
		CurData = nullptr;
		DeactiveUI();
	}
	else if (CurData != FieldData)
	{
		CurData = FieldData;
		DataChangeUI();
	}
}
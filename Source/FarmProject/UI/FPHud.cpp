// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPHud.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LevelScriptActor.h"
#include "GameSystem/Level/Interface/BuildManagerInterface.h"
#include "GameSystem/Building/ActorComponent/ClickableComponent.h"
#include "UI/Setting/FPStylingUI.h"
#include "GameSystem/Data/FieldItemData.h"
#include "UI/FPDownInfoWidget.h"

AFPHud::AFPHud()
{
}

void AFPHud::OpenStylingUI()
{
    if (StylingUI)
    {
        if (StylingUI->IsVisible())
        {
            StylingUI->SetVisibility(ESlateVisibility::Hidden);
            StylingUI->DeactiveStylingUI();
            if (BuildManager != nullptr)
            {
                BuildManager->DeactiveBuildMode();
            }
        }
        else
        {
            StylingUI->SetVisibility(ESlateVisibility::Visible);
            StylingUI->ActiveStylingUI();
            if (BuildManager != nullptr)
            {
                BuildManager->ActiveBuildMode();
            }
        }
    }
}

void AFPHud::DownInfoUIUpdate(TObjectPtr<UFieldItemData> FieldData)
{
    DownInfoUI->CurUISetting(FieldData);
}

void AFPHud::BeginPlay()
{
    if (StylingUI == nullptr)
    {
        StylingUI = Cast<UFPStylingUI>(CreateWidget<UUserWidget>(GetWorld(), StylingUIClass));
        if (StylingUI)
        {
            StylingUI->AddToViewport();
            StylingUI->SetVisibility(ESlateVisibility::Hidden);

            OnClickClickableComp.BindUObject(StylingUI, &UFPStylingUI::ActiveEditBuildMode);
        }
    }
    if (DownInfoUI == nullptr)
    {
        DownInfoUI = Cast<UFPDownInfoWidget>(CreateWidget<UFPDownInfoWidget>(GetWorld(), DownInfoUIClass));
        if (DownInfoUI)
        {
            DownInfoUI->AddToViewport();
            DownInfoUI->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (BuildManager == nullptr)
    {
        ALevelScriptActor* LevelScriptActor = GetWorld()->GetLevelScriptActor();
        BuildManager.SetObject(LevelScriptActor);
        BuildManager.SetInterface(Cast<IBuildManagerInterface>(LevelScriptActor));
    }
}
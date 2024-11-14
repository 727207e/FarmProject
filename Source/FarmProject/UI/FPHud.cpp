// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPHud.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LevelScriptActor.h"
#include "GameSystem/Level/Interface/BuildManagerInterface.h"

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
            if (BuildManager != nullptr)
            {
                BuildManager->DeactiveBuildMode();
            }
        }
        else
        {
            StylingUI->SetVisibility(ESlateVisibility::Visible);
            if (BuildManager != nullptr)
            {
                BuildManager->ActiveBuildMode();
            }
        }
    }
}

void AFPHud::BeginPlay()
{
    if (StylingUI == nullptr)
    {
        StylingUI = CreateWidget<UUserWidget>(GetWorld(), StylingUIClass);
        StylingUI->AddToViewport();
        StylingUI->SetVisibility(ESlateVisibility::Hidden);
    }

    if (BuildManager == nullptr)
    {
        ALevelScriptActor* LevelScriptActor = GetWorld()->GetLevelScriptActor();
        BuildManager.SetObject(LevelScriptActor);
        BuildManager.SetInterface(Cast<IBuildManagerInterface>(LevelScriptActor));
    }
}
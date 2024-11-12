// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPHud.h"
#include "Blueprint/UserWidget.h"

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
        }
        else
        {
            StylingUI->SetVisibility(ESlateVisibility::Visible);
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
}

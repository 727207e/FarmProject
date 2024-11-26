// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Data/FieldItemData.h"
#include "GameSystem/Level/FPGameInstance.h"

void UFieldItemData::InitStartTime()
{
    StartTime = FDateTime::Now();

    FTimespan TimeToAdd(0, 0, NeedMTime);
    NextNeedTime = StartTime + TimeToAdd;
}

void UFieldItemData::NextState()
{
    ECurState = ECurState == EFieldState::S ? EFieldState::M : EFieldState::L;

    if (ECurState == EFieldState::M)
    {
        FTimespan TimeToAdd(0, 0, NeedLTime + NeedMTime);
        NextNeedTime = StartTime + TimeToAdd;
    }

    if (OnNextState.IsBound())
    {
        OnNextState.Execute(ECurState);
    }
}

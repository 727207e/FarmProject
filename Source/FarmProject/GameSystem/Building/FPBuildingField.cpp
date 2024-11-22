// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/FPBuildingField.h"
#include "UI/FPHud.h"
#include "GameSystem/Data/FieldItemData.h"

AFPBuildingField::AFPBuildingField()
{
}

void AFPBuildingField::BeginPlay()
{
	Super::BeginPlay();

	MyHud = Cast<AFPHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	FieldData = NewObject<UFieldItemData>(this, UFieldItemData::StaticClass());
}

void AFPBuildingField::ShowBuildingUI()
{
	if (MyHud)
	{
		MyHud->DownInfoUIUpdate(FieldData);
	}
}

//FieldData에서 ResultFarmName을 기준으로 데이터를 가져와야 겠네 (근데 어디서 가져오지? -> 리스트가 있는 곳이 있어야 겠다)


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

//FieldData���� ResultFarmName�� �������� �����͸� �����;� �ڳ� (�ٵ� ��� ��������? -> ����Ʈ�� �ִ� ���� �־�� �ڴ�)


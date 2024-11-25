// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/FPBuildingField.h"
#include "UI/FPHud.h"
#include "GameSystem/Data/FieldItemData.h"
#include "Kismet/KismetMathLibrary.h"

AFPBuildingField::AFPBuildingField()
{
}

void AFPBuildingField::BeginPlay()
{
	Super::BeginPlay();

	MyHud = Cast<AFPHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	int32 RandomNumber = UKismetMathLibrary::RandomIntegerInRange(1, 10000);
	FString ObjectName = FString::Printf(TEXT("RandomObject_%d"), RandomNumber);
	UE_LOG(LogTemp, Error, TEXT(" Spawn : %s") , *ObjectName);
	FieldData = NewObject<UFieldItemData>(this, UFieldItemData::StaticClass(), FName(*ObjectName));
	//FieldData�� ����ִ� ��� �� �̹���, ��� ������.
}

void AFPBuildingField::ShowBuildingUI()
{
	if (MyHud)
	{
		MyHud->DownInfoUIUpdate(FieldData);
	}
}

//FieldData���� ResultFarmName�� �������� �����͸� �����;� �ڳ� (�ٵ� ��� ��������? -> ����Ʈ�� �ִ� ���� �־�� �ڴ�)


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
	//FieldData에 비어있는 경우 빈 이미지, 등등 넣을것.
}

void AFPBuildingField::ShowBuildingUI()
{
	if (MyHud)
	{
		MyHud->DownInfoUIUpdate(FieldData);
	}
}

//FieldData에서 ResultFarmName을 기준으로 데이터를 가져와야 겠네 (근데 어디서 가져오지? -> 리스트가 있는 곳이 있어야 겠다)


// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/Building/FPBuildingField.h"
#include "UI/FPHud.h"
#include "GameSystem/Data/FieldItemData.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

AFPBuildingField::AFPBuildingField()
{
	StaticMeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh1"));
	StaticMeshComponent1->SetupAttachment(GetRootComponent());
	StaticMeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh2"));
	StaticMeshComponent2->SetupAttachment(GetRootComponent());
	StaticMeshComponent3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh3"));
	StaticMeshComponent3->SetupAttachment(GetRootComponent());
	StaticMeshComponent4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh4"));
	StaticMeshComponent4->SetupAttachment(GetRootComponent());
	StaticMeshComponent5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh5"));
	StaticMeshComponent5->SetupAttachment(GetRootComponent());
	StaticMeshComponent6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh6"));
	StaticMeshComponent6->SetupAttachment(GetRootComponent());

	FarmMeshArray.Add(StaticMeshComponent1);
	FarmMeshArray.Add(StaticMeshComponent2);
	FarmMeshArray.Add(StaticMeshComponent3);
	FarmMeshArray.Add(StaticMeshComponent4);
	FarmMeshArray.Add(StaticMeshComponent5);
	FarmMeshArray.Add(StaticMeshComponent6);
}

void AFPBuildingField::BeginPlay()
{
	Super::BeginPlay();

	MyHud = Cast<AFPHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	FieldData = NewObject<UFieldItemData>(this, UFieldItemData::StaticClass());
	if (FieldData)
	{
		FieldData->OnNextState.BindUObject(this, &AFPBuildingField::ChangeStaticMesh);
	}
	//FieldData�� ����ִ� ��� �� �̹���, ��� ������.
}

void AFPBuildingField::ShowBuildingUI()
{
	if (MyHud)
	{
		MyHud->DownInfoUIUpdate(FieldData);
	}
}

void AFPBuildingField::ChangeStaticMesh(EFieldState ECurState)
{
	UStaticMesh* TargetMesh = nullptr;

	if (ECurState == EFieldState::M)
	{
		TargetMesh = FieldData->MStaticMesh;
	}
	else
	{
		TargetMesh = FieldData->LStaticMesh;
	}

	for (TObjectPtr<UStaticMeshComponent> StaticMeshComp : FarmMeshArray)
	{
		StaticMeshComp->SetStaticMesh(TargetMesh);
	}
}

//FieldData���� ResultFarmName�� �������� �����͸� �����;� �ڳ� (�ٵ� ��� ��������? -> ����Ʈ�� �ִ� ���� �־�� �ڴ�)


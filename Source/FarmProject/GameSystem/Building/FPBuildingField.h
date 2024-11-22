// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSystem/Building/FPBuilding.h"
#include "FPBuildingField.generated.h"

/**
 * 
 */
UCLASS()
class FARMPROJECT_API AFPBuildingField : public AFPBuilding
{
	GENERATED_BODY()
	
public:
	AFPBuildingField();
	virtual void BeginPlay() override;

	virtual void ShowBuildingUI() override;

protected:
	UPROPERTY()
	TObjectPtr<class AFPHud> MyHud;

	UPROPERTY()
	TObjectPtr<class UFieldItemData> FieldData;

	//본인이 가지고 있는 식물의 데이터를 가지고 있어야 함.
	//UI 업데이트는 데이터 보내주기
};

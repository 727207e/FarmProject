#pragma once

#include "CoreMinimal.h"
#include "InvenSaveForm.generated.h"

USTRUCT(BlueprintType)
struct FInvenSaveForm
{
    GENERATED_BODY()

public:
	UPROPERTY()
	int32 Id = 0;

    UPROPERTY()
    int32 ItemForm = 0; // 1 : Building , 2 : Seed , 3 : Animal

    UPROPERTY()
    int32 CurrentCount;
};

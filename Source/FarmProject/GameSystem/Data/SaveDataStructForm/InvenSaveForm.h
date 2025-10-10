#pragma once

#include "CoreMinimal.h"
#include "InvenSaveForm.generated.h"

UENUM(BlueprintType)
enum class EItemForm : uint8
{
	None = 0,
	Building = 1,
	Seed,
	Animal
};


USTRUCT(BlueprintType)
struct FInvenSaveForm
{
    GENERATED_BODY()

public:
	UPROPERTY()
	int32 Id = 0;

    UPROPERTY()
    EItemForm ItemForm = EItemForm::None;

    UPROPERTY()
    int32 CurrentCount;
};
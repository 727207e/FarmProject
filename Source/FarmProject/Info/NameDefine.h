#pragma once

#define SAVEGAME_NAME TEXT("SaveGame")
#define COLLISION_CLICKABLE ECC_GameTraceChannel2

UENUM(BlueprintType)
enum class ELanguageType : uint8
{
	Korean,
	English
};
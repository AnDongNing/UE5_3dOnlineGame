// Copyright Epic Games, Inc.All Rights Reserved.


#include "InventoryProjectCppGameMode.h"
#include "InventoryProjectCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventoryProjectCppGameMode::AInventoryProjectCppGameMode()
	: Super()
{
	// 将默认的Pawn类设置为我们的蓝图角色
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
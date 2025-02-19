// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryProjectCppPlayerController.h"
#include "EnhancedInputSubsystems.h"

void AInventoryProjectCppPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 获取增强输入子系统
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// 添加映射上下文以便获取控制
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}
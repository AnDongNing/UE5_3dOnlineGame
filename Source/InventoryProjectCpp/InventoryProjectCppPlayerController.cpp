// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryProjectCppPlayerController.h"
#include "EnhancedInputSubsystems.h"

void AInventoryProjectCppPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ��ȡ��ǿ������ϵͳ
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// ���ӳ���������Ա��ȡ����
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}
// Copyright Epic Games, Inc.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryProjectCppPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class INVENTORYPROJECTCPP_API AInventoryProjectCppPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** 用于玩家输入的输入映射上下文 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// 开始 Actor 接口
protected:

	virtual void BeginPlay() override;

	// 结束 Actor 接口
};
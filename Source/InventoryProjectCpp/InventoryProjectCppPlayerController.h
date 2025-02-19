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

	/** ����������������ӳ�������� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// ��ʼ Actor �ӿ�
protected:

	virtual void BeginPlay() override;

	// ���� Actor �ӿ�
};
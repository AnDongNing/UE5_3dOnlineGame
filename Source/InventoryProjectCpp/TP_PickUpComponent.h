// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InventoryProjectCppCharacter.h"
#include "TP_PickUpComponent.generated.h"
#include "Engine/Engine.h"

// 声明当有人拾取此物品时将调用的委托
// 拾取此物品的角色是随通知发送的参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AInventoryProjectCppCharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYPROJECTCPP_API UTP_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	/** 任何人都可以订阅以接收此事件的委托 */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickUp;

	UTP_PickUpComponent();
protected:

	/** 当游戏开始时调用 */
	virtual void BeginPlay() override;

	/** 当某物与此组件重叠时的代码 */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
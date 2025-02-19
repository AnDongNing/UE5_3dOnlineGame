// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InventoryProjectCppCharacter.h"
#include "TP_PickUpComponent.generated.h"
#include "Engine/Engine.h"

// ����������ʰȡ����Ʒʱ�����õ�ί��
// ʰȡ����Ʒ�Ľ�ɫ����֪ͨ���͵Ĳ���
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AInventoryProjectCppCharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYPROJECTCPP_API UTP_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	/** �κ��˶����Զ����Խ��մ��¼���ί�� */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickUp;

	UTP_PickUpComponent();
protected:

	/** ����Ϸ��ʼʱ���� */
	virtual void BeginPlay() override;

	/** ��ĳ���������ص�ʱ�Ĵ��� */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
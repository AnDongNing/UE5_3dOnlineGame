// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_PickUpComponent.h"

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// 设置球体碰撞
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// 注册我们的重叠事件
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 检查是否是第一人称角色重叠
	AInventoryProjectCppCharacter* Character = Cast<AInventoryProjectCppCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// 通知该角色正在被拾取
		OnPickUp.Broadcast(Character);

		// 从重叠事件中注销，以便不再触发
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_PickUpComponent.h"

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// ����������ײ
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// ע�����ǵ��ص��¼�
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ����Ƿ��ǵ�һ�˳ƽ�ɫ�ص�
	AInventoryProjectCppCharacter* Character = Cast<AInventoryProjectCppCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// ֪ͨ�ý�ɫ���ڱ�ʰȡ
		OnPickUp.Broadcast(Character);

		// ���ص��¼���ע�����Ա㲻�ٴ���
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
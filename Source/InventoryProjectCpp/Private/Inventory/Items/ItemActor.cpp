// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Items/ItemActor.h"

#include "Components/SphereComponent.h"
#include "Inventory/InventoryComponent.h"
#include "InventoryProjectCpp/InventoryProjectCppCharacter.h"

// 设置默认值
AItemActor::AItemActor()
{
	// 设置此Actor每帧调用Tick()。如果不需要，可以关闭此功能以提高性能。
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(MeshComponent);
	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);
}

// 当游戏开始或生成时调用
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	if (ItemObject == nullptr)
	{
		ItemObject = GetDefaultItemObject();
	}
}

void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AInventoryProjectCppCharacter* Player = Cast<AInventoryProjectCppCharacter>(OtherActor))
	{
		if (Player->GetInventoryComponent()->TryAddItem(ItemObject))
		{
			Destroy();
		}
	}
}
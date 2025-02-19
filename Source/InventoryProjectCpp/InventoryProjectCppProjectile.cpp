// Copyright Epic Games, Inc.All Rights Reserved.

#include "InventoryProjectCppProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AInventoryProjectCppProjectile::AInventoryProjectCppProjectile()
{
	// ʹ��������Ϊ�򵥵���ײ��ʾ
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AInventoryProjectCppProjectile::OnHit);		// ����һ��֪ͨ�������������ĳ���赲��ʱ����

	// ��Ҳ�������������
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// ����Ϊ�����
	RootComponent = CollisionComp;

	// ʹ��ProjectileMovementComponent�����ƴ�Ͷ������ƶ�
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Ĭ����3�������
	InitialLifeSpan = 3.0f;
}

void AInventoryProjectCppProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// ֻ���ڻ����������ʱ����ӳ���������Ͷ����
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}
// Copyright Epic Games, Inc.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryProjectCppProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)
class AInventoryProjectCppProjectile : public AActor
{
	GENERATED_BODY()

	/** ������ײ��� */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	/** Ͷ�����ƶ���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AInventoryProjectCppProjectile();

	/** ��Ͷ�������ĳ��ʱ���� */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** ����CollisionComp�Ӷ��� **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** ����ProjectileMovement�Ӷ��� **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
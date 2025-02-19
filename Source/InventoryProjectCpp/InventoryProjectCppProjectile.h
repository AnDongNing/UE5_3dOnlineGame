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

	/** 球体碰撞组件 */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	/** 投射物移动组件 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AInventoryProjectCppProjectile();

	/** 当投射物击中某物时调用 */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** 返回CollisionComp子对象 **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** 返回ProjectileMovement子对象 **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
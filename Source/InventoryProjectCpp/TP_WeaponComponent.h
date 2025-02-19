// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AInventoryProjectCppCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYPROJECTCPP_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	/** Ҫ���ɵ��䵯�� */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AInventoryProjectCppProjectile> ProjectileClass;

	/** ÿ�ο���ʱ���ŵ����� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** ÿ�ο���ʱ���ŵĶ�����̫�� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** ǹ������ڽ�ɫλ�õ�ƫ�� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	/** ӳ�������� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** ������붯�� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** ���ô�������Ե�Ĭ��ֵ */
	UTP_WeaponComponent();

	/** ���������ӵ���һ�˳ƽ�ɫ */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(AInventoryProjectCppCharacter* TargetCharacter);

	/** ����һ���䵯 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

protected:
	/** �������������Ϸ�淨 */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** ���д������Ľ�ɫ */
	AInventoryProjectCppCharacter* Character;
};
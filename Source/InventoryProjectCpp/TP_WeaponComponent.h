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
	/** 要生成的射弹类 */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AInventoryProjectCppProjectile> ProjectileClass;

	/** 每次开火时播放的声音 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** 每次开火时播放的动画蒙太奇 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** 枪口相对于角色位置的偏移 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	/** 映射上下文 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** 射击输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** 设置此组件属性的默认值 */
	UTP_WeaponComponent();

	/** 将武器附加到第一人称角色 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(AInventoryProjectCppCharacter* TargetCharacter);

	/** 发射一个射弹 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

protected:
	/** 结束此组件的游戏玩法 */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** 持有此武器的角色 */
	AInventoryProjectCppCharacter* Character;
};
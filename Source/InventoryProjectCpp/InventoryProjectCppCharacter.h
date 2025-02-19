// Copyright Epic Games, Inc. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InventoryProjectCppCharacter.generated.h"

class UInventoryComponent;
class UInventory;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class AInventoryProjectCppCharacter : public ACharacter
{
	GENERATED_BODY()

	/** 角色网格体：第一人称视角（手臂；仅自己可见） */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** 第一人称相机 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** 输入映射上下文 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** 跳跃输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** 移动输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** 库存输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

public:
	AInventoryProjectCppCharacter();

protected:
	virtual void BeginPlay();

public:

	/** 视角输入动作 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** 用于AnimBP切换到另一组动画的布尔值 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter的布尔值 */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter的布尔值 */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** InventoryComponent的Getter和Setter */
	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent) { InventoryComponent = NewInventoryComponent; }

protected:
	/** 用于移动输入 */
	void Move(const FInputActionValue& Value);

	/** 用于视角输入 */
	void Look(const FInputActionValue& Value);

protected:
	void ToggleInventory();

	UPROPERTY(BlueprintReadWrite)
	UInventory* InventoryWidget;

	UPROPERTY(BlueprintReadOnly)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TileSize = 50.f;

	// APawn接口
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// APawn接口结束

public:
	/** 返回Mesh1P子对象 **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** 返回FirstPersonCameraComponent子对象 **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
	TSubclassOf<UInventory> InventoryWidgetClass;
};
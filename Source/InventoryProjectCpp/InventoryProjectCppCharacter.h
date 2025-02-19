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

	/** ��ɫ�����壺��һ�˳��ӽǣ��ֱۣ����Լ��ɼ��� */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** ��һ�˳���� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** ����ӳ�������� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** ��Ծ���붯�� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** �ƶ����붯�� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** ������붯�� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

public:
	AInventoryProjectCppCharacter();

protected:
	virtual void BeginPlay();

public:

	/** �ӽ����붯�� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** ����AnimBP�л�����һ�鶯���Ĳ���ֵ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter�Ĳ���ֵ */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter�Ĳ���ֵ */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	/** InventoryComponent��Getter��Setter */
	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent) { InventoryComponent = NewInventoryComponent; }

protected:
	/** �����ƶ����� */
	void Move(const FInputActionValue& Value);

	/** �����ӽ����� */
	void Look(const FInputActionValue& Value);

protected:
	void ToggleInventory();

	UPROPERTY(BlueprintReadWrite)
	UInventory* InventoryWidget;

	UPROPERTY(BlueprintReadOnly)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TileSize = 50.f;

	// APawn�ӿ�
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// APawn�ӿڽ���

public:
	/** ����Mesh1P�Ӷ��� **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** ����FirstPersonCameraComponent�Ӷ��� **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
	TSubclassOf<UInventory> InventoryWidgetClass;
};
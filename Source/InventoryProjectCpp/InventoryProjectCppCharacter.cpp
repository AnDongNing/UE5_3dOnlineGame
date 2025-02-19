// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryProjectCppCharacter.h"
#include "InventoryProjectCppProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/Widget/Inventory.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AInventoryProjectCppCharacter

AInventoryProjectCppCharacter::AInventoryProjectCppCharacter()
{
	//角色开始时没有步枪
	bHasRifle = false;
	
	//设置碰撞舱的尺寸
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	//创建CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//创建一个网格组件，该组件将在“第一人称”视图查看（控制角色时）
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->SetColumns(5);
	InventoryComponent->SetRows(5);
}

void AInventoryProjectCppCharacter::BeginPlay()
{
	//调用基类
	Super::BeginPlay();

	// Create inventory widget
	// InventoryWidgetClass = LoadClass<UInventory>(nullptr, TEXT("/Game/Content/Blueprint/WBP_Inventory"));
	// if (InventoryWidgetClass != nullptr)
	// {
	// 	InventoryWidget = CreateWidget<UInventory>(GetWorld(), InventoryWidgetClass);
	// 	
	// 	if (InventoryWidget != nullptr)
	// 	{
	// 		InventoryWidget->InitializeInventory(InventoryComponent, TileSize);
	// 		InventoryWidget->AddToViewport();
	// 		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	// 	}
	// }

	//添加输入映射上下文
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AInventoryProjectCppCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//设置操作绑定
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInventoryProjectCppCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInventoryProjectCppCharacter::Look);

		// Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AInventoryProjectCppCharacter::ToggleInventory);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AInventoryProjectCppCharacter::Move(const FInputActionValue& Value)
{
	//输入是Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//添加移动
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AInventoryProjectCppCharacter::Look(const FInputActionValue& Value)
{
	//输入是Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//向控制器添加偏航和俯仰输入
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AInventoryProjectCppCharacter::ToggleInventory()
{
	//切换库存部件
	APlayerController* playerController = Cast<APlayerController>(this->GetController());
	if (InventoryWidget != nullptr)
	{
		if (InventoryWidget->IsInViewport())
		{
			InventoryWidget->RemoveFromParent();
			playerController->SetInputMode(FInputModeGameOnly());
			playerController->bShowMouseCursor = false;
		}
		else
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);
			InventoryWidget->AddToViewport();
			playerController->SetInputMode(InputMode);
			playerController->bShowMouseCursor = true;
		}
	}
}

void AInventoryProjectCppCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AInventoryProjectCppCharacter::GetHasRifle()
{
	return bHasRifle;
}
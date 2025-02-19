// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Widget/InventoryGrid.h"

#include "Line.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryGameStateBase.h"
#include "Inventory/Widget/Item.h"

class AInventoryGameStateBase;

void UInventoryGrid::InitializeGrid(UInventoryComponent* inventoryComp, float tileSize)
{
	InventoryComponent = inventoryComp;
	TileSize = tileSize;
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
	if (CanvasSlot != nullptr && InventoryComponent != nullptr)
	{
		CanvasSlot->SetSize(FVector2D( TileSize * InventoryComponent->GetColumns(), TileSize * InventoryComponent->GetRows()));
	}
	CreateLineSegments();
	RefreshGrid();
	InventoryComponent->OnInventoryChanged.AddDynamic(this, &UInventoryGrid::RefreshGrid);
}

int32 UInventoryGrid::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	DrawGrid(Context);
	if (UWidgetBlueprintLibrary::IsDragDropping() && bDrawDropLocation)
	{
		UItemObject* Payload = GetPayload(*UWidgetBlueprintLibrary::GetDragDroppingContent());
		FLinearColor Color = FLinearColor::White;
		if (IsRoomAvailable(Payload))
		{
			Color = FLinearColor(0, 1, 0, .25);
		}
		else
		{
			Color = FLinearColor(1, 0, 0, .25);
		}
		UWidgetBlueprintLibrary::DrawBox(Context,
			FVector2D(DraggedItemTopLeftTile.X * TileSize, DraggedItemTopLeftTile.Y * TileSize),
			FVector2D(Payload->GetDimensions().X * TileSize, Payload->GetDimensions().Y * TileSize),
			ItemBackgroundColor,
			Color);
	}
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UInventoryGrid::OnItemRemoved(UItemObject* ItemObject)
{
	InventoryComponent->RemoveItem(ItemObject);
	RefreshGrid();
}

bool UInventoryGrid::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (IsRoomAvailable(GetPayload(*InOperation)))
	{
		InventoryComponent->AddItemAt(GetPayload(*InOperation), InventoryComponent->TileToIndex(DraggedItemTopLeftTile));
	}
	else
	{
		if (!InventoryComponent->TryAddItem(GetPayload(*InOperation)))
		{
			GetWorld()->GetGameState<AInventoryGameStateBase>()->SpawnItemFromActor(InventoryComponent->GetOwner(), GetPayload(*InOperation), true);
		}
	}
	
	return true;
}

bool UInventoryGrid::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	FVector2D MousePosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	Chaos::Pair<bool, bool> Pair = MousePositionInTile(MousePosition);
	FVector2D Dimension = GetPayload(*InOperation)->GetDimensions();
	int topLeftX = Pair.First ? (Dimension.X - 1) : Dimension.X;
	int topLeftY = Pair.Second ? (Dimension.Y - 1) : Dimension.Y;
	FIntPoint ItemTileCenter = FIntPoint(FMath::Clamp(topLeftX, 0, topLeftX), FMath::Clamp(topLeftY,0, topLeftY)) / 2;
	DraggedItemTopLeftTile = FIntPoint((MousePosition / TileSize - ItemTileCenter).X, (MousePosition / TileSize - ItemTileCenter).Y);
	return true;
}

void UInventoryGrid::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	bDrawDropLocation = true;
}

void UInventoryGrid::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bDrawDropLocation = false;
}

void UInventoryGrid::RefreshGrid()
{
	GridCanvasPanel->ClearChildren();
	TMap<UItemObject*, FVector2D> Items = InventoryComponent->GetAllItems();
	for (auto Item : Items)
	{
		// 使用 ItemWidget 的 Bp 版本创建物品小部件
		/*
		如果使用 BindWidget，您必须在从您的小部件类派生的小部件的蓝图版本中创建相应的组件。
		然后，当想要创建小部件时，需要使用创建的蓝图类，而不是 c++ 类。
		BindWidget 会搜索具有特定名称的特定类的组件，但它不会创建这些组件。
		如果您不想使用蓝图，实际上不需要使用 BindWidget，可以直接在c++类中创建这些组件。
		*/
		UItem* ItemWidget = CreateItemWidget();
		ItemWidget->InitializeItem(Item.Key, TileSize);
		ItemWidget->OnRemoved.AddDynamic(this, &UInventoryGrid::OnItemRemoved);
		UPanelSlot* PanelSlot = GridCanvasPanel->AddChild(ItemWidget);
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot);
		CanvasSlot->SetAutoSize(true);
		CanvasSlot->SetPosition(FVector2D(Item.Value.X * TileSize, Item.Value.Y * TileSize));
	}
}

void UInventoryGrid::CreateLineSegments()
{
	const int Columns = InventoryComponent->GetColumns();
	const int Rows = InventoryComponent->GetRows();
	for (int i = 0; i <= Columns; i++)
	{
		// 计算垂直线的起点和终点
		Lines.Add(FLine(FVector2D(i * TileSize, 0), FVector2D(i * TileSize, Rows * TileSize)));
	}
	for (int i = 0; i <= Rows; i++)
	{
		// 计算水平线的起点和终点
		Lines.Add(FLine(FVector2D(0, i * TileSize), FVector2D(Columns * TileSize, i * TileSize)));
	}
}

Chaos::Pair<bool, bool> UInventoryGrid::MousePositionInTile(FVector2D MousePosition) const
{
	bool isRight;
	bool isDown;
	if (fmod(MousePosition.X, TileSize) > TileSize / 2)
	{
		isRight = true;
	}
	else
	{
		isRight = false;
	}
	if (fmod(MousePosition.Y, TileSize) > TileSize / 2)
	{
		isDown = true;
	}
	else
	{
		isDown = false;
	}
	return Chaos::MakePair(isRight, isDown);
}

void UInventoryGrid::DrawGrid(FPaintContext& Context) const
{
	FVector2D localTopLeft = FVector2D::ZeroVector;
	for (int i = 0; i < Lines.Num(); i++)
	{

		UWidgetBlueprintLibrary::DrawLine(Context,localTopLeft + Lines[i].Start, localTopLeft + Lines[i].End, LineColor, AntiAliasing, LineThickness);
	}
}

void UInventoryGrid::RotateItem()
{
	UItemObject* Payload = GetPayload(*UWidgetBlueprintLibrary::GetDragDroppingContent());
	if (IsValid(Payload))
	{
		Payload->Rotate();
		Cast<UItem>(UWidgetBlueprintLibrary::GetDragDroppingContent()->DefaultDragVisual)->GetItemIcon();
		Cast<UItem>(UWidgetBlueprintLibrary::GetDragDroppingContent()->DefaultDragVisual)->RefreshItem(); 
	}
}

UItemObject* UInventoryGrid::GetPayload(const UDragDropOperation& InDragDropEvent) const
{
	if (IsValid(&InDragDropEvent))
	{
		return Cast<UItemObject>(InDragDropEvent.Payload);
	}
	return nullptr;
}

bool UInventoryGrid::IsRoomAvailable(UItemObject* Payload) const
{
	if (Payload == nullptr)
	{
		return false;
	}

	return InventoryComponent->IsRoomAvailable(Payload, InventoryComponent->TileToIndex(DraggedItemTopLeftTile));
}


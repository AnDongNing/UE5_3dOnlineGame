// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

class UItemObject;
class USphereComponent;

UCLASS()
class INVENTORYPROJECTCPP_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// 为此 Actor 的属性设置默认值
	AItemActor();

protected:
	// 当游戏开始或生成时调用
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UItemObject* ItemObject;

	UFUNCTION(BlueprintImplementableEvent)
	UItemObject* GetDefaultItemObject();
};

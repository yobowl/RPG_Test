// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_TEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Physical Max number of items
	UPROPERTY(BlueprintReadWrite, Category = "Storage Space")
	int32 MaxNumItems = 65536;  // default is 2^16

	//Max Weight for Stored Items
	UPROPERTY(BlueprintReadWrite, Category = "Storage Space")
	float MaxWeight = 500.f;		// Assuming default max weight is in lbs. 

	//Max Number of Stacks (Slots)
	UPROPERTY(BlueprintReadWrite, Category = "Storage Space")
	uint8 MaxStacks = 8;	//Default max is 256 stacks (2^8)

	//Max number of items per stack/slot
	UPROPERTY(BlueprintReadWrite, Category = "Storage Space")
	uint8 ItemsPerStack = 99;	//This will be default, different items should specify respective max items/stack

	UPROPERTY(VisibleAnywhere)
	TArray<FItemStruct> SlotArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Storage Space")
	uint8 CurrentStacks = 0;

	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, int32> MaxItemMapping;

	FActorSpawnParameters SpawnParameters;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void AddItem(AItem* ItemToAdd, int32 NumToAdd);
	void AddItem(FItemStruct ItemToAdd, int32 NumToAdd);
	void RemoveItem(AItem* ItemToRemove, int32 NumToRemove);
	void DropItem();

	UFUNCTION(BlueprintCallable)
	TArray<FItemStruct> GetSlotArray();
};

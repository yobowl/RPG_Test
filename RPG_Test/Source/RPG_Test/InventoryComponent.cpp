// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	///Sets up default maximums for number of items in inventory, defaulting to zero.  Change specific values in blueprint
	MaxItemMapping.Emplace(EItemType::Null, 0);
	MaxItemMapping.Emplace(EItemType::Coin, 0);
	MaxItemMapping.Emplace(EItemType::Resource, 0);
	MaxItemMapping.Emplace(EItemType::Quest, 0);
	MaxItemMapping.Emplace(EItemType::Sword, 0);
	MaxItemMapping.Emplace(EItemType::Shield, 0);
	MaxItemMapping.Emplace(EItemType::Bow, 0);
	MaxItemMapping.Emplace(EItemType::Arrow, 0);
	MaxItemMapping.Emplace(EItemType::Helmet, 0);
	MaxItemMapping.Emplace(EItemType::Curaiss, 0);
	MaxItemMapping.Emplace(EItemType::Gauntlet, 0);
	MaxItemMapping.Emplace(EItemType::LegPlate, 0);


	SpawnParameters.bAllowDuringConstructionScript = false;
	SpawnParameters.bDeferConstruction = false;
	SpawnParameters.bNoFail = true;
	SpawnParameters.bTemporaryEditorActor = true;


}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(AItem* ItemToAdd, int32 NumToAdd)
{
	bool IsItemAdded = false;

	/// Create Item added to inventory and set the count of it
	FItemStruct ItemToBeAdded;
	ItemToBeAdded.SetItemCount(NumToAdd);
	ItemToBeAdded.SetItemType(ItemToAdd->GetItemType());
	ItemToBeAdded.SetItemName(ItemToAdd->GetItemName());
	
	if (!ItemToAdd->GetItemBlueprint())
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted picking up item which has not ItemBlueprint set!"));
	}

	if (!ItemToAdd->GetItemImage())
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted picking up item which has not ItemImage set!"));
	}

	ItemToBeAdded.SetItemBlueprint(ItemToAdd->GetItemBlueprint());
	ItemToBeAdded.SetItemImage(ItemToAdd->GetItemImage());

	for (FItemStruct& Item : SlotArray)
	{

		if (ItemToBeAdded == Item)
		{
			Item.SetItemCount(Item.GetItemCount() + ItemToBeAdded.GetItemCount());	//TODO create functionality to create additional stacks if Count added is greater than stack max

			IsItemAdded = true;
		}

		if (IsItemAdded) { break; }

	}

	if (!IsItemAdded)
	{
		SlotArray.Emplace(ItemToBeAdded);
		CurrentStacks = CurrentStacks + 1;
	}

	//TODO Handle situation where player already has the item being added

	//TODO Check if all inventory slots are used

	//TODO Take care of case where more than one stack is created
	

	ItemToAdd->Destroy();

}

void UInventoryComponent::AddItem(FItemStruct ItemToAdd, int32 NumToAdd = 1)
{

	CurrentStacks = CurrentStacks + 1;

}




void UInventoryComponent::RemoveItem(AItem* ItemToRemove, int32 NumToRemove)
{



}
//TODO Add Functionality to account for stacks
//TODO Add Functionality for dropping multiple items counts larger than one
// Removes Item from inventory and spawns the item in the world
void UInventoryComponent::DropItem()
{
	if (!(SlotArray.Num() > 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Slot Array is empty so nothing can be dropped"));
		return;
	}

	FItemStruct &ItemToDrop = SlotArray.Last();

	
	if (ItemToDrop.GetItemCount() <= 0) { return; }	//Prevent creating negative item counts;


	if (!ItemToDrop.GetItemBlueprint()) { return; }		//TODO Add functionality to still remove item from inventory when there is no valid blueprint

	FVector DropLocation = GetOwner()->GetActorLocation();		//TODO Create richer Drop location
	FRotator DropRotation = FRotator(0, 0, 0);


	if (!GetWorld()->SpawnActor(ItemToDrop.GetItemBlueprint(), &DropLocation, &DropRotation, SpawnParameters))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to drop item"));
		return;
	}

	if (ItemToDrop.GetItemCount() <= 1)
	{
		SlotArray.RemoveSingle(ItemToDrop);
		CurrentStacks = CurrentStacks - 1;
	}
	else
	{
		ItemToDrop.SetItemCount(ItemToDrop.GetItemCount() - 1);
	}
	

}

TArray<FItemStruct> UInventoryComponent::GetSlotArray()
{
	return SlotArray;
}
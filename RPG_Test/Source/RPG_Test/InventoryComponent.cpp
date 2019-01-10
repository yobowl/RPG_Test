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
	//FItemStruct ItemToBeAdded;
	//ItemToBeAdded.SetItemCount(NumToAdd);
	//ItemToBeAdded.SetItemType(ItemToAdd->GetItemType());
	//ItemToBeAdded.SetItemName(ItemToAdd->GetItemName());
	//
	//if (!ItemToAdd->GetItemBlueprint())
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Attempted picking up item which has not ItemBlueprint set!"));
	//}

	//if (!ItemToAdd->GetItemImage())
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Attempted picking up item which has not ItemImage set!"));
	//}

	//ItemToBeAdded.SetItemBlueprint(ItemToAdd->GetItemBlueprint());
	//ItemToBeAdded.SetItemImage(ItemToAdd->GetItemImage());

	FItemStruct ItemToBeAdded = ItemToAdd->GetItemProperties();

	for (FItemStruct& Item : SlotArray)
	{

		if (ItemToBeAdded == Item)
		{
			if (ItemToBeAdded.IsStackable)
			{
				Item.SetItemCount(Item.GetItemCount() + ItemToBeAdded.GetItemCount());	//TODO create functionality to create additional stacks if Count added is greater than stack max

				IsItemAdded = true;
			}

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

void UInventoryComponent::DropItem(FVector DropLocation, FRotator DropRotation, float DistanceAway)
{
	if (!(SlotArray.Num() > 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Slot Array is empty so nothing can be dropped"));
		return;
	}

	FItemStruct &ItemToDrop = SlotArray.Last();

	DropTheItem(ItemToDrop, DropLocation, DropRotation, DistanceAway);

}

//TODO Add Functionality to account for stacks
//TODO Add Functionality for dropping multiple items counts larger than one
// Removes Item from inventory and spawns the item in the world
void UInventoryComponent::DropTheItem(UPARAM(ref) FItemStruct &ItemToDrop, FVector DropLocation, FRotator DropRotation, float DistanceAway)
{
	if (!(SlotArray.Num() > 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Slot Array is empty so nothing can be dropped"));
		return;
	}



	
	if (ItemToDrop.GetItemCount() <= 0) { return; }	//Prevent creating negative item counts;


	if (!ItemToDrop.GetItemBlueprint()) { return; }		//TODO Add functionality to still remove item from inventory when there is no valid blueprint

	if (DropLocation == FVector(0.f))
	{
		if (DistanceAway == -1)		//TODO figure out alternative to determining if DistanceAway parameter has been supplied
		{
			DropLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * DefaultDropDistance;
		}
		else
		{
			DropLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * DistanceAway;
		}
	}


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



//TODO add functionality when items are used, currently just removes item
void UInventoryComponent::UseTheItem(UPARAM(ref)FItemStruct & ItemToUse)
{
	
	if (!(SlotArray.Num() > 0))
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Slot Array is empty so nothing can be used"));
		return;
	}

	if (ItemToUse.GetItemCount() <= 0) { return; }	//Prevent creating negative item counts;


	if (!ItemToUse.GetItemBlueprint()) { return; }		//TODO Add functionality to still use item from inventory when there is no valid blueprint



	if (ItemToUse.GetItemCount() <= 1)
	{
		SlotArray.RemoveSingle(ItemToUse);
		CurrentStacks = CurrentStacks - 1;
	}
	else
	{
		ItemToUse.SetItemCount(ItemToUse.GetItemCount() - 1);
	}

}


void UInventoryComponent::GetSlotArray(TArray<FItemStruct>& Array_Out)
{
	Array_Out = SlotArray;
}



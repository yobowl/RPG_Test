// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"


///Default Functions for Item Struct
FItemStruct::FItemStruct()
{
	ItemCount = 0;
	ItemName = "";
	ItemType = EItemType::Null;

}

int32 FItemStruct::GetItemCount()
{
	return ItemCount;
}

FName FItemStruct::GetItemName()
{
	return ItemName;
}

EItemType FItemStruct::GetItemType()
{
	return ItemType;
}

TSubclassOf<AItem> FItemStruct::GetItemBlueprint()
{
	return ItemBlueprint;
}

bool FItemStruct::GetItemImage(UTexture2D* Image_Out)
{
	if (!ItemImage) { return false; }

	Image_Out = ItemImage;

	return true;
}



void FItemStruct::SetItemCount(int32 Count)
{
	ItemCount = Count;
}

void FItemStruct::SetItemName(FName Name)
{
	ItemName = Name;
}

void FItemStruct::SetItemType(EItemType Type)
{
	ItemType = Type;
}

void FItemStruct::SetItemBlueprint(TSubclassOf<AItem> Blueprint)
{
	if (!Blueprint) { return; }

	ItemBlueprint = Blueprint;

}

void FItemStruct::SetItemImage(UTexture2D * Image)
{
	if (!Image) { return; }

	ItemImage = Image;

}


bool operator==(FItemStruct A, FItemStruct B)
{

	if (! (A.GetItemName() == B.GetItemName()))
	{
		return false;
	}

	if ((!A.GetItemBlueprint()) || (!B.GetItemBlueprint()))
	{
		return false;
	}

	if (!(A.GetItemType() == B.GetItemType()))
	{
		return false;
	}

	return true;
}

// Converts an Actor to an FItemStruct
FItemStruct FItemStruct::ActorToItem(AActor * Actor)
{
	FItemStruct NewItem;

	if (!Actor)
	{
		UE_LOG(LogTemp, Error, TEXT("nullptr used in ActorToItem()"))
			return NewItem;
	}

	NewItem.SetItemName(*(Actor->GetName()));


	return NewItem;
}


// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::SetItemName(FName Name)
{
	ItemProperties.SetItemName(Name);
}

void AItem::SetItemCount(int32 Count)
{
	ItemProperties.SetItemCount(Count);
}

void AItem::SetItemType(EItemType Type)
{
	ItemProperties.SetItemType(Type);
}

void AItem::SetItemBlueprint(TSubclassOf<AItem> Blueprint)
{
	if(!Blueprint) { return; }

	ItemProperties.SetItemBlueprint(Blueprint);
}

void AItem::SetItemImage(UTexture2D * Image)
{
	if (!Image) { return; }

	ItemProperties.SetItemImage(Image);
}

FName AItem::GetItemName()
{
	return ItemProperties.GetItemName();
}

int32 AItem::GetItemCount()
{
	return ItemProperties.GetItemCount();
}

EItemType AItem::GetItemType()
{
	return ItemProperties.GetItemType();
}

TSubclassOf<AItem> AItem::GetItemBlueprint()
{
	return ItemProperties.GetItemBlueprint();
}

bool AItem::GetItemImage(UTexture2D* Item_Out)
{
	return ItemProperties.GetItemImage(Item_Out);
}

void AItem::UseItem()
{
}

void AItem::UseItem_Struct(FItemStruct & Item_Out)
{
}


FItemStruct AItem::GetItemProperties()
{
	return ItemProperties;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM()
enum class EItemType : uint8
{
	Null,
	Coin,
	Resource,
	Quest,
	Sword,
	Shield,
	Bow,
	Arrow,
	Helmet,
	Curaiss,
	Gauntlet,
	LegPlate,
};


USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	FItemStruct();

	int32 GetItemCount();
	FName GetItemName();
	EItemType GetItemType();
	TSubclassOf<class AItem> GetItemBlueprint();	//TODO convert to null pointer safe getter method like GetItemImage()
	bool GetItemImage(UTexture2D* Image_Out);

	void SetItemCount(int32 Count);
	void SetItemName(FName Name);
	void SetItemType(EItemType Type);
	void SetItemBlueprint(TSubclassOf<class AItem> Blueprint);
	void SetItemImage(UTexture2D* Image);

	// Converts an Actor to an Item Struct
	static FItemStruct ActorToItem(AActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType = EItemType::Null;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class AItem> ItemBlueprint;

	//TODO Create mapping for item images to prevent each "stack" from containing a texture asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemImage;

	/// required to allow struct to be used in TArray
	friend bool operator == (FItemStruct A, FItemStruct B);

};


UCLASS()
class RPG_TEST_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

	static const FItemStruct EmptyItem;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FName ItemName = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 ItemCount = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	//Should Always reference the blueprint of the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class AItem> ItemBlueprint;

	// Icon to be used in the inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemImage;

	//Tells Inventory Components if this item can stack 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool IsStackable = true;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	// Set Item Name
	void SetItemName(FName Name);

	UFUNCTION(BlueprintCallable)
	//Set Item Count
	void SetItemCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	// Set Item Type
	void SetItemType(EItemType Type);

	UFUNCTION(BlueprintCallable)
	// Set Item Blueprint
	void SetItemBlueprint(TSubclassOf<AItem> Blueprint);

	UFUNCTION(BlueprintCallable)
	void SetItemImage(UTexture2D* Image);

	UFUNCTION(BlueprintCallable)
	// Return Item Name
	FName GetItemName();

	UFUNCTION(BlueprintCallable)
	// Return ItemCount
	int32 GetItemCount();
	
	UFUNCTION(BlueprintCallable)
	// Return ItemType
	EItemType GetItemType();

	UFUNCTION(BlueprintCallable)
	// Return ItemBlueprint
	TSubclassOf<AItem> GetItemBlueprint();

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetItemImage();

	// Copies values to item from a different item
	void CopyValues(AItem* ItemToCopy);

private:

};

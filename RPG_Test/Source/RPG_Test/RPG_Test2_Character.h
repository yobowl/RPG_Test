// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InventoryComponent.h"
#include "ItemGrabbingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPG_Test2_Character.generated.h"

class UInputComponent;

UCLASS(config = Game)
class ARPG_Test2_Character : public ACharacter
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grabber", meta = (AllowPrivateAccess = "true"))
		class UItemGrabbingComponent* GrabbingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* InventoryComponent;


public:
	ARPG_Test2_Character();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:


	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void OnGrab();
	void OnPickup();
	void OnRelease();
	void OnDrop();
	void OnInventory();		//This calls the ShowInventoryUI function which calls blueprint commands.

	FHitResult GrabResult;
	FHitResult PickupResult;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
		float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.f;

	UFUNCTION(BlueprintCallable)
		void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
		void AddHealth(float HealthToAdd);

	UFUNCTION(BlueprintCallable)
		void SubtractHealth(float HealthToSubtract);


	// This invokes the UI to update the inventory in the player character blueprint
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Inventory UI Update"))
		void UpdateInventoryUI();

	// This invokes the UI to display the inventory using blueprint
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Toggle Inventory UI"))
		void ShowInventoryUI();

	// This event is implemented when damaged is taken
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Damage Taken"))
		void OnDamage();

	// This event is implemented when the character dies
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "On Death"))
		void OnDeath();

	// This event is implemented when Health value changes
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "On Health Change"))
		void OnHealthChange();


	UFUNCTION(BlueprintCallable)
		virtual void Death();

	UFUNCTION(BlueprintCallable)
		virtual void HealthUpdate();

	UFUNCTION(BlueprintCallable)
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:

};
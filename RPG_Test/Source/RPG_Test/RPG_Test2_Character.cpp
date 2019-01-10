// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPG_Test2_Character.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);


//////////////////////////////////////////////////////////////////////////
// ARPG_Test2_Character

ARPG_Test2_Character::ARPG_Test2_Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;


	// Create grabbing component
	GrabbingComponent = CreateDefaultSubobject<UItemGrabbingComponent>(TEXT("Grabbing_Component"));

	// Create inventory component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory_Component"));

}

void ARPG_Test2_Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////
// Input

void ARPG_Test2_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind Grab event
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &ARPG_Test2_Character::OnGrab);

	// Bind Pickup event
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ARPG_Test2_Character::OnPickup);

	// Bind Release event
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &ARPG_Test2_Character::OnRelease);

	// Bind Drop event
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &ARPG_Test2_Character::OnDrop);

	// Bind Inventory event
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ARPG_Test2_Character::OnInventory);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ARPG_Test2_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPG_Test2_Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARPG_Test2_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARPG_Test2_Character::LookUpAtRate);


}



void ARPG_Test2_Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ARPG_Test2_Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ARPG_Test2_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPG_Test2_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void ARPG_Test2_Character::OnGrab()
{
	//TODO manipulate object with physics handle

	UE_LOG(LogTemp, Warning, TEXT("Test Grab!"));

	GrabResult = GrabbingComponent->Grab();

}

void ARPG_Test2_Character::OnPickup()
{
	//TODO create inventory and add object to inventory

	UE_LOG(LogTemp, Warning, TEXT("Test Pickup!"));

	PickupResult = GrabbingComponent->Pickup();

	if (!PickupResult.Actor.IsValid()) { return; }

	if (!PickupResult.GetActor()->IsA<AItem>()) { return; }

	InventoryComponent->AddItem(Cast<AItem>(PickupResult.GetActor()), 1);	//TODO Allow for picking up more than 1 item

	UpdateInventoryUI();

}


void ARPG_Test2_Character::OnRelease()
{
	GrabbingComponent->Release();
}


void ARPG_Test2_Character::OnDrop()
{
	InventoryComponent->DropItem();  //TODO Allow for dropping specific items

	UpdateInventoryUI();
}

void ARPG_Test2_Character::OnInventory()
{
	ShowInventoryUI();
}


// Called when damage is taken
float ARPG_Test2_Character::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = Health - DamageAmount;

	OnDamage();


	// UE4 standards: this should return the actual amount of damage done
	return DamageAmount;
}




void ARPG_Test2_Character::HealthUpdate()
{
	// Put any specific stuff here

	//Implement Blueprint Health change behavior
	OnHealthChange();

}


void ARPG_Test2_Character::SetHealth(float NewHealth)
{
	Health = NewHealth;
	HealthUpdate();
}

void ARPG_Test2_Character::AddHealth(float HealthToAdd)
{
	Health = Health + HealthToAdd;
	HealthUpdate();
}

void ARPG_Test2_Character::SubtractHealth(float HealthToSubtract)
{
	Health = HealthToSubtract;
	HealthUpdate();
}


void ARPG_Test2_Character::Death()
{
	// Put any specific stuff here...

	//Implement Bueprint Death behavior
	OnDeath();

	// Actions taking care of player corpse
	Destroy();
}


void ARPG_Test2_Character::OnDamage_Implementation()
{

	if (Health <= 0.f)
	{
		HealthUpdate();

		Health = 0.f;

		Death();

	}

	HealthUpdate();
}

void ARPG_Test2_Character::OnDeath_Implementation()
{
}

void ARPG_Test2_Character::OnHealthChange_Implementation()
{
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate != NULL) {
		if (GetTotalMassOnPressurePlate() > ThresholdWeight) {
			DoorRotation = FRotator(0.0f, OpenDoorAngle, 0.0f);
			GetOwner()->SetActorRotation(DoorRotation);
		}
		else {
			DoorRotation = FRotator(0.0f, CloseDoorAngle, 0.0f);
			GetOwner()->SetActorRotation(DoorRotation);
		}
	}
}

float UOpenDoor::GetTotalMassOnPressurePlate() {
	float TotalMass = 0.f;
	TArray<AActor*> OUT OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

FRotator NewRotation;
float val;

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
	Owner = GetOwner();
	//val = 90.0;
	// ...
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0, 0.0, 0.0));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0, 90.0f, 0.0));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("Tick %f"), val);

	//if (val <= 0.0) {
	//	return;
	//}
	//val = val - 1.0;
	//Owner->SetActorRotation(FRotator(0.0, val, 0.0));
	//FString rotation = Owner->GetActorRotation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("Tick %s"), rotation);

	// ...

	//if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	//{
	if (GetTotalMassOfActorOnPlate() > 50.0f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
		
	//}

	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastDoorOpenTime >= DoorCloseDelay)
	{
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassOfActorOnPlate() 
{
	float TotalMass = 0.0f;
	if (!PressurePlate) {
		return 0.0f;
	}
	TSet<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (const auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("TOTAL ACTOR WEIGHT: %f"), TotalMass);
		UE_LOG(LogTemp, Warning, TEXT("Actor on plate: %s"), *Actor->GetName());
	}

	return TotalMass;
}


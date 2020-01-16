// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

AActor* Owner;
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
	val = 90.0;
	// ...
	Owner = GetOwner();
	//NewRotation = FRotator(0.0, 90.0, 0.0);
	//Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("Tick %f"), val);

	if (val <= 0.0) {
		return;
	}
	val = val - 1.0;
	Owner->SetActorRotation(FRotator(0.0, val, 0.0));
	//FString rotation = Owner->GetActorRotation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("Tick %s"), rotation);

	// ...
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "PodManager.h"
#include "Components/SphereComponent.h"

// Sets default values
APodManager::APodManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = SphereCollision;
}

// Called when the game starts or when spawned
void APodManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APodManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


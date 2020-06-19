// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PodManager.generated.h"

UCLASS()
class TRIALANDERRORCPP_API APodManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APodManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* SphereCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

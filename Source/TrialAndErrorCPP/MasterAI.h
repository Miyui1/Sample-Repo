// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MasterAI.generated.h"



UCLASS()
class TRIALANDERRORCPP_API AMasterAI : public ACharacter
{
	GENERATED_BODY()

	
public:
	// Sets default values for this character's properties
	AMasterAI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Behavior")
	class UBehaviorTree* BehaviorTreeAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MasterAIController.generated.h"

class UAISenseConfig_Sight;
UCLASS()
class TRIALANDERRORCPP_API AMasterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMasterAIController(const FObjectInitializer & ObjectInitializer);


	UPROPERTY(EditDefaultsOnly, Category = AIPerception)
	UAISenseConfig_Sight* SightConfiguration;

	/*UPROPERTY(EditDefaultsOnly, Category = AIPerception)
	class UAIPerceptionComponent* AIPerceptionComponent;*/
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn * InPawn) override;
	virtual void OnUnPossess() override;
	
public:
	
	UFUNCTION()
	void SenseStuff(AActor* Actor, FAIStimulus Stimulus);
};

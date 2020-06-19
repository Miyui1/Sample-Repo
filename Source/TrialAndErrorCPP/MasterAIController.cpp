// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MasterAI.h"
#include "BehaviorTree/BehaviorTree.h"




AMasterAIController::AMasterAIController(const FObjectInitializer & ObjectInitializer)
{
	SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfiguration"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	PerceptionComponent->ConfigureSense(*SightConfiguration);
	PerceptionComponent->SetDominantSense(*SightConfiguration->GetSenseImplementation());
	
	SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
	SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;
	
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMasterAIController::SenseStuff);
	
}

void AMasterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMasterAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	AMasterAI* EnemyCharacter = Cast<AMasterAI>(InPawn);
	if (EnemyCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character is Valid and Possesed"));
		if (EnemyCharacter->BehaviorTreeAsset && EnemyCharacter->BehaviorTreeAsset->BlackboardAsset)
		{
			RunBehaviorTree(EnemyCharacter->BehaviorTreeAsset);
			UE_LOG(LogTemp, Warning, TEXT("BehaviorTree Is Running"));
			GetBlackboardComponent()->SetValueAsObject(FName("SelfActor"), InPawn);
		}
	}
}

void AMasterAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
}

void AMasterAIController::SenseStuff(AActor* Actor, FAIStimulus Stimulus)
{
	
	if (Actor->ActorHasTag(FName("Player Character"))) {

		GetBlackboardComponent()->SetValueAsObject(FName("FocusedActor"), Actor);
	}
}
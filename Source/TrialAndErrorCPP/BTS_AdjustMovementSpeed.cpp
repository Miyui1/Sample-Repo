// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_AdjustMovementSpeed.h"
#include "MasterAI.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"


UBTS_AdjustMovementSpeed::UBTS_AdjustMovementSpeed(const FObjectInitializer & ObjectInitializer)
{
	
}

void UBTS_AdjustMovementSpeed::TickNode(UBehaviorTreeComponent & OwnerComp,	uint8 * NodeMemory,	float DeltaSeconds)
{
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
	
	AMasterAI* AICharacter = Cast<AMasterAI>(OwnerComp.GetAIOwner()->GetPawn());
	if (AICharacter) 
	{
		ACharacter* PlayerCharacter = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FocusedActor.SelectedKeyName));
		if (PlayerCharacter)
		{
			GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("Speed: %f"), AICharacter->GetCharacterMovement()->MaxWalkSpeed));
			if (PlayerCharacter->GetVelocity().Z > 0 && PlayerCharacter->GetCharacterMovement()->IsFalling())
			{
				AICharacter->GetCharacterMovement()->MaxWalkSpeed -= 10.f;
			}
			else 
			{
				if (!(AICharacter->GetCharacterMovement()->MaxWalkSpeed >= 600))
				{
					AICharacter->GetCharacterMovement()->MaxWalkSpeed += 10.f;
				}
			}
			
		}
		
	}
}

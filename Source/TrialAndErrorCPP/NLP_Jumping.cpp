// Fill out your copyright notice in the Description page of Project Settings.


#include "NLP_Jumping.h"
#include "MasterAI.h"
#include "Kismet/KismetMathLibrary.h"
#include"NavigationSystem/Public/NavLinkCustomComponent.h"
#include"Navigation/PathFollowingComponent.h"
#include"GameFramework/Controller.h"

ANLP_Jumping::ANLP_Jumping(const FObjectInitializer & ObjectInitializer)
{

	GetSmartLinkComp()->SetMoveReachedLink(this, &ANLP_Jumping::NotifySmartLinkReached);
	JumpDuration = 1.5f;
	bSmartLinkIsRelevant = true;
}



void ANLP_Jumping::ReceiveSmartLinkReached(AActor * Agent, const FVector & Destination)
{
	//Super::ReceiveSmartLinkReached(Agent, Destination);
	UE_LOG(LogTemp, Warning, TEXT("SmartLink Running"));
	AMasterAI* AICharacter = Cast<AMasterAI>(Agent);
	if (AICharacter)
	{
		CalculateRequiredRotation(AICharacter, Destination);
		AICharacter->SetActorRotation(RequiredRotation);
		CalculateRequiredVelocity(JumpDuration, Agent->GetActorLocation(), Destination);
		AICharacter->LaunchCharacter(RequiredVelocity, true, true);
	}
}

void ANLP_Jumping::NotifySmartLinkReached(UNavLinkCustomComponent * LinkComp, UObject * PathingAgent, const FVector & DestPoint)
{
	UPathFollowingComponent* PathComp = Cast<UPathFollowingComponent>(PathingAgent);
	if (PathComp)
	{
		AActor* PathOwner = PathComp->GetOwner();
		AController* ControllerOwner = Cast<AController>(PathOwner);
		if (ControllerOwner)
		{
			PathOwner = Cast<AActor>(ControllerOwner->GetPawn());
		}

		ReceiveSmartLinkReached(PathOwner, DestPoint);
		OnSmartLinkReached.Broadcast(PathOwner, DestPoint);
	}
}

FVector ANLP_Jumping::CalculateRequiredVelocity(float Duration, FVector StartingLocation, FVector EndingLocation)
{
	RequiredVelocity.X = (EndingLocation.X - StartingLocation.X) / Duration;
	RequiredVelocity.Y = (EndingLocation.Y - StartingLocation.Y) / Duration;
	RequiredVelocity.Z = (((Duration* Duration * 0.5f * 982.f) + EndingLocation.Z) - StartingLocation.Z) / Duration;

	return RequiredVelocity;
}

FRotator ANLP_Jumping::CalculateRequiredRotation(AMasterAI* Character, FVector EndingLocation)
{
	FRotator LookedAtRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), EndingLocation);
	RequiredRotation.Roll = Character->GetActorRotation().Roll;
	RequiredRotation.Pitch = Character->GetActorRotation().Pitch;
	RequiredRotation.Yaw = LookedAtRotation.Yaw;
	
	return RequiredRotation;
}
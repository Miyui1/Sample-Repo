// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "NLP_Jumping.generated.h"


/**
 * 
 */
UCLASS()
class TRIALANDERRORCPP_API ANLP_Jumping : public ANavLinkProxy
{
	GENERATED_BODY()
	
public:
	ANLP_Jumping(const FObjectInitializer & ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
	float JumpDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameters)
	FVector RequiredVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameters)
	FRotator RequiredRotation;

	
	
	void ReceiveSmartLinkReached(AActor * Agent, const FVector & Destination);
	void NotifySmartLinkReached(UNavLinkCustomComponent * LinkComp, UObject * PathingAgent, const FVector & DestPoint);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector CalculateRequiredVelocity(float Duration, FVector StartingLocation, FVector EndingLocation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FRotator CalculateRequiredRotation(AMasterAI* Character, FVector EndingLocation);

};

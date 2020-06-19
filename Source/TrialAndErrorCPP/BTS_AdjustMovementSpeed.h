// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_AdjustMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class TRIALANDERRORCPP_API UBTS_AdjustMovementSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	

public:
	UBTS_AdjustMovementSpeed(const FObjectInitializer & ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector FocusedActor;
protected:
	virtual void TickNode(UBehaviorTreeComponent & OwnerComp,uint8 * NodeMemory,float DeltaSeconds) override;
	
	
};

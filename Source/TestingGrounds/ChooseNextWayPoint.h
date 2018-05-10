// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWayPoint.generated.h"

/**
 *		Need to be connected AIModule and GameplayTasks in C++ in C# file ProjectName.Build.cs

PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks" });

 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextWayPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(Editanywhere, Category = "Blackboard")
	struct FBlackboardKeySelector Index;

	UPROPERTY(Editanywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WayPoint;

};

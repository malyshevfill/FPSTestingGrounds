// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
//#include "GameFramework/Pawn.h"
#include "PatrolRoute.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	int32 iIndex = Blackboard->GetValueAsInt(Index.SelectedKeyName);
	//UE_LOG(LogTemp, Warning, TEXT("ChooseNextWayPoint::ExecuteTask %d"), iIndex);
	
	// Get controlled Patrolling Guard
	auto AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ensure(AIPawn)) { return EBTNodeResult::Failed;}
	auto PatrolRouteComp = AIPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComp)) { return EBTNodeResult::Failed; }

	//auto PatrollingGuard = Cast<APatrollingGuard>(AIPawn);

	// Set new Way Point in BlackBoard
	/*if (PatrollingGuard->PatrolPoints.)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewWayPointObject == nullptr"));
		Blackboard->SetValueAsObject(WayPoint.SelectedKeyName, AIPawn);
		return EBTNodeResult::Failed;
	}*/
	
	auto WayPoints = PatrolRouteComp->GetPatrolPoints();
	if (WayPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Patrol Points array have no points"));
		return EBTNodeResult::Failed;
	}
	if (!WayPoints[iIndex])
	{
		UE_LOG(LogTemp, Warning, TEXT("Patrol point is not defined"));
		return EBTNodeResult::Failed;
	}


	Blackboard->SetValueAsObject(WayPoint.SelectedKeyName, WayPoints[iIndex]);

	// Set new Index in Blackboard
	iIndex++;
	
	if ( iIndex >= PatrolRouteComp->GetPatrolPoints().Num())
	{
		iIndex = 0;
	}

	
	Blackboard->SetValueAsInt(Index.SelectedKeyName, iIndex);

	

	// return if Succeeded
	return EBTNodeResult::Succeeded;
}

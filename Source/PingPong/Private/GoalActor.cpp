#include "GoalActor.h"
#include "BallActor.h"
#include "Components/BoxComponent.h"

AGoalActor::AGoalActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GoalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GoalCollision"));
	SetRootComponent(GoalCollision);
	GoalCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GoalCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	GoalCollision->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnGoalOverlap);
}

void AGoalActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGoalActor::OnGoalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ABallActor::StaticClass()))
	{
		OtherActor->SetActorLocation(FVector(-150.0f, 0.0f, 200.0f));
	}
}

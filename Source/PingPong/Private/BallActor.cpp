#include "BallActor.h"
#include "PingPongPaddle.h"

#include "Components/StaticMeshComponent.h"

ABallActor::ABallActor()
{
	PrimaryActorTick.bCanEverTick = true;
  
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	SetRootComponent(BallMesh);
  
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->BodyInstance.SetCollisionProfileName("BlockAll");
  
	BallMesh->OnComponentHit.AddDynamic(this, &ABallActor::OnHit);

	BallSpeed = 1600.0f;
}

void ABallActor::BeginPlay()
{
	Super::BeginPlay();
  
	CurrentVelocity = FVector(BallSpeed, 0.0f, 0.0f);
}

void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);
}

void ABallActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Wall"))
	{
		CurrentVelocity.Y *= -1.02f;
	}

	if (OtherActor->ActorHasTag("Wall2"))
	{
		CurrentVelocity.X *= -1.02f;
	}
  
	if (OtherActor->ActorHasTag("Ceiling") || OtherActor->ActorHasTag("Floor"))
	{
		CurrentVelocity.Z *= -1.02f;
	}
  
	if (OtherActor->IsA(APingPongPaddle::StaticClass()))
	{
		CurrentVelocity.X *= -1.02f;
	}
}
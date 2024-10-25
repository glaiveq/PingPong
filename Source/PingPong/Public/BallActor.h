#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class PINGPONG_API ABallActor : public AActor
{
	GENERATED_BODY()

public:
	ABallActor();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
  
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BallMesh;
  
	UPROPERTY(EditAnywhere, Category = "Ball")
	float BallSpeed;
  
	FVector CurrentVelocity;
};
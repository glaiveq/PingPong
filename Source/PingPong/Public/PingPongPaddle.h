#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PingPongPaddle.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UCameraComponent;
class UInputComponent;

UCLASS()
class PINGPONG_API APingPongPaddle : public APawn
{
	GENERATED_BODY()

public:
	APingPongPaddle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:

	void MovePaddle(float AxisValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MovePaddle(FVector Direction);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_MovePaddle(FVector Direction);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* PaddleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComponent;

private:
	UPROPERTY(EditAnywhere, Category = "Paddle")
	float PaddleSpeed;
	
};
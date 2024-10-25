#include "PingPongPaddle.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"

APingPongPaddle::APingPongPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	PaddleMesh->SetupAttachment(SceneComponent);
	PaddleMesh->SetRelativeScale3D(FVector(0.2f, 4.0f, 2.0f));
	PaddleMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SceneComponent);
	CameraComponent->SetRelativeLocation(FVector(-1200.0f, 0.0f, 1000.0f));
	CameraComponent->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	
	PaddleSpeed = 900.0f;
}

void APingPongPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

void APingPongPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APingPongPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APingPongPaddle::MovePaddle);
}

void APingPongPaddle::MovePaddle(float AxisValue)
{
	if (Controller && Controller->IsLocalController())
	{
		FVector Direction = CameraComponent->GetRightVector() * AxisValue * PaddleSpeed * GetWorld()->DeltaTimeSeconds;
		FVector NewLocation = GetActorLocation() + Direction;
		SetActorLocation(NewLocation);
		
		Server_MovePaddle(Direction);
	}
}

void APingPongPaddle::Server_MovePaddle_Implementation(FVector Direction)
{
	FVector NewLocation = GetActorLocation() + Direction;
	SetActorLocation(NewLocation);
	
	Multicast_MovePaddle(NewLocation);
}

bool APingPongPaddle::Server_MovePaddle_Validate(FVector Direction)
{
	return true;
}

void APingPongPaddle::Multicast_MovePaddle_Implementation(FVector NewLocation)
{
	if (!HasAuthority())
	{
		SetActorLocation(NewLocation);
	}
}
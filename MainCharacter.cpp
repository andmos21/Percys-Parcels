// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "NormalAIBehavior.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"


const FName AMainCharacter::MoveForwardBinding("MoveForward");
const FName AMainCharacter::MoveSidewaysBinding("MoveSide");


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));


	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Custum static Mesh"));
    StaticMesh->SetupAttachment(RootComponent);
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);

    // set up gameplay key bindings
    PlayerInputComponent->BindAxis(MoveForwardBinding);
    PlayerInputComponent->BindAxis(MoveSidewaysBinding);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UNormalAIBehavior ai1;
	AMainCharacter player;

    //setting up player
    player.health = 100.0;
    player.defence = 1.0;
    player.exp = 0.0;
    player.scared= 0.0;


    ai1.health = 100.0;
    ai1.damage = 5.0;
    ai1.exp = 25.0;

    player.setPlayer();
    ai1.setAI();

}

void AMainCharacter::Tick(float DeltaSeconds)
{
    // Find movement direction
    const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
    const float SideValue = GetInputAxisValue(MoveSidewaysBinding);

    // Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
    const FVector MoveDirection = FVector(ForwardValue, SideValue, 0.f).GetClampedToMaxSize(1.0f);

    // Insert ForwardValue in C++ to move Forward
    // Calculate  movement
    const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

    if (Movement.SizeSquared() > 0.0f)
    {
        const FRotator NewRotation = Movement.Rotation();
        FHitResult Hit(1.f);
        RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

        if (Hit.IsValidBlockingHit())
        {
            const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
            const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
            RootComponent->MoveComponent(Deflection, NewRotation, true);
        }
    }
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

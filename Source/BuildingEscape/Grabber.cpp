// Copyritsh Ruksov Yegor 2018.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get the player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    auto World = GetWorld();
    {
        auto PlayerController = World->GetFirstPlayerController();

        if (!PlayerController)
        {
            UE_LOG(LogTemp, Error, TEXT("Player contreller is null in grabber class"));
        }
        PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
    }

    // Uncomment to see log out
    /*UE_LOG(LogTemp, Warning, TEXT("Player view point location (%s), rotation (%s)")
        , *PlayerViewPointLocation.ToString()
        , *PlayerViewPointRotation.ToString());*/

    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

    // Draw a red trace in the world
    DrawDebugLine(GetWorld()
        , PlayerViewPointLocation
        , LineTraceEnd
        , FColor::Red
        , false
        , 0.f
        , 0
        , 10.f);

    /// Setup query parameters
    FCollisionQueryParams TraceParams(FName(""), false, GetOwner());

    /// Trace ray out to reach distance
    FHitResult Hit;
    bool IsHitFound = World->LineTraceSingleByObjectType(Hit
        , PlayerViewPointLocation
        , LineTraceEnd
        , FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
        , TraceParams);

    /// See what we hit
    if (IsHitFound)
    {
        auto HitActor = Hit.GetActor();
        UE_LOG(LogTemp, Warning, TEXT("Hit object: %s"), *HitActor->GetName());
    }
}


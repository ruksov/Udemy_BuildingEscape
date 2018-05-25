// Copyritsh Ruksov Yegor 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    void OpenDoor();
    void CloseDoor();

private:
    UPROPERTY(EditAnywhere, meta=(ClampMin=-90.0, ClampMax=90.0))
    float OpenAngle = 90.f;	

    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;

    UPROPERTY(EditAnywhere, meta=(ClampMin=0.0))
    float DoorCloseDelay;

    float DoorLastOpenTime;

    UPROPERTY(VisibleAnywhere)
    AActor* TriggerActor;   // Pawn inherits from Actor
    AActor* Owner;          // Owner door
};

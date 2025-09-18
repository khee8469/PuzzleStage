#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawner.generated.h"

class ATimerActor;

UCLASS()
class PUZZLESTAGE_API AMySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMySpawner();


	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control|BlueprintAsset")
	TSubclassOf<AActor> BP_RotationActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control|Timer")
	float TimerInterval;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control|Timer")
	float FirstTimerInterval;

	FTimerHandle TimerHnadle;


	virtual void BeginPlay() override;

	void Spawn();
};

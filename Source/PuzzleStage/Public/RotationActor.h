#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationActor.generated.h"

UCLASS()
class PUZZLESTAGE_API ARotationActor : public AActor
{
	GENERATED_BODY()

public:	
	ARotationActor();
	
	float GetRotationSpeed();
	void SetRotationSpeed(float Speed);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	float RotationSpeed;

	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComp;

	FTimerHandle DestroyTimerHandle;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void DestroyTimer(float DestroyTime);
	void HandleDestroy();
};

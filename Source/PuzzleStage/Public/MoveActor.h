#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActor.generated.h"

UCLASS()
class PUZZLESTAGE_API AMoveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveActor();

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	FVector StartLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	FVector MoveNormal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	float MaxRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Value")
	bool BackMove;

	FTimerHandle DestroyTimerHandle;

	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComp;


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void DestroyTimer(float DestroyTime);
	void HandleDestroy();
};

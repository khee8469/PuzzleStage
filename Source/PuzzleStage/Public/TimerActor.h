#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerActor.generated.h"

UCLASS()
class PUZZLESTAGE_API ATimerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimerActor();

	FTimerHandle TimerHandle;
	FTimerHandle DestroyTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Control|Timer")
	float TimerInterval;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control|Cheack")
	bool bCheck;

	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComp;



	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	void ActorHidden();
	void DestroyTimer(float DestroyTime);
	void HandleDestroy();
};

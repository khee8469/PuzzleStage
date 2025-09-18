#include "TimerActor.h"

ATimerActor::ATimerActor()
{
	PrimaryActorTick.bCanEverTick = false;
	TimerInterval = 1;
	FirstTimerInterval = 1;
	bCheck = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/EditorMaterials/LevelTransformMaterial.LevelTransformMaterial"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
}

void ATimerActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimerActor::ActorHidden, TimerInterval, true, FirstTimerInterval);
	
}

void ATimerActor::Destroyed()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}


void ATimerActor::ActorHidden()
{
	if (!bCheck)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		bCheck = true;
	}
	else
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
		bCheck = false;
	}
}

void ATimerActor::DestroyTimer()
{
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ATimerActor::HandleDestroy, 1, false, 5);
}

void ATimerActor::HandleDestroy()
{
	Destroy();
}

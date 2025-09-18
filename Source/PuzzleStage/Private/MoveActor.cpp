#include "MoveActor.h"

AMoveActor::AMoveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	MoveNormal = FVector::Zero();
	MoveSpeed = 0;
	StartLocation = FVector::Zero();
	MaxRange = 0;
	BackMove = false;

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

void AMoveActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void AMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!BackMove)
	{
		AddActorLocalOffset(MoveNormal * MoveSpeed * DeltaTime);
		if (MaxRange * MaxRange <= FVector::DistSquared(StartLocation, GetActorLocation()))
		{
			BackMove = true;
		}
	}
	else
	{
		AddActorLocalOffset(-MoveNormal * MoveSpeed * DeltaTime);
		if (FVector::DistSquared(StartLocation, GetActorLocation()) <= MoveSpeed)
		{
			BackMove = false;
		}
	}
}

void AMoveActor::DestroyTimer()
{
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AMoveActor::HandleDestroy, 1, false, 2);
}

void AMoveActor::HandleDestroy()
{
	Destroy();
}


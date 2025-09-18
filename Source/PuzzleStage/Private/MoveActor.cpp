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
		if (MaxRange <= FVector::Dist(StartLocation, GetActorLocation()))
		{
			BackMove = true;
			return;
		}
		AddActorLocalOffset(MoveNormal.GetSafeNormal() * MoveSpeed * DeltaTime, true);
	}
	else
	{
		if (FVector::Dist(StartLocation, GetActorLocation()) <= MoveSpeed * DeltaTime)
		{
			BackMove = false;
			return;
		}
		AddActorLocalOffset(-MoveNormal.GetSafeNormal() * MoveSpeed * DeltaTime, true);
	}
}

void AMoveActor::DestroyTimer(float DestroyTime)
{
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AMoveActor::HandleDestroy, DestroyTime, false, DestroyTime);
}

void AMoveActor::HandleDestroy()
{
	Destroy();
}


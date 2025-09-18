#include "RotationActor.h"

ARotationActor::ARotationActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 100.0f;

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

float ARotationActor::GetRotationSpeed()
{
	return RotationSpeed;
}

void ARotationActor::SetRotationSpeed(float Speed)
{
	RotationSpeed = Speed;
}

void ARotationActor::BeginPlay()
{
	Super::BeginPlay();

}

void ARotationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}

void ARotationActor::DestroyTimer()
{
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ARotationActor::HandleDestroy, 1, false, 2);
}

void ARotationActor::HandleDestroy()
{
	Destroy();
}

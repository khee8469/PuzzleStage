#include "MySpawner.h"
#include "TimerActor.h"
#include "MoveActor.h"
#include "RotationActor.h"
#include "TimerActor.h"

AMySpawner::AMySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/VREditor/BasicMeshes/SM_Ball_01.SM_Ball_01"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/EditorMaterials/LevelTransformMaterial.LevelTransformMaterial"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<AActor> BPClass(TEXT("/Game/Blueprints/BP_RotationActor.BP_RotationActor_C"));
	if (BPClass.Succeeded())
	{
		Actor = BPClass.Class;
	}
}

void AMySpawner::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(TimerHnadle,this, &AMySpawner::Spawn, TimerInterval, true, TimerInterval);
}

void AMySpawner::Spawn()
{
	double x = GetActorLocation().X + FMath::RandRange(-1000, 1000);
	double y = GetActorLocation().Y + FMath::RandRange(-1000, 1000);
	double z = GetActorLocation().Z + FMath::RandRange(-1000, 1000);

	FVector location = { x,y,z };
	FRotator Rotation = GetActorRotation();

	AActor* NewActor = GetWorld()->SpawnActor<AActor>(Actor, location, Rotation);
	
	if (AMoveActor* MoveActor = Cast<AMoveActor>(NewActor))
	{
		MoveActor->MaxRange = FMath::RandRange(1000, 2000);
		MoveActor ->MoveNormal = FMath::VRand();
		MoveActor->MoveSpeed = 1000.0f;
		MoveActor->DestroyTimer(DestroyTime);
	}
	else if (ARotationActor* RotationActor = Cast<ARotationActor>(NewActor))
	{
		RotationActor->SetRotationSpeed(FMath::RandRange(50, 100));
		RotationActor->DestroyTimer(DestroyTime);
	}
	else if (ATimerActor* TimerActor = Cast<ATimerActor>(NewActor))
	{
		TimerActor->TimerInterval = FMath::RandRange(1, 2);
		TimerActor->DestroyTimer(DestroyTime);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "WorldController.h"

// Sets default values
AWorldController::AWorldController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	frameCounter = 0;
}

// Called when the game starts or when spawned
void AWorldController::BeginPlay()
{
	Super::BeginPlay();
	getDepthFrameGetter();
	getMeshTerrain(); 
	getFuildSpawner();
	
	getDrawDepthMap();
}

// Called every frame
void AWorldController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	processControl();
	frameCounter++;
}

void AWorldController::getDrawDepthMap()
{
	TArray<AActor*> actorList;
	TSubclassOf<ADrawDepthMap> classToFind;
	classToFind = ADrawDepthMap::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorList);

	for (int i = 0; i < actorList.Num(); i++)
	{
		if (actorList[i]->Tags[0] == TEXT("DrawDepthMap"))
		{
			drawDepthMap = Cast<ADrawDepthMap>(actorList[i]);
			break;
		}
	}
}

void AWorldController::processControl()
{
	if (frameCounter == 800)
	{

		DepthFrame nowDepthFrame0 = depthFrameGetter->get();
		depthFrameGetter->set((imageProcessor->pixelFilter(nowDepthFrame0)).depthValue);
	}
	if (frameCounter == 1100)
	{

		DepthFrame nowDepthFrame1 = depthFrameGetter->get();
		depthFrameGetter->set((imageProcessor->gaussFilter(nowDepthFrame1)).depthValue);
	}
	DepthFrame &nowDepthFrame = depthFrameGetter->get();
	drawDepthMap->getDepthMap(nowDepthFrame);
	logMessage(frameCounter);
	//reliefMapSpawner->drawReliefMap(meshTerrain->getColor(), nowDepthFrame,reliefMapSpawner->byGradient);
	//meshTerrain->updateMeshTerrain(nowDepthFrame);
	//if (timeToCollision())
	//{
	//	setCollisionBody();
	//	spawnFuild();
	//}
}

//DepthFrame
void AWorldController::getDepthFrameGetter()
{
	TArray<AActor*> actorList;
	TSubclassOf<AdepthFrameGetter> classToFind;
	classToFind = AdepthFrameGetter::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorList);

	for (int i = 0; i < actorList.Num(); i++)
	{
		if (actorList[i]->Tags[0] == TEXT("DepthFrameGetter"))
		{
			depthFrameGetter = Cast<AdepthFrameGetter>(actorList[i]);
			break;
		}
	}
}

void AWorldController::getMeshTerrain()
{
	TArray<AActor*> actorList;
	TSubclassOf<AmeshTerrain> classToFind;
	classToFind = AmeshTerrain::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorList);

	for (int i = 0; i < actorList.Num(); i++)
	{
		if (actorList[i]->Tags[0] == TEXT("MeshTerrain"))
		{
			meshTerrain = Cast<AmeshTerrain>(actorList[i]);
			break;
		}
	}
}

bool AWorldController::timeToCollision()
{
	if (frameCounter%frameInterval == 0)
		return true;
	else
		return false;
}

void AWorldController::setCollisionBody()
{
	DepthFrame &nowDepthFrame = depthFrameGetter->get();
	meshTerrain->clearCollisionBody();
	collisionSpawner->setEdgeColor(meshTerrain->getColor());
	collisionSpawner->setCollision(nowDepthFrame);
	TArray<CollisionBody> nowCollisionBodyList = collisionSpawner->getCollisionBodyList();
	int listSize = nowCollisionBodyList.Num();
	for (int i = 0; i < listSize; i++)
	{
		TArray<FVector>presentCollisionBody;
		presentCollisionBody.Empty();
		presentCollisionBody.Add(nowCollisionBodyList[i].button);
		presentCollisionBody.Add(nowCollisionBodyList[i].top);
		presentCollisionBody.Add(nowCollisionBodyList[i].right);
		presentCollisionBody.Add(nowCollisionBodyList[i].left);
		presentCollisionBody.Add(nowCollisionBodyList[i].center);
		meshTerrain->addCollisionBody(presentCollisionBody);
	}
}

void AWorldController::spawnFuild()
{
	
	DepthFrame &nowDepthFrame = depthFrameGetter->get();
	fuildSpawner->calPlaneDepth(nowDepthFrame);

	if (fuildSpawner->planeDepth < 20)
	{
		fuildSpawner->destoryFuild();
		return;
	}
	FVector spawnLocation;
	int spawnArea = 0;
	bool spawnFlag = false;
	TArray<CollisionBody> nowCollisionBodyList = collisionSpawner->getCollisionBodyList();
	for (auto collisionBody : nowCollisionBodyList)
	{
		int nowDepth = collisionBody.center.Z;
		if (nowDepth < fuildSpawner->planeDepth - basinTreshold)
		{
			if (collisionBody.sumPoint >= spawnArea)
			{
				spawnArea = collisionBody.sumPoint;
				spawnLocation = collisionBody.center;
				spawnFlag = true;
			}
		}
	}
	if (spawnFlag)
	{
		FTransform spawnTransform;
		spawnTransform.SetLocation(spawnLocation);
		spawnTransform.SetRotation(FQuat(90, 0, 0, 1));
		fuildSpawner->spawnFuild(spawnTransform);
	}
	else
	{
		fuildSpawner->destoryFuild();
	}
}

void AWorldController::getFuildSpawner()
{
	TArray<AActor*> actorList;
	TSubclassOf<AFuildSpawner> classToFind;
	classToFind = AFuildSpawner::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorList);

	for (int i = 0; i < actorList.Num(); i++)
	{
		if (actorList[i]->Tags[0] == TEXT("FuildSpawnerTag"))
		{
			fuildSpawner = Cast<AFuildSpawner>(actorList[i]);
			break;
		}
	}
}

void AWorldController::logMessage(int message)
{
	FString logSumNumber;
	logSumNumber = FString::FromInt(message);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, logSumNumber);
}
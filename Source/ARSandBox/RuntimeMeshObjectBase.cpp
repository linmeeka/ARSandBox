// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "RuntimeMeshObjectBase.h"


// Sets default values
ARuntimeMeshObjectBase::ARuntimeMeshObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RuntimeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("RuntimeMesh"));
	RootComponent = RuntimeMesh;
}

void ARuntimeMeshObjectBase::getDepthValue()
{
	//TArray<AActor*> actorList;
	//TSubclassOf<AdepthFrameGetter> classToFind;
	//classToFind = AdepthFrameGetter::StaticClass();
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorList);

	//for (int i = 0; i < actorList.Num(); i++)
	//{
	//	if (actorList[i]->Tags[0] == TEXT("DepthFrameGetter"))
	//	{
	//		tmpActor = Cast<AdepthFrameGetter>(actorList[i]);
	//		int sumNum = tmpActor->640*640;
	//		for (int j = 0; j < sumNum; j++)
	//		{
	//		//	depthValue[j] = tmpActor->depthValue[j];
	//		//	depthFrame->depthValue[j] = tmpActor->depthValue[j];
	//		}
	//	}
	//}
}

// Called when the game starts or when spawned
void ARuntimeMeshObjectBase::BeginPlay()
{
	Super::BeginPlay();
//	depthValue.Init(0, 409600);
}

// Called every frame
void ARuntimeMeshObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


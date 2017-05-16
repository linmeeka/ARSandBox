// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "depthFrameGetter.h"

// Sets default values
AdepthFrameGetter::AdepthFrameGetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AdepthFrameGetter::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add(TEXT("DepthFrameGetter"));
	sumNum = 307200;
}

// Called every frame
void AdepthFrameGetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	getDepthFrame();
}

void AdepthFrameGetter::getDepthFrame()
{
	TArray <UCameraStreamComponent*> components;
	GetComponents<UCameraStreamComponent>(components);
	for (int i = 0; i < components.Num(); i++)
	{
		if (components[i] != NULL)
		{
			cameraStream = components[i];
			if (cameraStream != NULL)	
			{
				if (cameraStream->DepthBuffer.Num() != 0)
				{
					sumNum = cameraStream->DepthBuffer.Num();
					for (int j = 0; j < sumNum; j++)
					{
						depthFrame->depthValue[j]= 255-cameraStream->DepthBuffer[j];
					}
				}
			}
			break;
		}
	}
}

void AdepthFrameGetter::set(const TArray<int> &newDepthValue)
{
	for (auto i : newDepthValue)
	{
		depthFrame->depthValue[i] = newDepthValue[i];
	}
}

void AdepthFrameGetter::getDepthFrame(DepthFrame * &depthFrame)
{

}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Kinect.h>
#include <windows.h>
#include "GameFramework/Actor.h"
#include "KinectFrameManager.generated.h"

UCLASS()
class ARSANDBOX_API AKinectFrameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKinectFrameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	IKinectSensor* pSensor = nullptr;
	IDepthFrameSource* pFrameSource = nullptr;
	IFrameDescription* pFrameDescription = nullptr;
	IDepthFrameReader* pFrameReader = nullptr;

public:
	// 2b. Get frame description
	int        iWidth = 515;
	int        iHeight =424;
	UINT16 *depthValue = new UINT16[512*424];
};

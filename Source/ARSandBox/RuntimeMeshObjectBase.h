// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"
#include "depthFrameGetter.h"
#include "RuntimeMeshObjectBase.generated.h"

UCLASS()
class ARSANDBOX_API ARuntimeMeshObjectBase : public AActor
{
	GENERATED_BODY()

public:
	DepthFrame *depthFrame=new DepthFrame();
	AdepthFrameGetter * tmpActor;

	// Sets default values for this actor's properties
	ARuntimeMeshObjectBase();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	URuntimeMeshComponent *RuntimeMesh;
	
	
};

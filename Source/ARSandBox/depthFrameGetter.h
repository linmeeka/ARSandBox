// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"
#include "CameraStreamComponent.h"
#include "GameFramework/Actor.h"
#include "depthFrameGetter.generated.h"

UCLASS()
class ARSANDBOX_API AdepthFrameGetter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
//	static AdepthFrameGetter * getInstance();

private:
//	static AdepthFrameGetter *m_pDepthFrameGetter;
	AdepthFrameGetter();
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	DepthFrame *depthFrame = new DepthFrame();
	int depthTmp;
	int sumNum;
//	TArray<int> depthValue;
	UCameraStreamComponent *cameraStream;
	void getDepthFrame();
	void getDepthFrame(DepthFrame * &depthFrame);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	DepthFrame & get()
	{
		return *depthFrame;
	}
	void set(const TArray<int> &newDepthValue);
};

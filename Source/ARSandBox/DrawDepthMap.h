// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DepthFrame.h"
#include "GameFramework/HUD.h"
#include "DrawDepthMap.generated.h"

/**
 * 
 */
UCLASS()
class ARSANDBOX_API ADrawDepthMap : public AHUD
{
	GENERATED_BODY()
	
public:
	void getDepthMap(const DepthFrame &newDepthFrame);
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
private:
	int mapWidth = 640;
	int realHeight = 480;
	bool initFlag = false;
	TArray<int> depthFrame;
	
	UPROPERTY(EditAnywhere) UTexture2D * depthMap;
	void setTexture();
	
};

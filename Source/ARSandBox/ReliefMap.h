// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DepthFrame.h"
/**
 * 
 */
class ARSANDBOX_API ReliefMap
{
public:
	ReliefMap();
	~ReliefMap();

	enum DrawingMethod
	{
		byThreshold = 0,
		byGradient = 1
	};

public:
	void drawReliefMap(TArray<FColor> &VertexColors, const DepthFrame &depthFrame,DrawingMethod drawingMethod=byGradient);

private:
	void initColor();

//ReliefMap
	//Threshold
	TArray<int> value_interval;
	TArray<FColor> color_interval;

	void setVertexColorsByThreshold(TArray<FColor> &VertexColors, const DepthFrame &depthFrame);

	//Gradient
	TArray<int> value_gradient;
	TArray<FColor> color_gradient;

	FColor calGradientColor(int number,int value);
	void setVertexColorsByGradient(TArray<FColor> &VertexColors, const DepthFrame &depthFrame);

//counter
	//Threshold
	TArray<int> counterFlag;

	bool checkCounter(int x, int y, TArray<FColor> &VertexColors, const DepthFrame &depthFrame);
	void drawContourByThreshold(TArray<FColor> &VertexColors, const DepthFrame &depthFrame);

	//Gradient
	const int counterNumber = 10;
	int minDepthValue, maxDepthValue;
	TArray<int> counterValue;

	void setMaxAndMin(const DepthFrame &depthFrame);
	void calCounterValue();
	void drawCounterByGradient(TArray<FColor> &VertexColors, const DepthFrame &depthFrame);
};

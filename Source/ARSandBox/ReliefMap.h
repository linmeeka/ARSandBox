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

public:
	void setVertexColorsByThreshold(TArray<FColor> &VertexColors, const DepthFrame &depthFrame);
	void setVertexColorsByGradient(TArray<FColor> &VertexColors, const DepthFrame &depthFrame);
	void drawCounter(TArray<FColor> &VertexColors, const DepthFrame &depthFrame);

private:
	void initColor();

//ReliefMap
	TArray<int> value_interval;
	TArray<FColor> color_interval;

	TArray<int> value_gradient;
	TArray<FColor> color_gradient;

	FColor calGradientColor(int number,int value);

//counter
	const int counterNumber = 10;
	int minDepthValue, maxDepthValue;
	TArray<int> counterValue;

	void setMaxAndMin(const DepthFrame &depthFrame);
	void calCounterValue();
};


#include "DepthFrame.h"
#pragma once

class AImageProcessor
{
public:	
	// Sets default values for this actor's properties
	AImageProcessor();
//	DepthFrame imageFiltering(const DepthFrame &newDepthFrame);
	DepthFrame pixelFilter(const DepthFrame &depthFrame);
	DepthFrame gaussFilter(const DepthFrame &depthFrame);

private:
	DepthFrame depthFrame;

// pixelFilter
	const int innerBandThreshold = 3;
	const int outerBandThreshold = 1;

	
//gaussFilter
	TArray<int> gaussTemplate;
	void initGaussTemplates();
	int gaussTemplateSize;
	int sumWeight;

	
};

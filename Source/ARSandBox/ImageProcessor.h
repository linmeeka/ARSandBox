
#include "DepthFrame.h"
#pragma once

class AImageProcessor
{
public:	
	// Sets default values for this actor's properties
	AImageProcessor();
	void imageFiltering( TArray<int> &depthValue);
	TArray<int> pixelFilter(const DepthFrame &depthFrame);

private:
	int mapHeight = 640;
	int mapWidth = 640;
	int realHeight = 480; 

// pixelFlter
	const int innerBandThreshold = 3;
	const int outerBandThreshold = 7;
//	TArray<int> pixelFilter(const TArray<int> depthValue);
	
	
};

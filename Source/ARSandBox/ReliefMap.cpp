// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "ReliefMap.h"

ReliefMap::ReliefMap()
{
	initColor();
}

ReliefMap::~ReliefMap()
{
}


void ReliefMap::initColor()
{
	value_interval.Init(0, 11);
	color_interval.Init(FColor::Black, 10);
	//…Ë÷√÷µŒ™ { 0,25, 50,75, 100,125, 150,175, 200,255, 255 };
	value_interval[0] = 0;
	for (int i = 1; i < 10; i++)
		value_interval[i] = value_interval[i - 1] + 29;
	value_interval[10] = 255;

	color_interval[0] = FColor(255, 0, 0);
	color_interval[1] = FColor(231, 143, 24);
	color_interval[2] = FColor(237, 233, 46);
	color_interval[3] = FColor(153, 238, 68);
	color_interval[4] = FColor(49, 230, 67);
	color_interval[5] = FColor(64, 238, 186);
	color_interval[6] = FColor(80, 231, 248);
	color_interval[7] = FColor(4, 104, 240);
	color_interval[8] = FColor(46, 61, 245);

	value_gradient.Add(0);
	value_gradient.Add(85);
	value_gradient.Add(170);
	value_gradient.Add(256);
	value_gradient.Add(256);

	color_gradient.Add(FColor::Blue);
	color_gradient.Add(FColor::Green);
	color_gradient.Add(FColor::Yellow);
	color_gradient.Add(FColor::Red);
	color_gradient.Add(FColor::Red);
}

void ReliefMap::drawReliefMap(TArray<FColor> &VertexColors, const DepthFrame &depthFrame, DrawingMethod drawingMethod/* =byGradient */)
{
	switch (drawingMethod)
	{
	case ReliefMap::byThreshold:
		setVertexColorsByThreshold(VertexColors, depthFrame);
		drawContourByThreshold(VertexColors, depthFrame);
		break;
	case ReliefMap::byGradient:
		setVertexColorsByGradient(VertexColors, depthFrame);
		drawCounterByGradient(VertexColors, depthFrame);
		break;
	default:
		break;
	}
}

void ReliefMap::setVertexColorsByThreshold(TArray<FColor> &VertexColors, const DepthFrame &depthFrame)
{
	for (int i = 0; i < depthFrame.mapHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			int index = i*depthFrame.mapWidth + j;
			if (i >= 480)
			{
				VertexColors[index] = FColor::Black;
				continue;
			}
			if (depthFrame.depthValue[index] < value_interval[0])
				VertexColors[index] = FColor::Black;
			else if (depthFrame.depthValue[index]>value_interval[value_interval.Num() - 1])
				VertexColors[index] = FColor::Black;
			else
			{
				int flag = 0;
				for (int k = 0; k < value_interval.Num() - 1; k++)
				{
					if (depthFrame.depthValue[index] >= value_interval[k] && depthFrame.depthValue[index] < value_interval[k + 1])
					{
						//if (abs(depthValue[index] - value_interval[k]) < 0.1 || abs(depthValue[index] - value_interval[k + 1]) < 0.1)
						//	VertexColors[index] = FColor::Black;
						//else
						VertexColors[index] = color_interval[k];
						flag = 1;
					}
				}
				if (flag == 0)
				{
					VertexColors[index] = FColor::Orange;
				}
			}
		}
	}
}

void ReliefMap::setVertexColorsByGradient(TArray<FColor> &VertexColors, const DepthFrame &depthFrame)
{
	for (int i = 0; i <depthFrame.realHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			int index = i*depthFrame.mapWidth + j;
			auto tmpDepth = depthFrame.depthValue[index];
			if (i >= depthFrame.realHeight)
			{
				VertexColors[index] = FColor::Black;
				continue;
			}
			if (depthFrame.depthValue[index] < value_gradient[0])
				VertexColors[index] = FColor::Black;
			else if (depthFrame.depthValue[index]>value_gradient[value_gradient.Num() - 1])
				VertexColors[index] = FColor::Black;
			else
			{
				int flag = 0;
				for (int k = 0; k < value_gradient.Num() - 1; k++)
				{
					if (depthFrame.depthValue[index] >= value_gradient[k] && depthFrame.depthValue[index] < value_gradient[k + 1])
					{
						
						VertexColors[index] = calGradientColor(k, depthFrame.depthValue[index]);
						flag = 1;
					}
				}
				if (flag == 0)
				{
					VertexColors[index] = FColor::Black;
				}
			}
		}
	}
}

FColor ReliefMap::calGradientColor(int number,int value)
{
	FColor resultColor;
	double rate = (double)(value - value_gradient[number]) / (double)(value_gradient[number + 1] - value_gradient[number]);
	if (rate == 0)
	{
		if (value == value_gradient[number])
		{
			return color_gradient[number];
		}
		else
			return FColor::Orange;
	}
	else
	{
		resultColor = color_gradient[number];
		resultColor.R -= (color_gradient[number].R - color_gradient[number + 1].R)*rate;
		resultColor.G -= (color_gradient[number].G - color_gradient[number + 1].G)*rate;
		resultColor.B -= (color_gradient[number].B - color_gradient[number + 1].B)*rate;
	}
	return resultColor;
}

void ReliefMap::drawCounterByGradient(TArray<FColor> &VertexColors, const DepthFrame &depthFrame)
{
	setMaxAndMin(depthFrame);
	calCounterValue();
	for (int i = 0; i < depthFrame.realHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			int index = i*depthFrame.mapWidth + j;
			for (int k = 0; k < counterNumber; k++)
			{
				if (depthFrame.depthValue[index] == counterValue[k])
				{
					VertexColors[index] = FColor::Black;
					break;
				}
			}
		}
	}

}

void ReliefMap::setMaxAndMin(const DepthFrame &depthFrame)
{
	minDepthValue = 256;
	maxDepthValue = 0;
	for (int i = 0; i < depthFrame.realHeight; i++)
	{
		for (int j = 0; j <depthFrame.mapWidth; j++)
		{
			int index = i*depthFrame.mapWidth + j;
			if (depthFrame.depthValue[index] > maxDepthValue)
			{
				maxDepthValue = depthFrame.depthValue[index];
			}
			if (depthFrame.depthValue[index] < minDepthValue)
			{
				minDepthValue = depthFrame.depthValue[index];
			}
		}
	}
}

void ReliefMap::calCounterValue()
{
	counterValue.Empty();
	int nowValue = minDepthValue;
	int dif = (maxDepthValue - minDepthValue) / counterNumber+1;
	for (int i = 0; i < counterNumber; i++)
	{
		counterValue.Add(nowValue);
		nowValue += dif;
	}
}

bool ReliefMap::checkCounter(int x, int y, TArray<FColor> &VertexColors, const DepthFrame &depthFrame)
{
	TArray<FColor> colorArea;
	bool checkFlag = 0;
	if (depthFrame.checkInRealMap(x + 1, y))
	{
		colorArea.Add(VertexColors[(x + 1)*depthFrame.mapWidth + y]);
	}
	if (depthFrame.checkInRealMap(x + 1, y + 1))
	{
		colorArea.Add(VertexColors[(x + 1)*depthFrame.mapWidth + y + 1]);
	}
	if (depthFrame.checkInRealMap(x, y + 1))
	{
		colorArea.Add(VertexColors[(x)*depthFrame.mapWidth + y + 1]);
	}
	FColor tmp = VertexColors[x*depthFrame.mapWidth + y];
	for (int i = 0; i < colorArea.Num(); i++)
	{
		if (tmp != colorArea[i])
		{
			checkFlag = 1;
			break;
		}
	}
	if (checkFlag)
		return true;
	else
		return false;
}

void ReliefMap::drawContourByThreshold(TArray<FColor> &VertexColors, const DepthFrame &depthFrame)
{
	counterFlag.Init(0, depthFrame.sumNumber);
	for (int i = 0; i < depthFrame.mapHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			if (checkCounter(i, j,VertexColors,depthFrame))
				counterFlag[i*depthFrame.mapWidth + j] = 1;
		}
	}
	for (int i = 0; i < depthFrame.mapHeight; i++)
	{
		for (int j = 0; j < depthFrame.mapWidth; j++)
		{
			int index = i*depthFrame.mapWidth + j;
			if (counterFlag[index])
				VertexColors[index] = FColor::Black;
		}
	}
}
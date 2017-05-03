// Fill out your copyright notice in the Description page of Project Settings.

#include "ARSandBox.h"
#include "ImageProcessor.h"


// Sets default values
AImageProcessor::AImageProcessor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

void AImageProcessor::imageFiltering(TArray<int> &depthValue)
{
	/*for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			int index = i*mapWidth + j;
			if (depthValue[index] == 255)
			{
				depthValue[index] = 0;
			}
		}
	}*/
}

TArray<int> AImageProcessor::pixelFilter(const DepthFrame &depthFrame)
//TArray<int> AImageProcessor::pixelFilter(const TArray<int> depthValue)
{	
	TArray<int> smoothDepthArray;
	// ������������ֵ��ȷ����������ȷ�ķ�Χ��
	int widthBound = 512 - 1;
	int heightBound = 424 - 1;

	// ����ÿ������
	for (int depthArrayRowIndex = 0; depthArrayRowIndex< depthFrame.realHeight; depthArrayRowIndex++)
	{
		// ����һ�������е�ÿ������
		for (int depthArrayColumnIndex = 0; depthArrayColumnIndex < depthFrame.mapWidth; depthArrayColumnIndex++)
		{
			depthIndex = depthArrayColumnIndex + (depthArrayRowIndex * depthFrame.mapWidth);

			// ������Ϊ���ֵΪ0�����ؼ�Ϊ��ѡ����
			if (depthFrame.depthValue[depthIndex] == 0)
			{
				// ͨ���������������ǿ��Լ���õ����صĺ�������
				int x = depthIndex % depthFrame.realHeight;
				int y = (depthIndex - x) / depthFrame.realHeight;

				// filter collection ���������˲�����ÿ�����ֵ��Ӧ��Ƶ�ȣ��ں���
				// ���ǽ�ͨ�������ֵ��ȷ������ѡ����һ��ʲô���ֵ��
				// 5*5���򣬳�ȥ���ĵĺ�ѡ���أ������24 �����ֵ
				unsigned short filterCollection[24][2] = { 0 };

				// �������ڷ��������������������ں�������ȷ����ѡ�����Ƿ��˲�
				int innerBandCount = 0;
				int outerBandCount = 0;

				// �����ѭ��������Ժ�ѡ����Ϊ���ĵ�5 X 5���������н��б��������ﶨ���������߽硣�����
				// ��������ڵ�����Ϊ���㣬��ô���ǽ���¼������ֵ�����������ڱ߽�ļ�������һ�����������
				// �߹��趨����ֵ����ô���ǽ�ȡ�˲�����ͳ�Ƶ����ֵ��������Ƶ����ߵ��Ǹ����ֵ��Ӧ���ں�ѡ
				// ������
				// �������ڷ������ض࣬�򽫺�ѡ���ظ�ֵΪ�����������ֵ��
				for (int yi = -2; yi < 3; yi++)
				{
					for (int xi = -2; xi < 3; xi++)
					{
						// yi��xiΪ������������ں�ѡ���ص�ƽ����

						// ���ǲ�Ҫxi = 0&&yi = 0���������Ϊ��ʱ�����ľ��Ǻ�ѡ����
						if (xi != 0 || yi != 0)
						{
							// ȷ���������������ͼ�е�λ��
							int xSearch = x + xi;
							int ySearch = y + yi;

							// ���������ص�λ���Ƿ񳬹���ͼ��ı߽磨��ѡ������ͼ��ı�Ե��
							if(depthFrame.checkInRealMap(xSearch,ySearch))
							{
								int index = xSearch + (ySearch * depthFrame.mapWidth);
								// ����ֻҪ������
								if (depthFrame.depthValue[index] != 0)
								{
									// ����ÿ�����ֵ��Ƶ��
									for (int i = 0; i < 24; i++)
									{
										if (filterCollection[i][0] == depthFrame.depthValue[index])
										{
											// ����� filter collection���Ѿ���¼����������
											// �������ȶ�Ӧ��Ƶ�ȼ�һ
											filterCollection[i][1]++;
											break;
										}
										else if (filterCollection[i][0] == 0)
										{
											// ���filter collection��û�м�¼������
											// ��ô��¼
											filterCollection[i][0] = depthFrame.depthValue[index];
											filterCollection[i][1]++;
											break;
										}
									}

									// ȷ���������ĸ��߽��ڵ����ز�Ϊ�㣬����Ӧ��������һ
									if (yi != 2 && yi != -2 && xi != 2 && xi != -2)
										innerBandCount++;
									else
										outerBandCount++;
								}
							}
						}
					}
				}

				// �жϼ������Ƿ񳬹���ֵ�����������ڷ������ص���Ŀ��������ֵ��
				// ��Ҫ�����з����������ֵ��Ӧ��ͳ������
				if (innerBandCount >= innerBandThreshold || outerBandCount >= outerBandThreshold)
				{
					short frequency = 0;
					short depth = 0;
					// ���ѭ����ͳ�����з����������ֵ��Ӧ������
					for (int i = 0; i < 24; i++)
					{
						// ��û�м�¼���ֵʱ���޷������ֵ�����أ�
						if (filterCollection[i][0] == 0)
							break;
						if (filterCollection[i][1] > frequency)
						{
							depth = filterCollection[i][0];
							frequency = filterCollection[i][1];
						}
					}
					smoothDepthArray.Add(depth);
				}
				else
				{
					smoothDepthArray.Add(0);
				}
			}
			else
			{
				// ������ص����ֵ��Ϊ�㣬����ԭ���ֵ
				smoothDepthArray.Add(depthFrame.depthValue[depthIndex]);
			}
		}
	}
	return smoothDepthArray;
}
// maze.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "maze.h"
#include <String>
const int Max = 100;

bool PrintMap(char* fName, char map[100][100], int maxWidth, int maxHeight)
{
	ofstream outputFile(fName);
	if (!outputFile)
	{
		return 0;
	}
	for (int i = 0; i < maxHeight; i++)
	{
		for (int j = 0; j < maxWidth; j++)
		{
			outputFile << map[i][j];
		}
		outputFile << "\n";
	}
	outputFile.close();
	return 1;
}
void WaveDirection(int x, int y, int step, int newMap[Max][Max])
{
	if (newMap[x][y] != wall && newMap[x][y] == noWall)
	{
		newMap[x][y] = step + 1;
	}
}
bool WavePropagation(int xA, int yA, int xB, int yB, int newMap[Max][Max], int maxWidth, int maxHeight)
{
	int step = 0;
	bool rightWay = true;
	newMap[yB][xB] = 0;
	while (rightWay)
	{
		rightWay = false;
		for (int i = 0; i < maxWidth; i++)
			for (int j = 0; j < maxHeight; j++)
			{
				if (newMap[j][i] == step)
				{
					WaveDirection(j + 1, i, step, newMap); //низ
					WaveDirection(j - 1, i, step, newMap); //верх
					WaveDirection(j, i - 1, step, newMap); //лево
					WaveDirection(j, i + 1, step, newMap); //право
				}
			}
		step++;
		rightWay = true;
		if (newMap[yA][xA] != noWall || step > maxWidth * maxHeight)
		{
			rightWay = false;
		}
	}
	return 1;

}
bool DrawWay(int x, int y, char map[Max][Max], int newMap[Max][Max], int step)
{
	if (newMap[x][y] == step)
	{
		map[x][y] = '.';
		return 0;
	}
	return 1;
}
void FindWay(int bx, int by, int newMap[Max][Max], char map[Max][Max])
{
	int step = newMap[by][bx];
	bool nextStep;
	while (step > 1)
	{
		step--;
		nextStep = true;
		nextStep = DrawWay(by + 1, bx, map, newMap, step);
		if (!nextStep)
		{
			by++;
			continue;
		}
		nextStep = DrawWay(by - 1, bx, map, newMap, step);
		if (!nextStep)
		{
			by--;
			continue;
		}
		nextStep = DrawWay(by, bx + 1, map, newMap, step);
		if (!nextStep)
		{
			bx++;
			continue;
		}
		nextStep = DrawWay(by, bx - 1, map, newMap, step);
		if (!nextStep)
		{
			bx--;
		}
	}
}
bool DrawingMap(char* iFileName, char* outputFileName)
{
	ifstream inputFile(iFileName);
	if (!inputFile) return 1;
	string line = "";
	char map[100][100];
	int width, nA = 0, nB = 0, xA = 0, yA = 0, xB = 0, yB = 0, newMap[Max][Max], maxWidth = 0, maxHeight = 0;
	while (!inputFile.eof())
	{
		std::getline(inputFile, line);
		if (line.length() > maxWidth)
		{
			maxWidth = line.length();
		}
		width = 0;
		while (width < line.length())
		{
			if (line[width] == '#')
			{
				newMap[maxHeight][width] = wall;
			}
			else
			{
				newMap[maxHeight][width] = noWall;
			}
			if (line[width] == 'A')
			{
				nA++;
				xA = width;
				yA = maxHeight;
			}
			if (line[width] == 'B')
			{
				nB++;
				xB = width;
				yB = maxHeight;
			}
			map[maxHeight][width] = line[width];
			width++;
		}
		maxHeight++;
	}
	inputFile.close();
	if ((nA != 1 || nB != 1) || maxWidth > Max || maxHeight > Max)
	{
		return 0;
	}
	if (WavePropagation(xA, yA, xB, yB, newMap, maxWidth, maxHeight))
	{
		int step = newMap[yA][xA];
		FindWay(xA, yA, newMap, map);
		PrintMap(outputFileName, map, maxWidth, maxHeight);
	}
	return 1;
}
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		return 0;
	}
	char *inputFileName = argv[1];
	char *outputFileName = argv[2];
	DrawingMap(inputFileName, outputFileName);
	return 0;
}


// maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "maze.h"


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
void FillMap(int x, int y, int step, int newMap[100][100])
{
	if (newMap[x][y] != wall && newMap[x][y] == noWall) // низ
	{
		newMap[x][y] = step + 1;
	}
}
bool WavePropagation(int xA, int yA, int xB, int yB, int newMap[100][100], int maxWidth, int maxHeight)
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
					FillMap(j + 1, i, step,  newMap); //низ
					FillMap(j - 1, i, step, newMap); //верх
					FillMap(j, i - 1, step, newMap); //лево
					FillMap(j, i + 1, step, newMap); //право
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
bool DrawWay(int x, int y, char map[100][100], int newMap[100][100], int step)
{
	if (newMap[x][y] == step)
	{
		map[x][y] = '.';
		return 0;
	}
	return 1;
}
void FindWay(int bx, int by, int newMap[100][100], char map[100][100])
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
			}
			nextStep = DrawWay(by - 1, bx, map, newMap, step);
			if (!nextStep)
			{
				by--;
			}
			nextStep = DrawWay(by, bx + 1, map, newMap, step);
			if (!nextStep)
			{
				bx++;
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
	if (!inputFile)
	{
		return 1;
	}
	string line = "";
	char map[100][100];
	int width, nA = 0, nB = 0, len, xA = 0, yA = 0, xB = 0, yB = 0, newMap[100][100], maxWidth = 0, maxHeight = 0;
	while (!inputFile.eof())
	{
		getline(inputFile, line);
		len = line.length();
		if (len > maxWidth)
		{
			maxWidth = len;
		}
		width = 0;

		while (width < len)
		{			
			if (line[width] == '#'  )
			{
				newMap[len][width] = wall; //стена
			}
			else
			{
				newMap[len][width] = noWall;//индикатор еще не ступали сюда
			}
			if (line[width] == 'A')
			{
				nA++;
				xA = width;
				yA = len;				
		    }
			if (line[width] == 'B')
			{
				nB++;
				xB = width;
				yB = len;
			}
			if (nA == 2 || nB == 2)
			{
				inputFile.close();
				return 0;
			}
			map[maxHeight][width] = line[width];
			width++;
		}
		maxHeight++;
	}

	inputFile.close();
	if (nA == 0 || nB == 0)
	{
		return 0;
	}
	if (maxWidth > 100 && maxHeight > 100)
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


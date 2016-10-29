// maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "maze.h"
bool FindErrors(char* firstFileName, char* secondFileName)
{

	ifstream inputFile(firstFileName);

	if (!inputFile)
	{
		printf("Error with opening input file %s\n", inputFile);
		return 1;
	}

	ofstream outputFile(secondFileName);
	if (!outputFile)
	{
		printf("Error with opening output file %s\n", secondFileName);
		return 1;
	}
	inputFile.close();
	outputFile.close();


	if (strlen(firstFileName) == 0 || strlen(secondFileName) == 0)
	{
		printf("Uncorrect input or output file! \n");
		return 1;
	}
	return 0;
}

bool FindRoad(int xA, int yA, int xB,int  yB)
{
	int step = 0;
	bool add = true;
	newMap[yB][xB] = 0;
	while (add)
	{
		add = false;
		for (int i = 0; i < maxWidth; i++)
			for (int j = 0; j < maxHigh; j++)
			{
				if (newMap[j][i] == step)
				{
					if (newMap[j + 1][i] != -2 && newMap[j + 1][i] == -1) // низ
					{
						newMap[j + 1][i] = step + 1;
					}

					if (newMap[j - 1][i] != -2 && newMap[j - 1][i] == -1)  //верх
					{
						newMap[j - 1][i] = step + 1;
					}

					if (newMap[j][i - 1] != -2 && newMap[j][i - 1] == -1) //лево
					{
						newMap[j][i - 1] = step + 1;
					}

					if (newMap[j][i + 1] != -2 && newMap[j][i + 1] == -1)
					{
						newMap[j][i + 1] = step + 1;
					}
				}
			}
		step++;
		add = true;
		if (newMap[yA][xA] != -1)
		{
			add = false;
		}

		if (step > maxWidth * maxHigh)
		{
			add = false;
			return 0;
		}

	}

	return 1;

}

void GoToStart(int bx, int by)
{
	
	    int step = newMap[by][bx];
		bool flag;
		while (step > 1)
		{
			step--;
			flag = true;
			if (newMap[by + 1][bx] == step && flag)
			{
				map[by + 1][bx] = '.';
				flag = false;
				by = by + 1;
			}

			if (newMap[by - 1][bx] == step && flag)
			{
				map[by - 1][bx] = '.';
				flag = false;
				by = by - 1;
			}

			if (newMap[by][bx + 1] == step && flag)
			{
				map[by][bx + 1] = '.';
				flag = false;
				bx = bx + 1;
			}

			if (newMap[by][bx - 1] == step && flag)
			{
				map[by][bx - 1] = '.';
				flag = false;
				bx = bx - 1;
			}
		}
}

bool FillArray(char* iFileName)
{
	ifstream inputFile(iFileName);
	string line = "";
	int width, nA = 0, nB = 0, len, xA = 0, yA = 0, xB = 0, yB = 0;
	while (!inputFile.eof())
	{
		//high++;
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
				newMap[maxHigh][width] = -2; //стена
			}
			else
			{
				newMap[maxHigh][width] = -1;//индикатор еще не ступали сюда
			}

			if (line[width] == 'A')
			{
				nA++;
				xA = width;
				yA = maxHigh;
				
		    }

			if (line[width] == 'B')
			{
				nB++;
				xB = width;
				yB = maxHigh;
			}

			if (nA == 2 || nB == 2)
			{
				return 0;
			}

			map[maxHigh][width] = line[width];

			width++;
			

		}
		maxHigh++;
	}

	inputFile.close();
	if (nA == 0 || nB == 0)
	{
		return 0;
	}

	if (maxWidth > 100 && maxHigh > 100)
	{
		return 0;
	}

	if (FindRoad(xA, yA, xB, yB))
	{
		int step = newMap[yA][xA];
		GoToStart(xA, yA);
	}

	return 1;
}
void PrintMap(char* fName)
{
	ofstream outputFile(fName);
	for (int i = 0; i < maxHigh; i++)
	{
		for (int j = 0; j < maxWidth; j++)
		{
			outputFile << map[i][j];
		}
		outputFile << "\n";
	}
	outputFile.close();
}

int main(int argc, char* argv[])
{
	printf("\n ------------------------------ \n");
	if (argc != 3)
	{
		return 0;
	}
	char *inputFileName = argv[1];
	char *outputFileName = argv[2];
	if (!FindErrors(inputFileName, outputFileName))
	{
		if (FillArray(inputFileName))
		{
			PrintMap(outputFileName);		
		}		
	}
	return 0;
}


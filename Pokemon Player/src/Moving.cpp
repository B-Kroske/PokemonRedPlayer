#include "../headers/Moving.h"

using namespace std;

void Moving::followWall()
{
	//PLAN: Go counter-clockwise around the map
	//	1. Go a direction determined by where you entered from
	//	2. When you hit a wall, start bumping along it
	//	3. When you don't bump off the wall, then keep going that way and 
	//      bumping along another wall
	//	4. If you hit a corner (you bump off both directions), start 
	//		going the opposite of your bump direction

	//WHen going right, bump along bottom wall
	//going up, bump along right
	//Going left, bump along up
	//going down, bump along left

	//Determine where you currently are
	int currMap = read2Bytes(MAP_NAME);
	int currPos;
	int newPos= -1;
	int currDir;
	int bumpDir[] = {Control::RIGHT, Control::LEFT, Control::UP, Control::DOWN};

	//Find the starting direction
	currDir = findStartingDir();

	//Move to a wall to get bearings
	while(newPos != currPos)
	{
		//cout << "Step Right" << endl;
		currPos = newPos;
		Control::go(currDir);
		newPos = read2Bytes(Y_POS);
		
	}
	//Move along the wall
	currDir = (currDir % 2 == 0) ? currDir + 1 : currDir - 1;
	//cout << "Current direction: " << currDir << endl;

	//Walk along the outer wall of an area until we enter a new area
	while(currMap == read2Bytes(MAP_NAME))
	{
		//cout << "Current Position: " << currPos << endl;

		//Try to bump on the wall
		Control::go(bumpDir[currDir]);
		Sleep(READ_POS_SLEEP);
		newPos = read2Bytes(Y_POS);

		//cout << "After bump: " << newPos << endl;
		//If newPos and currPos differ, we are moving in a different direction
		if(newPos != currPos)
		{
			currDir = bumpDir[currDir];
		}
		//Otherwise, keep moving along the wall
		else
		{
			Control::go(currDir);
			Sleep(READ_POS_SLEEP);
			//cout << "After real move: " << newPos << endl;
		}

		//Check that we moved
		newPos = read2Bytes(Y_POS);
		

		//We still didn't move
		if(currPos == newPos)
		{
			//Go away from the wall (along another wall)
			currDir = (currDir % 2 == 0) ? currDir + 1 : currDir - 1;
			//cout << "REVERSING TO GO : " << currDir << endl;
			//Control::go(currDir);
			//newPos
		}

		currPos = newPos;
		//We have tried 3 directions and none have worked
		//if(currPos
	}

	
}



int Moving::read2Bytes(int startPos)
{
	char vals[2];

	//Dump the ram and open the file
	Control::dumpRam();
	ifstream infile ("./Emulator/cgb_wram.bin", ios::in|ios::binary);

	//Get the x and y positions
	infile.seekg(startPos, ios::beg);
	infile.read(vals, 2);

	infile.close();
	int tmp = vals[0] << 8;
	//cout << (int)vals[0] << " " << tmp << " " << (int)vals[1] << endl;

	return (int)(((int)vals[0] << 8) + (int)vals[1]);
}

int Moving::findStartingDir()
{
	int xSize;
	int ySize;
	int mapSize = read2Bytes(MAP_SIZE);

	//Calculate the size of the map
	xSize = (mapSize & 0xFF) * 2;
	ySize = (mapSize >> 8) * 2;

	int xPos;
	int yPos;
	int currPos;

	currPos = read2Bytes(Y_POS);
	xPos = currPos & 0xFF;
	yPos = currPos >> 8;
	
	//Pick a starting direction based on how close we are to different walls
	//Closer to the top of the area
	cout << ySize << " " << yPos << endl;
	cout << xSize << " " << xPos << endl;

	if(yPos < (ySize / 2))
	{
		//Closer to left or right
		//Closer to left side
		if(xPos < (xSize / 2))
		{
			if(yPos < xPos)
				return Control::LEFT;
			else
				return Control::DOWN;

		}
		else
		{
			if(yPos < (xSize - xPos))
				return Control::LEFT;
			else
			{
				cout << "CLOSER TO TOP" << endl;
				return Control::UP;
			}
		}
	}
	else
	{
		if(xPos < (xSize / 2))
		{
			if((ySize - yPos) < xPos)
				return Control::RIGHT;
			else
				return Control::DOWN;

		}
		else
		{
			if((ySize - yPos) < (xSize - xPos))
				return Control::RIGHT;
			else
			{
				cout << "CLOSER TO BOTTOM" << endl;
				return Control::UP;
			}
		}
	}
}
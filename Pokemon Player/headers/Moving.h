#ifndef MOVING_H
#define MOVING_H

#include <iostream>
#include <fstream>
#include "../headers/Control.h"

class Moving {

    public:
		static void followWall();
		//Returns an int containg coordinates stored as a single integer due to 
		//bit shifting
		static int read2Bytes(int start);
		static int findStartingDir();

    private:
		static const int MAP_NAME = 0x136A;
		static const int Y_POS = 0x1361;
		static const int READ_POS_SLEEP = 500;
		static const int MAP_SIZE = 0x1368;
		
};
#endif
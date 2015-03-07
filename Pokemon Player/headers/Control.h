#ifndef CONTROL_H
#define CONTROL_H

#include <windows.h>
#include <iostream>

class Control {

    public:
        static bool pressA();
		static bool pressB();
		//Press B alot to skip the boring stuff
		static bool mashB(int times);
		static bool pressStart();
		static bool pressSelect();
		static bool dumpRam();
		static char readRam();
		static bool goUp();
		static bool goDown();
		static bool goLeft();
		static bool goRight();
		static bool go(int dir);

		//Constants
		static const int UP = 0;
		static const int DOWN = 1;
		static const int LEFT = 2;
		static const int RIGHT = 3;

    private:
        static bool pressKey(short vk);
};
#endif
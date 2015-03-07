#include "../headers/Battle.h"
#include "../headers/Data.h"
#include "../headers/Moving.h"
using namespace std;

int main()
{
	Data dat;
	
	Sleep(5000);
	//Battle battleMode(dat);
	//battleMode.fight();

	Moving::followWall();
	return 0;
}
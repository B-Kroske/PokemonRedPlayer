#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Move {
    int pow;
    int type;
    int acc;
	int pp;
    
    Move(int p, int a, int t, int powPoint)
    {
        pow = p;
        acc = a;
        type = t;
		pp = powPoint;
    }
    
    Move()
    {
        pow = 0;
        acc = 0;
        type = 0;
		pp = 0;
    }
};

struct Result {
	int teamPos;
	int move;
	double maxDamage;
	double takeDamage;

	Result(int pos, int m, int dam, int take)
    {
        teamPos = pos;
		move = m;
		maxDamage = dam;
		takeDamage = take;
    }
    
    Result()
    {
        teamPos = 0;
		move = 0;
		maxDamage = 0;
		takeDamage = 0;
    }
};

class Data {
	public:
		Data();
		Move getMove(int index);
		int convGameType(int t);
		int atkTarg(int t);
		static bool sortResults(Result a, Result b);

	private:
		int physOrSpec[15];
		int gameToMine[26];
		int csvToMine[16];
		Move moveList[166];
		bool initMoves();

		vector<string> &split(const string &s, char delim, vector<string> &elems);
		vector<string> split(const string &s, char delim);
		int StringToNumber(string &Text );
};
#endif
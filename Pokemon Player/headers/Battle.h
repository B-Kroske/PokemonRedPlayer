#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include "../headers/Pokemon.h"
#include "../headers/Control.h"
#include "../headers/Data.h"

class Battle {

	public:
		Battle(Data &d);
		~Battle();
		void fight();

	private:
		//Constants
		static const int ATTACK = 1;
		static const int SWITCH = 2;
		static const int HEAL = 3;
		
		static const int PLAYER_LEAD = 0;
		static const int OPPONENT_LEAD = -1;

		//static constants for various memory locations
		static const int BATTLE_FLAG = 0x1057;
		static const int OPPONENT_LEAD_MEM = 0x0FDA;
		static const int PLAYER_LEAD_MEM = 0x1009;
		static const int PLAYER_TEAM_COUNT_MEM = 0x1163;
		static const int PLAYER_TEAM_MEM = 0x116B;

		//Some Sleep times 
		static const int ATTACK_SLEEP = 5000;
		static const int MENU_SLEEP = 500;
		static const int PRE_HEAL_SLEEP = 2000;

		void init();
		//The current state of the player's Team
		Pokemon playerTeam[6];
		int teamCount;
		int nextMove[2];

		//The opponent
		Pokemon opponent;

		//Variables to track the state of a battle
		int pkmOut;
		int currMove;
		int itemPos;
		int currSelPoke;

		//Storage for various things that may be useful
		Data dat;
		char * memBlock;

		bool readRam();
		bool buildTeam();
		//Determines the best action to take on a specific turn. Sets the values in "nextMove".
		void determineAction();
		//Attack with the i'th move
		void attack(int atkIndex);

		//Switch to the i'th pokemon
		void swap(int pkmnIndex);

		//Use a full heal on the i'th pokemon (assuming there are any full heals in the first item slot)
		void heal(int pkmnIndex);

		//Updates the i'th position pokemon on the player's team. If pos equals -1, update the opposing pokemon.
		bool updatePoke(int pos);
		double calcDamage(Pokemon atk, Pokemon def, int move, bool isMax);
		//A pokmeon's info is stored in a longer format outside of battle. Pass the address of the start of the pokemon's info
		Pokemon loadLongPoke(int addr);
		Pokemon loadShortPoke(int addr);
		//All stats are stored as 2-byte values. Pass the address of the first stat bit
		int loadStat(int addr);
};
#endif
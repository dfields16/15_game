#include "GameManager.h"

GameManager::GameManager(Difficulty d):
	difficulty(d)
	{
		switch(difficulty){
			case Beginner:
				//gamePtrn = BPTRN;
			break;
			case Intermediate:
				//gamePtrn = IPTRN;
			break;
			case Advanced:
				//gamePtrn = APTRN;
			break;
			case Expert:
				//gamePtrn = EPTRN;
			break;
		}
	}
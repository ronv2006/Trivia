#pragma once
#include <string>
#include <mutex>
class RoomData {
public:
	unsigned int _id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
    

    
};
#ifndef __SCORE__H__
#define __SCORE__H__


#include "cocos2d.h"
USING_NS_CC;

#include <vector>
#include <string>

class ScoreDate
{
public:
	static ScoreDate* getInstance();
	static void addScore(int num, std::string &name);
	static std::vector<std::string> names;
	static int numbers[20];
	static void getWanted();
	bool init();


private:
	static ScoreDate* sharedDataControl;
	
	static int top;
	
};

#endif // !__SCORE__H__

#include "ScoreData.h"
#include "cstdlib"
#include "cstdio"
#include "cocos2d.h"
#include "base/CCUserDefault.h"

ScoreDate* ScoreDate::sharedDataControl = nullptr;
int ScoreDate::top = 0;
int ScoreDate::numbers[20] = {0};
std::vector<std::string> ScoreDate::names = std::vector<std::string>();

ScoreDate* ScoreDate::getInstance()
{
	if(sharedDataControl == nullptr){
		sharedDataControl = new ScoreDate();
		if(!sharedDataControl->init()){
			delete sharedDataControl;
			sharedDataControl = nullptr;
			CCLOG("ERROR: Could not init ScoreDate");
		}
	}
	return sharedDataControl;
}

bool ScoreDate::init()
{
	char str[5];
	for (int i = 0; i < 12; i++)
	{
		sprintf(str, "%d", i);
		numbers[i] = UserDefault::getInstance()->getIntegerForKey(str, 0);
		//UserDefault::getInstance()->setIntegerForKey(str, 0);
		CCLOG("numbers %d is : %d", i, numbers[i]);
		sprintf(str, "%d", i+100);
		names.push_back( UserDefault::getInstance()->getStringForKey(str, std::string("God")) );
		//UserDefault::getInstance()->setStringForKey(str, std::string("God"));

		

	}


	return true;
}
void ScoreDate::addScore(int num, std::string &name)
{
	if(num < numbers[11])
		return;

	CCLOG("Before");
	for (int i = 0; i < 12; i++)
	{
		CCLOG("   %d", numbers[i]);
	}

	char str[10];
	int index = 11;
	for (index = 0; index < 12; index++)
	{
		if (numbers[index] < num)
		{
			break;
		}
	}
	if(index == 12) return;
	for (int i = 11; i > index; i--)
	{
		numbers[i] = numbers[i-1];
		names[i] = names[i-1];
	}

	numbers[index] = num;
	names[index] = name;

	CCLOG("After");
	for (int i = 0; i < 12; i++)
	{
		CCLOG("%s   %d", names[i].c_str(), numbers[i]);
	}

	for (int i = 0; i < 12; i++)
	{
		sprintf(str, "%d", i);
		UserDefault::getInstance()->setIntegerForKey(str, numbers[i]);
		sprintf(str, "%d", i+100);
		UserDefault::getInstance()->setStringForKey(str, names[i]);
	}
}

void  ScoreDate::getWanted()
{
	names.clear();
	char str[5];
	for (int i = 0; i < 12; i++)
	{
		sprintf(str, "%d", i);
		numbers[i] = UserDefault::getInstance()->getIntegerForKey(str, 0);
		//UserDefault::getInstance()->setIntegerForKey(str, 0);
		CCLOG("numbers %d is : %d", i, numbers[i]);
		sprintf(str, "%d", i+100);
		names.push_back( UserDefault::getInstance()->getStringForKey(str, std::string("God")) );
		//UserDefault::getInstance()->setStringForKey(str, std::string("God"));



	}
}
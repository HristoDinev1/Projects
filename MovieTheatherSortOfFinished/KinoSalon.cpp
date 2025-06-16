#include <iostream>
#include "AppManager.h"


int main()
{
	AppManager& appManager = AppManager::getInstance();
	appManager.run();
}
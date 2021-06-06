#pragma once

#include <string>
#include "./../Controllers/MenuController.h"
#include "./../Controllers/AuthController.h"

class Navigator
{
public:
	static void goTo(std::string path);
};


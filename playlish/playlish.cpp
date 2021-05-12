// playlish.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "./App.h"
// TODO: config library does network: https://github.com/nlohmann/json
// #include "./include/tao/config.hpp"



int main()
{
	std::cout << __cplusplus << std::endl;
	App::run();	
}
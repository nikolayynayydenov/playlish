#pragma once

class MenuController
{
public:
	static void handle();

	static void showOptions();

	static int processInput();

	static void processGuestInput(int input);

	static void processLoggedInInput(int input);

protected:
	static void showLoggedInOptions();

	static void showGuestOptions();
};


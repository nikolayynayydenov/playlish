#include <iostream>
#include <string>
#include "./App.h"
#include "./DB.h"
#include <SQLAPI.h>

int main(int argc, char* argv[]) {
	try {
		App::run();
	}
	catch (SAException& x) {
		DB::conn().Rollback();
		printf("SAException: %s\n", x.ErrText().GetMultiByteChars());
	}

	return 0;
}
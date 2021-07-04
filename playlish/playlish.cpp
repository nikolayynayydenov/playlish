#define CATCH_CONFIG_RUNNER
#include "./Common/DB.h"
#include "./Common/Navigator.h"

#include "./Tests/catch_amalgamated.hpp"

int main(int argc, char* argv[]) {
	try {
		Navigator::goTo("menu");

		//int result = Catch::Session().run(argc, argv);
	}
	catch (SAException& x) {
		DB::conn().Rollback();
		printf("SAException: %s\n", x.ErrText().GetMultiByteChars());
	}
	catch (...) {
		printf("General exception.");
	}

	return 0;
}
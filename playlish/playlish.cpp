#include "./Common/DB.h"
#include "./Common/Navigator.h"

int main(int argc, char* argv[]) {
	try {
		Navigator::goTo("menu");
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
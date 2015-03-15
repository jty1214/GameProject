#include "GPGame.h"
#include "Initializer.h"
#include "ArgumentHandler.h"

__int32 main(int argc, char* argv[])
{
	Initialize();
	_ArgumentRegister::process(argc, argv);
	return 0;
}
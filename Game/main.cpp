#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Game.h"

int main()
{
	Game game;
	game.Run();

	return 0;
}

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BurgerTime.h"

// resolves a linker error with sdl macro decl
#undef main
int main(int, char* [])
{
	BurgerTime engine;
	engine.Run();

	return 0;
}

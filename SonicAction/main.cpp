#include <DxLib.h>
#include "Game.h"

#ifdef _DEBUG
int main() 
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif // _DEBUG
{
	Game::GetInstance().Init();
	Game::GetInstance().Run();
	Game::GetInstance().End();
}
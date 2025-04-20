#include "pch.h"
#include "Tetris.h"

int main()
{
	CTetris tetris;
	const int nFPS = 5;
	const int nSleepTime = 1000 / nFPS; // 게임 속도 설정
	while (true)
	{
		ST_KEY_STATE stKeyState; //키 class (AWD)
		stKeyState.Clear(); // 키 감지 초기화

		tetris.Input(&stKeyState); // 키 입력 감지
		tetris.Update(stKeyState); // 키 입력 행동
		tetris.Render(); // 랜더링

		if (tetris.IsGameOver() && _kbhit()) // Game OVER 검사
		{
			(void)_getch();
			tetris = CTetris();
		}

		Sleep(nSleepTime); //게임 딜레이
	}
	return 0;
}

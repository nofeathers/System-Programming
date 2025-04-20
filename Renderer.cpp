#include "pch.h"
#include "Renderer.h"

void CRenderer::Clear(void)
{
	for (int y = 0; y < g_nScreenHeight; y++)
	{
		memset(m_szScreenBuffer[y], ' ', g_nScreenWidth);
		m_szScreenBuffer[y][g_nScreenWidth] = 0;
	}
}

void CRenderer::Draw(int x, int y, const char* pszBuffer, int nBufferSize)
{
	for (int i = 0; i < nBufferSize; i++) // x, y 블록 좌표 설정
	{
		int nPosX = x + i;
		if (' ' != pszBuffer[i])
			m_szScreenBuffer[y][nPosX] = pszBuffer[i];
	}
}

void CRenderer::Render(void) // 화면 버퍼를 콘솔에 출력 함수
{
	system("cls");		//화면 버퍼의 내용을 콘솔에 출력

	for (int y = 0; y < g_nScreenHeight; y++)
		printf("%s\n", m_szScreenBuffer[y]);	//화면 깜빡임 방지를 위해 시스템 명령어 사용
}

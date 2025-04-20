#pragma once

// 화면 크기 상수
const int g_nScreenWidth = 30;    // 화면 가로 크기
const int g_nScreenHeight = 25;   // 화면 세로 크기

// 화면 렌더링 담당 클래스
class CRenderer
{
	char m_szScreenBuffer[g_nScreenHeight][g_nScreenWidth + 1];  // 화면 버퍼

public:
	void Clear(void);                                   
	void Draw(int x, int y, const char* pszBuffer, int nBufferSize);  
	void Render(void);                                   
};


#pragma once

#include "RenderObject.h"
#include "Tetrimino.h"

// 게임 맵의 크기 상수
const int g_nMapWidth = 16;    // 맵의 가로 크기
const int g_nMapHeight = 20;   // 맵의 세로 크기

// 게임 맵을 관리하는 클래스
class CMap : public CRenderObject
{
private:
	char m_szMapData[g_nMapHeight][g_nMapWidth + 1];  // 맵 데이터 배열

public:
	CMap() {
		Clear();
	}

	void Clear(void);                    // 맵 초기화
	bool IsCollide(const CTetrimino* pTetrimino) const;  // 벽 충돌 검사
	void Pile(const CTetrimino* pTetrimino);            // 블록 쌓기
	void OnDraw(CRenderer* pRenderer) override;          // 화면에 맵 그리기
};


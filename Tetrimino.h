#pragma once

#include "RenderObject.h"

enum E_TETRIMINO_TYPE
{
	TETRIMINO_I = 0,
	TETRIMINO_O,
	TETRIMINO_J,
	TETRIMINO_L,
	TETRIMINO_S,
	TETRIMINO_Z,
	TETRIMINO_T,
	TETRIMINO_COUNT
};

class CTetrimino : public CRenderObject
{
private:
	char m_szBlock[4][4][4 + 1];
	int m_nRotation;

public:
	// 회전 상태 초기화 및 블록 배열 초기화
	CTetrimino() : m_nRotation(0) {
		memset(m_szBlock, 0, sizeof(m_szBlock));
	}
	
	void Reset(int nType);
	void OnDraw(CRenderer* pRenderer) override;
	
	// 블록 이동
	void Move(int dx, int dy) {
		m_nPosX += dx;
		m_nPosY += dy;
	}
	
	// 블록 회전 (90도)
	void Rotate() {
		m_nRotation = (m_nRotation + 1) % 4;
	}
	
	// 특정 위치의 블록 문자 반환
	char GetBlock(int rotation, int y, int x) const {
		return m_szBlock[rotation][y][x];
	}

	// 현재 회전 상태 반환
	int GetRotation() const {
		return m_nRotation;
	}
};


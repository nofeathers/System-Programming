#pragma once

#include "Renderer.h"
#include "Tetrimino.h"
#include "Map.h"

/* 키 입력 상태를 저장하는 구조체 */
struct ST_KEY_STATE
{
	bool bRotateKeyDown;
	bool bLeftKeyDown;
	bool bRightKeyDown;
	bool bSmashKeyDown;

	ST_KEY_STATE() : bRotateKeyDown(false), bLeftKeyDown(false), bRightKeyDown(false), bSmashKeyDown(false) {}

	// 모든 키 상태 초기화
	void Clear(void)
	{
		bRotateKeyDown = false;
		bLeftKeyDown = false;
		bRightKeyDown = false;
		bSmashKeyDown = false;
	}
};

// 테트리스 게임의 메인 클래스
class CTetris
{
private:
	CRenderer m_Render;      // 화면 렌더링 객체
	CTetrimino m_Tetrimino;  // 현재 테트리미노 객체
	CMap m_Map;              // 게임 맵 객체
	bool m_bGameOver;        // 게임 오버 상태

public:
	CTetris(void);           // 생성자
	~CTetris(void);          // 소멸자

	void Input(ST_KEY_STATE* pKeyState);  // 키 입력 처리
	void Update(ST_KEY_STATE stKeyState); // 게임 상태 업데이트
	void Render(void);                     // 화면 렌더링
	bool IsGameOver(void) const { return m_bGameOver; }  // 게임 오버 상태 확인
};


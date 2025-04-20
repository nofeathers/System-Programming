#include "pch.h"
#include "Tetris.h"

CTetris::CTetris(void) : m_bGameOver(false)
{
    m_Tetrimino.Reset(rand() % TETRIMINO_COUNT); // 랜덤 블록 생성
    m_Map.Clear(); // 맵 초기화
}

// 소멸자
CTetris::~CTetris(void)
{
}

// 키 입력 처리 함수
void CTetris::Input(ST_KEY_STATE* pKeyState)
{
    char cKeyDown = 0;
    while (_kbhit())
        cKeyDown = static_cast<char>(_getch()); // 키 입력 감지

    if ('A' == cKeyDown || 'a' == cKeyDown)
        pKeyState->bLeftKeyDown = true; // 왼쪽 이동 키
    if ('D' == cKeyDown || 'd' == cKeyDown)
        pKeyState->bRightKeyDown = true; // 오른쪽 이동 키
    if ('W' == cKeyDown || 'w' == cKeyDown)
        pKeyState->bRotateKeyDown = true; // 회전 키
}

void CTetris::Update(ST_KEY_STATE stKeyState)
{
    if (m_bGameOver) // 게임 오버 상태면 업데이트 중단
        return;

    CTetrimino prevTetrimino = m_Tetrimino; // 이전 상태 저장
    
    if (stKeyState.bLeftKeyDown) //왼쪽으로 이동
        m_Tetrimino.Move(-1, 0);
    if (stKeyState.bRightKeyDown) //오른쪽으로 이동
        m_Tetrimino.Move(1, 0);
    if (stKeyState.bRotateKeyDown) // 블록 회전
        m_Tetrimino.Rotate();
    
    if (m_Map.IsCollide(&m_Tetrimino)) // 충돌 검사
    {
        m_Tetrimino = prevTetrimino; // 충돌 시 이전 상태로 복원
        
        if (m_Map.IsCollide(&m_Tetrimino)) // 충돌 검사
        {
            m_Map.Pile(&prevTetrimino); // 블록 맵에 쌓음
            m_Tetrimino.Reset(rand() % TETRIMINO_COUNT); // 새로운 블록 생성
            
            if (m_Map.IsCollide(&m_Tetrimino)) // 새 블록 충돌 검사
            {
                m_bGameOver = true; // 게임 오버
                return;
            }
        }
    }
    
    m_Tetrimino.Move(0, 1); // 자동으로 아래로 이동
    
    if (m_Map.IsCollide(&m_Tetrimino)) // 아래로 이동 후 충돌 검사
    {
        m_Tetrimino.Move(0, -1); // 충돌 시 이전 위치로 복원
        m_Map.Pile(&m_Tetrimino); // 블록을 맵에 쌓음
        m_Tetrimino.Reset(rand() % TETRIMINO_COUNT); // 새로운 블록 생성
        
        if (m_Map.IsCollide(&m_Tetrimino)) // 새 블록 충돌 검사
        {
            m_bGameOver = true; // 게임 오버
            return;
        }
    }
}

void CTetris::Render(void)
{
    m_Render.Clear(); // 화면 버퍼 초기화
    m_Map.OnDraw(&m_Render); // 맵 그리기
    
    if (!m_bGameOver)
    {
        m_Tetrimino.OnDraw(&m_Render); // 테트리스 그리기
    }
    else
    {
        const char* gameOverMsg = "GAME OVER";
        m_Render.Draw(2, g_nScreenHeight / 2, gameOverMsg, static_cast<int>(strlen(gameOverMsg))); // 게임 오버 메시지 표시
    }
    
    m_Render.Render(); //랜더링
}
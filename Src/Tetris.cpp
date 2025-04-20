#include "pch.h"
#include "Tetris.h"

CTetris::CTetris(void) : m_bGameOver(false)
{
    m_Tetrimino.Reset(rand() % TETRIMINO_COUNT);
    m_Map.Clear();
}

CTetris::~CTetris(void)
{
}

void CTetris::Input(ST_KEY_STATE* pKeyState) // 키 입력
{
    char cKeyDown = 0;
    while (_kbhit())
        cKeyDown = static_cast<char>(_getch());

    if ('A' == cKeyDown || 'a' == cKeyDown)
        pKeyState->bLeftKeyDown = true;
    if ('D' == cKeyDown || 'd' == cKeyDown)
        pKeyState->bRightKeyDown = true;
    if ('W' == cKeyDown || 'w' == cKeyDown)
        pKeyState->bRotateKeyDown = true;
    if ('S' == cKeyDown || 's' == cKeyDown)
        pKeyState->bSmashKeyDown = true;
}

void CTetris::Update(ST_KEY_STATE stKeyState) // 게임 플레이
{
    if (m_bGameOver)
        return;

    CTetrimino prevTetrimino = m_Tetrimino;

    if (stKeyState.bLeftKeyDown) //좌 우 블록 회전 키 입력 행동
        m_Tetrimino.Move(-1, 0);
    if (stKeyState.bRightKeyDown)
        m_Tetrimino.Move(1, 0);
    if (stKeyState.bRotateKeyDown)
        m_Tetrimino.Rotate();

    if (m_Map.IsCollide(&m_Tetrimino))
    {
        m_Tetrimino = prevTetrimino;

        if (m_Map.IsCollide(&m_Tetrimino))
        {
            m_Map.Pile(&prevTetrimino);
            m_Tetrimino.Reset(rand() % TETRIMINO_COUNT);

            if (m_Map.IsCollide(&m_Tetrimino))
            {
                m_bGameOver = true;
                return;
            }
        }
    }

    if (stKeyState.bSmashKeyDown) // 블록 바닥으로 이동
    {
        while (!m_Map.IsCollide(&m_Tetrimino))
        {
            m_Tetrimino.Move(0, 1);
        }
        m_Tetrimino.Move(0, -1);
        m_Map.Pile(&m_Tetrimino);
        m_Tetrimino.Reset(rand() % TETRIMINO_COUNT);

        if (m_Map.IsCollide(&m_Tetrimino))
        {
            m_bGameOver = true;
            return;
        }
    }
    else
    {
        m_Tetrimino.Move(0, 1);

        if (m_Map.IsCollide(&m_Tetrimino))
        {
            m_Tetrimino.Move(0, -1);
            m_Map.Pile(&m_Tetrimino);
            m_Tetrimino.Reset(rand() % TETRIMINO_COUNT);

            if (m_Map.IsCollide(&m_Tetrimino))
            {
                m_bGameOver = true;
                return;
            }
        }
    }
}

void CTetris::Render(void)
{
    m_Render.Clear();
    m_Map.OnDraw(&m_Render);

    if (!m_bGameOver)
    {
        m_Tetrimino.OnDraw(&m_Render);
    }
    else
    {
        const char* gameOverMsg = "GAME OVER";
        m_Render.Draw(2, g_nScreenHeight / 2, gameOverMsg, static_cast<int>(strlen(gameOverMsg)));
    }

    m_Render.Render();
}
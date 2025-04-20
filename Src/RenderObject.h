#pragma once

#include "Renderer.h"

class CRenderObject
{
protected:
	int m_nPosX;
	int m_nPosY;

public:
	CRenderObject() : m_nPosX(0), m_nPosY(0) {} 
	virtual ~CRenderObject() {}  
	
	virtual void OnDraw(CRenderer* pRenderer) = 0;
	
	int GetPosX() const { return m_nPosX; }
	int GetPosY() const { return m_nPosY; }
	void SetPosX(int x) { m_nPosX = x; }
	void SetPosY(int y) { m_nPosY = y; }
};

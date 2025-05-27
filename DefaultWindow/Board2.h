#pragma once
#include "CObj.h"
#include "CKeyMgr.h"
class Board2 : public CObj
{
public:
	Board2();
	virtual ~Board2();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Update_Matrix();

private:
    void    Key_Input();


private:

    float       m_fAngleX = 0.f;
    float       m_fAngleY = 0.f;
    float       m_fAngleZ = 0.f;
    float       m_fSpeed = 0.f;   // �̵� �ӵ�

    bool        m_bFlip = false;    // �ø�������
    bool        m_bShuvit = false;
    bool        m_bHardFlip = false;

    D3DXMATRIX  m_matWorld; // ���� ��ȯ ���
    struct tagPolygon m_tBoard;
};


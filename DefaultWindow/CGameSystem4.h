#pragma once
#include "CObj.h"
enum BTYPE {BU, BD, BEND};
enum WTYPE {WU, WD, WEND};

class CGameSystem4 : public CObj
{
public:
	CGameSystem4();
	virtual ~CGameSystem4();

public:
    void Get_PlayerType(BTYPE playerBType, WTYPE playerWType)
    {
        m_eCurPlayerBType = playerBType;
        m_eCurPlayerWType = playerWType;
    }
public:
    float   Get_ResultTime() { return m_fResultTime; }

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void Input_Type();
    void Validate_Result();

private:
    queue<std::pair<BTYPE, WTYPE>> q;

    BTYPE    m_eBType;
    WTYPE    m_eWType;

    BTYPE    m_eCurPlayerBType;
    WTYPE    m_eCurPlayerWType;

    float   m_fInputTime;
    float   m_fResultTime;

    bool    m_bResult;
};


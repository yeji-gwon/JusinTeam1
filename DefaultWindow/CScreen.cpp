#include "pch.h"
#include "CScreen.h"

CScreen::CScreen()
{
}

CScreen::~CScreen()
{
}

void CScreen::Initialize()
{
    m_vPos = {400,300,0.f};
    m_vScale = { 400,300,0.f };
}

int CScreen::Update()
{
    return 0;
}

void CScreen::Late_Update()
{
}

void CScreen::Render(HDC hDC)
{
}

void CScreen::Release()
{
}

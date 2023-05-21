#include "Fade.h"
#include "UI/UIImage.h"

CFade::CFade() :
    m_Opacity(1.f)
{
    m_WindowTypeName = "Fade";
}

CFade::CFade(const CFade& Window) :
    CUIWindow(Window)
{
}

CFade::~CFade()
{
}

void CFade::Start()
{  
    CUIWindow::Start();
}

bool CFade::Init()
{
    CUIWindow::Init();

    m_Fade = CreateWidget<CUIImage>("Fade");
    m_Fade->SetSize(1280.f, 720.f);
    m_Fade->SetPos(0.f, 0.f);

    m_Fade->SetTexture("Fade", TEXT("Fade.png"));

    return true;
}

void CFade::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    m_Opacity -= 0.001f;

    m_Fade->SetOpacity(m_Opacity);
}

void CFade::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CFade::Render()
{
    CUIWindow::Render();
}

CFade* CFade::Clone()
{
    return new CFade(*this);
}

void CFade::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CFade::Load(FILE* File)
{
    CUIWindow::Load(File);
}

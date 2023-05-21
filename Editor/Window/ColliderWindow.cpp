//
//#include "Component/ColliderBox2D.h"
//#include "ColliderWindow.h"
//#include "Component/CameraComponent.h"
//#include "Scene/SceneManager.h"
//#include "Scene/Scene.h"
//#include "Editor/EditorInput.h"
//#include "Input.h"
//
//CColliderWindow::CColliderWindow()
//{
//}
//
//CColliderWindow::~CColliderWindow()
//{
//}
//
//bool CColliderWindow::Init()
//{
//	return true;
//}
//
//void CColliderWindow::Update(float DeltaTime)
//{
//	if (GetAsyncKeyState('W') & 0x8000)
//	{
//		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
//
//		Camera->AddWorldPositionY(200.f * g_DeltaTime);
//	}
//
//	if (GetAsyncKeyState('S') & 0x8000)
//	{
//		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
//
//		Camera->AddWorldPositionY(-200.f * g_DeltaTime);
//	}
//
//	if (GetAsyncKeyState('D') & 0x8000)
//	{
//		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
//
//		Camera->AddWorldPositionX(200.f * g_DeltaTime);
//	}
//
//	if (GetAsyncKeyState('A') & 0x8000)
//	{
//		CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();
//
//		Camera->AddWorldPositionX(-200.f * g_DeltaTime);
//	}
//
//	// 마우스의 월드위치를 얻어온다.
//	Vector2 Pos[3];
//	Pos[0] = CInput::GetInst()->GetMouseWorldPos();
//	Pos[1] = CInput::GetInst()->GetMouseWorldPos();
//	Pos[2] = CInput::GetInst()->GetMouseWorldPos();
//	Pos[3] = CInput::GetInst()->GetMouseWorldPos();
//
//	 m_Info.Top = Pos[0];
//
//
//	/*int	Index = m_TileMap->GetTileIndex(Pos);
//
//	m_TileMap->SetEditorMouseOnTile(Index);
//
//	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
//	{
//		switch ((ETileEditMode)m_TileEditCombo->GetSelectIndex())
//		{
//		case ETileEditMode::Image:
//			m_TileMap->ChangeTileFrame(Pos, m_TileFrameList->GetSelectIndex());
//			break;
//		case ETileEditMode::Option:
//			m_TileMap->ChangeTileOption(Pos, (ETileOption)m_TileOptionCombo->GetSelectIndex());
//			break;
//		}
//	}*/
//}

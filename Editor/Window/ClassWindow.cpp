
#include "ClassWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "PathManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/WallObj.h"
#include "../GameObject/Effect.h"
#include "../GameObject/PortalObject.h"
#include "../GameObject/Grimm.h"
#include "../GameObject/SecondBackObj.h"
#include "../GameObject/GrimmTroupeBackObj.h"
#include "../GameObject/GrimmChild.h"
#include "../GameObject/GrimmLandPoint.h"
#include "../GameObject/BossMap.h"
#include "../GameObject/Vengefly.h"
#include "../GameObject/BrokenVessel.h"
#include "../GameObject/Vengefly2.h"
#include "../GameObject/PortalObject2.h"


#include "ObjectWindow.h"
#include "ComponentWindow.h"
#include "Editor/EditorGUIManager.h"

#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/TileMapComponent.h"

CClassWindow::CClassWindow()
{
}

CClassWindow::~CClassWindow()
{
}

bool CClassWindow::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("ObjectClass");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* Button = CreateWidget<CEditorButton>("오브젝트생성", 150.f, 30.f);

	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CClassWindow>(this, &CClassWindow::ObjectCreateCallback);

	m_ObjectList = CreateWidget<CEditorListBox>("ObjectListBox");

	m_ObjectList->SetHideName("ObjectListBox");

	m_ObjectList->SetSize(200.f, 300.f);
	m_ObjectList->SetPageItemCount(6);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_ObjectSelectName = CreateWidget<CEditorInput>("ObjectName");

	m_ObjectSelectName->SetHideName("ObjectName");
	m_ObjectSelectName->SetSize(150.f, 30.f);
	m_ObjectSelectName->AddFlag(ImGuiInputTextFlags_ReadOnly);

	Label = CreateWidget<CEditorLabel>("ComponentClass");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);
	Label->SetSizeX(150.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	Button = CreateWidget<CEditorButton>("컴포넌트생성", 150.f, 30.f);

	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CClassWindow>(this, &CClassWindow::ComponentCreateCallback);

	m_ObjectList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ObjectClickCallback);


	m_ComponentList = CreateWidget<CEditorListBox>("ComponentListBox");

	m_ComponentList->SetHideName("ComponentListBox");

	m_ComponentList->SetSize(200.f, 300.f);
	m_ComponentList->SetPageItemCount(6);


	m_ComponentList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ComponentClickCallback);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_ComponentSelectName = CreateWidget<CEditorInput>("ComponentName");

	m_ComponentSelectName->SetHideName("ComponentName");
	m_ComponentSelectName->SetSize(150.f, 30.f);
	m_ComponentSelectName->AddFlag(ImGuiInputTextFlags_ReadOnly);

	LoadGameObjectName();

	LoadComponentName();

	return true;
}

void CClassWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	/*if(m_SelectObjectItem != "Player2D")
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

			Camera->AddWorldPositionY(400.f * g_DeltaTime);
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

			Camera->AddWorldPositionY(-400.f * g_DeltaTime);
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

			Camera->AddWorldPositionX(400.f * g_DeltaTime);
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

			Camera->AddWorldPositionX(-400.f * g_DeltaTime);
		}
	}*/
}

void CClassWindow::ObjectClickCallback(int Index, const std::string& Item)
{
	m_SelectObjectItem = Item;

	m_ObjectSelectName->SetText(Item.c_str());
}

void CClassWindow::ComponentClickCallback(int Index, const std::string& Item)
{
	m_SelectComponentItem = Item;

	m_ComponentSelectName->SetText(Item.c_str());
}

void CClassWindow::ObjectCreateCallback()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CGameObject* Obj = nullptr;

	if (m_SelectObjectItem == "")
		return;

	CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

	if (m_SelectObjectItem == "GameObject")
		Obj = Scene->CreateObject<CGameObject>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Player2D")
		Obj = Scene->CreateObject<CPlayer2D>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Bullet")
		Obj = Scene->CreateObject<CBullet>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Monster")
		Obj = Scene->CreateObject<CMonster>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "BackObj")
		Obj = Scene->CreateObject<CBackObj>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "WallObj")
		Obj = Scene->CreateObject<CWallObj>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Effect")
		Obj = Scene->CreateObject<CEffect>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Portal")
		Obj = Scene->CreateObject<CPortalObject>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Grimm")
		Obj = Scene->CreateObject<CGrimm>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "SecondBackObj")
		Obj = Scene->CreateObject<CSecondBackObj>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "GrimmTroupeBackObj")
		Obj = Scene->CreateObject<CGrimmTroupeBackObj>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "GrimmChild")
		Obj = Scene->CreateObject<CGrimmChild>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "GrimmLandPoint")
		Obj = Scene->CreateObject<CGrimmLandPoint>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Vengefly")
		Obj = Scene->CreateObject<CVengefly>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "BrokenVessel")
		Obj = Scene->CreateObject<CBrokenVessel>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "BossMap")
		Obj = Scene->CreateObject<CBossMap>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "Vengefly2")
		Obj = Scene->CreateObject<CVengefly2>(m_SelectObjectItem);

	else if (m_SelectObjectItem == "PortalObject2")
		Obj = Scene->CreateObject<CPortalObject2>(m_SelectObjectItem);

	if (Window)
	{
		Window->AddItem(Obj, m_SelectObjectItem);
	}
}

void CClassWindow::ComponentCreateCallback()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");
	CComponentWindow* ComponentWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");

	CGameObject* SelectObject = ObjectWindow->GetSelectObject();

	if (!SelectObject)
		return;

	CSceneComponent* SelectComponent = (CSceneComponent*)ComponentWindow->GetSelectComponent();

	if (!SelectComponent)
	{
		SelectComponent = SelectObject->GetRootComponent();
	}

	std::string	Name;

	CSceneComponent* NewComponent = nullptr;

	if (m_SelectComponentItem == "SpriteComponent")
	{
		Name = "SpriteComponent(SpriteComponent)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CSpriteComponent>("SpriteComponent");
	}

	else if (m_SelectComponentItem == "SceneComponent")
	{
		Name = "SceneComponent(SceneComponent)";
		NewComponent = SelectObject->CreateComponent<CSceneComponent>("SceneComponent");
	}

	else if (m_SelectComponentItem == "TargetArm")
	{
		Name = "TargetArm(TargetArm)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CTargetArm>("TargetArm");
	}

	else if (m_SelectComponentItem == "CameraComponent")
	{
		Name = "CameraComponent(CameraComponent)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CCameraComponent>("CameraComponent");
	}

	else if (m_SelectComponentItem == "TileMapComponent")
	{
		Name = "TileMapComponent(TileMapComponent)";
		NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CTileMapComponent>("TileMapComponent");
	}

	if (SelectComponent)
	{
		std::string	ParentName = SelectComponent->GetName() + "(" + SelectComponent->GetComponentTypeName() + ")";
		
		SelectComponent->AddChild(NewComponent);

		ComponentWindow->AddItem((CComponent*)NewComponent, Name, ParentName);
	}

	else
	{
		std::string	ObjName = SelectObject->GetName() + "(" + SelectObject->GetObjectTypeName() + ")";

		ComponentWindow->AddItem((CComponent*)NewComponent, Name, ObjName);
	}
}

void CClassWindow::LoadGameObjectName()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	int	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/GameObject/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_ObjectList->AddItem(Name);
	}

	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	memset(Directory, 0, MAX_PATH);
	strcpy_s(Directory, Path);

	// Engine의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Engine/Include/GameObject/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_ObjectList->AddItem(Name);
	}
}

void CClassWindow::LoadComponentName()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	int	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 Component폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/Component/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_ComponentList->AddItem(Name);
	}

	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	memset(Directory, 0, MAX_PATH);
	strcpy_s(Directory, Path);

	// Engine의 GameObject폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Engine/Include/Component/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		else if (strcmp(Name, "Transform") == 0 || 
			strcmp(Name, "Transform2D") == 0 ||
			strcmp(Name, "Component") == 0 || 
			strcmp(Name, "PrimitiveComponent") == 0 || 
			strcmp(Name, "ObjectComponent") == 0 ||
			strcmp(Name, "Tile") == 0)
			continue;

		m_ComponentList->AddItem(Name);
	}
}

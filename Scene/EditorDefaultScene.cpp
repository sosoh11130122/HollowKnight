
#include "EditorDefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/StartSceneUI.h"
#include "../UI/FirstSceneUI.h"

CEditorDefaultScene::CEditorDefaultScene()
{
	m_ClassTypeName = "EditorDefaultScene";
}

CEditorDefaultScene::~CEditorDefaultScene()
{
}

bool CEditorDefaultScene::Init()
{
	m_Owner->GetViewport()->CreateUIWindow<CStartSceneUI>("StartUI");
	//m_Owner->GetViewport()->CreateUIWindow<CFirstSceneUI>("FirstSceneUI");


	return true;
}

///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	tutorial.cpp
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTutorial(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TUTO tuto[TUTORIAL_GOUKEI];
static int tutoPadpos;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorial(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,	
			TEXTURE_TUTORIALF1,				
			&tuto[0].pD3DTexture);		
		D3DXCreateTextureFromFile(pDevice,	
			TEXTURE_TUTORIALF2,				
			&tuto[1].pD3DTexture);	
		D3DXCreateTextureFromFile(pDevice,	
			TEXTURE_TUTORIALF3,				
			&tuto[2].pD3DTexture);		
	}
	tuto[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	tuto[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	tuto[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	tutoPadpos = 0;
	// 頂点情報の作成
	MakeVertexTutorial();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	if (tuto[0].pD3DTexture != NULL)
	{// テクスチャの開放
		tuto[0].pD3DTexture->Release();
		tuto[0].pD3DTexture = NULL;
	}
	if (tuto[1].pD3DTexture != NULL)
	{// テクスチャの開放
		tuto[1].pD3DTexture->Release();
		tuto[1].pD3DTexture = NULL;
	}
	if (tuto[2].pD3DTexture != NULL)
	{// テクスチャの開放
		tuto[2].pD3DTexture->Release();
		tuto[2].pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_B))
	{// Enter押したら、ステージを切り替える
		PlaySound(SOUND_LABEL_SE_enter02);
		SetFade(FADE_OUT, SCENE_SELECT, SOUND_LABEL_BGM_select01);
	}
	else if(IsButtonTriggered(0, BUTTON_R1)) 	tutoPadpos++;
	else if (IsButtonTriggered(0, BUTTON_L1)) 	tutoPadpos--;
	if (tutoPadpos > 3) tutoPadpos = 0;
	else if (tutoPadpos < 0) tutoPadpos = 3;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);
	if (GetKeyboardPress(DIK_1) || tutoPadpos == 1)
	{
		pDevice->SetTexture(0, tuto[0].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, tuto[0].vertexWk, sizeof(VERTEX_2D));
		if (GetKeyboardPress(DIK_2)) tutoPadpos = 2;
		else if (GetKeyboardPress(DIK_3))tutoPadpos = 3;
		else if (GetKeyboardPress(DIK_1)) tutoPadpos = 0;
	}
	else if (GetKeyboardPress(DIK_2) || tutoPadpos == 2)
	{
		pDevice->SetTexture(0, tuto[1].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, tuto[1].vertexWk, sizeof(VERTEX_2D));
		if (GetKeyboardPress(DIK_1)) tutoPadpos = 1;
		else if (GetKeyboardPress(DIK_3))tutoPadpos = 3;
		else if (GetKeyboardPress(DIK_2)) tutoPadpos = 0;
	}
	else if (GetKeyboardPress(DIK_3) || tutoPadpos == 3)
	{
		pDevice->SetTexture(0, tuto[2].pD3DTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, tuto[2].vertexWk, sizeof(VERTEX_2D));
		if (GetKeyboardPress(DIK_1)) tutoPadpos = 1;
		else if (GetKeyboardPress(DIK_2))tutoPadpos = 2;
		else if (GetKeyboardPress(DIK_3)) tutoPadpos = 0;
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTutorial(void)
{

	// 頂点座標の設定
	tuto[0].vertexWk[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	tuto[0].vertexWk[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	tuto[0].vertexWk[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	tuto[0].vertexWk[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	tuto[0].vertexWk[0].rhw =
	tuto[0].vertexWk[1].rhw =
	tuto[0].vertexWk[2].rhw =
	tuto[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	tuto[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	tuto[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	tuto[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	tuto[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	tuto[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	tuto[1].vertexWk[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	tuto[1].vertexWk[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	tuto[1].vertexWk[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	tuto[1].vertexWk[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	tuto[1].vertexWk[0].rhw =
	tuto[1].vertexWk[1].rhw =
	tuto[1].vertexWk[2].rhw =
	tuto[1].vertexWk[3].rhw = 1.0f;
	tuto[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	tuto[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	tuto[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	tuto[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	tuto[2].vertexWk[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	tuto[2].vertexWk[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	tuto[2].vertexWk[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	tuto[2].vertexWk[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	tuto[2].vertexWk[0].rhw =
	tuto[2].vertexWk[1].rhw =
	tuto[2].vertexWk[2].rhw =
	tuto[2].vertexWk[3].rhw = 1.0f;
	tuto[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	tuto[2].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	tuto[2].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	tuto[2].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	tuto[2].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}


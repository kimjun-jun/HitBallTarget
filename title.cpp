/**
* @file title.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "title.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief 頂点生成関数 MakeVertexTitle
* @return HRESULT
*/
HRESULT MakeVertexTitle(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TITLE g_title;				//!< タイトル構造体変数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TITLE_LOGO,									// ファイルの名前
			&g_title.pD3DTexture);							// 読み込むメモリー
	}

	// 頂点情報の作成
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	for (int i = 0; i < TITLE_GOUKEI; i++)
	{
		if (g_title.pD3DTexture != NULL)
		{// テクスチャの開放
			g_title.pD3DTexture->Release();
			g_title.pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	MasterVolumeChange(1);
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_B))
	{// Enter押したら、ステージを切り替える
		PlaySound(SOUND_LABEL_SE_enter01);
		SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial01);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < TITLE_GOUKEI; i++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_title.pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_title.vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	g_title.vertexWk[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X - TITLELOGO_SIZE_X, TITLELOGO_POS_Y - TITLELOGO_SIZE_Y, 0.0f);
	g_title.vertexWk[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y - TITLELOGO_SIZE_Y, 0.0f);
	g_title.vertexWk[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X - TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	g_title.vertexWk[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);

	g_title.vertexWk[0].rhw =
	g_title.vertexWk[1].rhw =
	g_title.vertexWk[2].rhw =
	g_title.vertexWk[3].rhw = 1.0f;

	g_title.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_title.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_title.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_title.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_title.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_title.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_title.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_title.vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


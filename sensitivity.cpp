/**
* @file sensitivity.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "ball.h"
#include "sensitivity.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief ポリゴン頂点生成関数 MakeVertexSensitivity
* @return HRESULT
*/
HRESULT MakeVertexSensitivity(void);

/**
* @brief テクスチャ設定関数 SetTextureSensitivity
*/
void SetTextureSensitivity(void);

/**
* @brief 頂点設定関数 SetVertexSensitivity
*/
void SetVertexSensitivity(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
SENSITIVITY g_sensitivity[SENSITIVITYMAX];			//!< 0はじめから、1あきらめる、2オプション	構造体変数
static int SSENSIkey;								//!< これが感度の値

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSensitivity(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_L1R1,
			&g_sensitivity[0].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_SENSITIVITYNUM,
			&g_sensitivity[1].pD3DTexture);
	}

	g_sensitivity[0].pos = D3DXVECTOR3(PX1_POS_X, PY1_POS_Y, 0.0f);
	g_sensitivity[1].pos = D3DXVECTOR3(PX1_POS_X, PY2_POS_Y, 0.0f);
	SSENSIkey = 5;
	// 頂点情報の作成
	MakeVertexSensitivity();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitSensitivity(void)
{
	SSENSIkey = 5;
	SetVertexSensitivity();
	SetTextureSensitivity();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSensitivity(void)
{
	for (int i = 0; i < SENSITIVITYMAX; i++)
	{
		if (g_sensitivity[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_sensitivity[i].pD3DTexture->Release();
			g_sensitivity[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理　シーンSENSITIVITYのアップデート
//=============================================================================
void UpdateSensitivity(void)
{
	if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonTriggered(0, BUTTON_DIGITAL_RIGHT) || IsButtonTriggered(0, BUTTON_ANALOG_L_RIGHT))
	{
		if (SSENSIkey < 9)
		{
			SSENSIkey++;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) || IsButtonTriggered(0, BUTTON_DIGITAL_LEFT) || IsButtonTriggered(0, BUTTON_ANALOG_L_LEFT))
	{
		if (SSENSIkey > 1)
		{
			SSENSIkey--;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
	}
	//上限
	if (SSENSIkey > 9) SSENSIkey = 9;
	else if (SSENSIkey < 1) SSENSIkey = 1;
	if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
	{
		PlaySound(SOUND_LABEL_SE_enter02);
		SetScene(SCENE_OPTION);
	}
	SetVertexSensitivity();
	SetTextureSensitivity();
}

//=============================================================================
// 更新処理　シーンTUTOSENSITIVITYのアップデート
//=============================================================================
void UpdateTUTOSensitivity(void)
{
	if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonTriggered(0, BUTTON_DIGITAL_RIGHT) || IsButtonTriggered(0, BUTTON_ANALOG_L_RIGHT))
	{
		if (SSENSIkey < 9)
		{
			SSENSIkey++;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
	}
	else if (GetKeyboardTrigger(DIK_LEFT) || IsButtonTriggered(0, BUTTON_DIGITAL_LEFT) || IsButtonTriggered(0, BUTTON_ANALOG_L_LEFT))
	{
		if (SSENSIkey > 1)
		{
			SSENSIkey--;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
	}
	//上限
	if (SSENSIkey > 9) SSENSIkey = 9;
	else if (SSENSIkey < 1) SSENSIkey = 1;
	if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
	{
		PlaySound(SOUND_LABEL_SE_enter02);
		SetScene(SCENE_TUTORIALMENU);
	}
	SetVertexSensitivity();
	SetTextureSensitivity();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSensitivity(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < SENSITIVITYMAX; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_sensitivity[i].pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_sensitivity[i].vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexSensitivity(void)
{
	// テクスチャのパースペクティブコレクト用
	g_sensitivity[0].vertexWk[0].rhw =
		g_sensitivity[0].vertexWk[1].rhw =
		g_sensitivity[0].vertexWk[2].rhw =
		g_sensitivity[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_sensitivity[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_sensitivity[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_sensitivity[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_sensitivity[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_sensitivity[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_sensitivity[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_sensitivity[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_sensitivity[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//number
	g_sensitivity[1].vertexWk[0].rhw =
		g_sensitivity[1].vertexWk[1].rhw =
		g_sensitivity[1].vertexWk[2].rhw =
		g_sensitivity[1].vertexWk[3].rhw = 1.0f;
	g_sensitivity[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_sensitivity[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_sensitivity[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_sensitivity[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_sensitivity[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_sensitivity[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_sensitivity[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_sensitivity[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureSensitivity(void)
{
	g_sensitivity[1].vertexWk[0].tex = D3DXVECTOR2(SSENSIkey*0.1f, 0.0f);
	g_sensitivity[1].vertexWk[1].tex = D3DXVECTOR2((SSENSIkey + 1)*0.1f, 0.0f);
	g_sensitivity[1].vertexWk[2].tex = D3DXVECTOR2(SSENSIkey*0.1f, 1.0f);
	g_sensitivity[1].vertexWk[3].tex = D3DXVECTOR2((SSENSIkey + 1)*0.1f, 1.0f);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexSensitivity(void)
{
	// 頂点座標の設定 
	for (int i = 0; i < SENSITIVITYMAX; i++)
	{
		g_sensitivity[i].vertexWk[0].vtx.x = g_sensitivity[i].pos.x - TEXTURE_SENSITIVITYBROAD_SIZE_X;
		g_sensitivity[i].vertexWk[0].vtx.y = g_sensitivity[i].pos.y - TEXTURE_SENSITIVITYBROAD_SIZE_Y;
		g_sensitivity[i].vertexWk[0].vtx.z = 0.0f;
		g_sensitivity[i].vertexWk[1].vtx.x = g_sensitivity[i].pos.x + TEXTURE_SENSITIVITYBROAD_SIZE_X;
		g_sensitivity[i].vertexWk[1].vtx.y = g_sensitivity[i].pos.y - TEXTURE_SENSITIVITYBROAD_SIZE_Y;
		g_sensitivity[i].vertexWk[1].vtx.z = 0.0f;
		g_sensitivity[i].vertexWk[2].vtx.x = g_sensitivity[i].pos.x - TEXTURE_SENSITIVITYBROAD_SIZE_X;
		g_sensitivity[i].vertexWk[2].vtx.y = g_sensitivity[i].pos.y + TEXTURE_SENSITIVITYBROAD_SIZE_Y;
		g_sensitivity[i].vertexWk[2].vtx.z = 0.0f;
		g_sensitivity[i].vertexWk[3].vtx.x = g_sensitivity[i].pos.x + TEXTURE_SENSITIVITYBROAD_SIZE_X;
		g_sensitivity[i].vertexWk[3].vtx.y = g_sensitivity[i].pos.y + TEXTURE_SENSITIVITYBROAD_SIZE_Y;
		g_sensitivity[i].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// 現在の感度取得
//=============================================================================
int GetSSENSIkey(void)
{
	return SSENSIkey;
}


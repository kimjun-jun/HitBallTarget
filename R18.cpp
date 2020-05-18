/**
* @file R18.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "option.h"
#include "bg.h"
#include "R18.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexR18select(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
R18SELECT g_r18select[R18SELECTMAX];//0感度、1キャンセル、2コントローラー、3R18、
static int R18posx;			//R18カーソルのposx
static int R18posy;			//R18カーソルのposy

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitR18select(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_R18SELECT01,
			&g_r18select[0].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_R18SELECT03,
			&g_r18select[1].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_R18SELECT02,
			&g_r18select[2].pD3DTexture);
	}

	g_r18select[0].pos = D3DXVECTOR3(R18SELECT_PX1_POS_X, R18SELECT_PY1_POS_Y, 0.0f);
	g_r18select[1].pos = D3DXVECTOR3(R18SELECT_PX1_POS_X, R18SELECT_PY2_POS_Y, 0.0f);
	g_r18select[2].pos = D3DXVECTOR3(R18SELECT_PX2_POS_X, R18SELECT_PY1_POS_Y, 0.0f);
	R18posx = 0;
	R18posy = 0;
	// 頂点情報の作成
	MakeVertexR18select();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitR18select(void)
{
	R18posx = 0;
	R18posy = 0;
	SetVertexR18select();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitR18select(void)
{
	for (int i = 0; i < R18SELECTMAX; i++)
	{
		if (g_r18select[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_r18select[i].pD3DTexture->Release();
			g_r18select[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理　シーンオプションでアップデート
//=============================================================================
void UpdateR18select(void)
{
	if (R18posx == 0)
	{
		if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_DIGITAL_UP) || IsButtonTriggered(0, BUTTON_ANALOG_L_UP))
		{
			R18posy--;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DIGITAL_DOWN) || IsButtonTriggered(0, BUTTON_ANALOG_L_DOWN))
		{
			R18posy++;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
	}
	if (R18posy == 0)
	{
		if (GetKeyboardTrigger(DIK_LEFT) || IsButtonTriggered(0, BUTTON_DIGITAL_LEFT) || IsButtonTriggered(0, BUTTON_ANALOG_L_LEFT))
		{
			R18posx--;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
		else if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonTriggered(0, BUTTON_DIGITAL_RIGHT) || IsButtonTriggered(0, BUTTON_ANALOG_L_RIGHT))
		{
			R18posx++;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
	}
	//上限
	if (R18posx > 1) R18posx = 0;
	else if (R18posx < 0) R18posx = 1;
	if (R18posy > 1) R18posy = 0;
	else if (R18posy < 0) R18posy = 1;


	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_A))
	{
		//魔女っ子
		if (R18posx == 0&&R18posy == 0)
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SetGameBGtype(0);
		}
		//標準
		else if (R18posx == 0 && R18posy == 1)
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SetGameBGtype(-1);
		}
		//スイーツ
		else if (R18posx == 1 && R18posy == 0)
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SetGameBGtype(1);
		}
		SetScene(SCENE_OPTION);
	}
	if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
	{
		PlaySound(SOUND_LABEL_SE_enter02);
		SetScene(SCENE_OPTION);
	}
	SetVertexR18select();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawR18select(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < R18SELECTMAX; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_r18select[i].pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_r18select[i].vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexR18select(void)
{
	// テクスチャのパースペクティブコレクト用
	g_r18select[0].vertexWk[0].rhw =
		g_r18select[0].vertexWk[1].rhw =
		g_r18select[0].vertexWk[2].rhw =
		g_r18select[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_r18select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_r18select[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_r18select[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_r18select[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_r18select[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_r18select[1].vertexWk[0].rhw =
		g_r18select[1].vertexWk[1].rhw =
		g_r18select[1].vertexWk[2].rhw =
		g_r18select[1].vertexWk[3].rhw = 1.0f;
	g_r18select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_r18select[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_r18select[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_r18select[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_r18select[2].vertexWk[0].rhw =
	g_r18select[2].vertexWk[1].rhw =
	g_r18select[2].vertexWk[2].rhw =
	g_r18select[2].vertexWk[3].rhw = 1.0f;
	g_r18select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_r18select[2].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_r18select[2].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_r18select[2].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_r18select[2].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexR18select(void)
{
	// 頂点座標の設定 
	for (int i = 0; i < R18SELECTMAX; i++)
	{
		g_r18select[i].vertexWk[0].vtx.x = g_r18select[i].pos.x - TEXTURE_R18SELECT_SIZE_X;
		g_r18select[i].vertexWk[0].vtx.y = g_r18select[i].pos.y - TEXTURE_R18SELECT_SIZE_Y;
		g_r18select[i].vertexWk[0].vtx.z = 0.0f;
		g_r18select[i].vertexWk[1].vtx.x = g_r18select[i].pos.x + TEXTURE_R18SELECT_SIZE_X;
		g_r18select[i].vertexWk[1].vtx.y = g_r18select[i].pos.y - TEXTURE_R18SELECT_SIZE_Y;
		g_r18select[i].vertexWk[1].vtx.z = 0.0f;
		g_r18select[i].vertexWk[2].vtx.x = g_r18select[i].pos.x - TEXTURE_R18SELECT_SIZE_X;
		g_r18select[i].vertexWk[2].vtx.y = g_r18select[i].pos.y + TEXTURE_R18SELECT_SIZE_Y;
		g_r18select[i].vertexWk[2].vtx.z = 0.0f;
		g_r18select[i].vertexWk[3].vtx.x = g_r18select[i].pos.x + TEXTURE_R18SELECT_SIZE_X;
		g_r18select[i].vertexWk[3].vtx.y = g_r18select[i].pos.y + TEXTURE_R18SELECT_SIZE_Y;
		g_r18select[i].vertexWk[3].vtx.z = 0.0f;
	}
	if (R18posx == 0 && R18posy == 0)
	{
		g_r18select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (R18posx == 0 && R18posy == 1)
	{
		g_r18select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (R18posx == 1 && R18posy == 0)
	{
		g_r18select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_r18select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_r18select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}


R18SELECT *GetR18select(void)
{
	return &g_r18select[0];
}


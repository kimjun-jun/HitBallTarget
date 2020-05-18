/**
* @file controltype.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "ball.h"
#include "controltype.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexContype(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CONTYPE g_contype[CONTYPEMAX];//0はじめから、1あきらめる、2オプション
static int SCONposy;			//ポーズカーソルのposy
static int SCONkeypos;			//これがA/Dキー
static int diffsec;			//点滅タイム
static int diffnum;				//diffuse倍率

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitContype(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_DIGITAL,
			&g_contype[0].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_ANALOG,
			&g_contype[1].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_CONTYPECURSOR,
			&g_contype[2].pD3DTexture);
	}

	g_contype[0].pos = D3DXVECTOR3(PX1_POS_X, PY1_POS_Y, 0.0f);
	g_contype[1].pos = D3DXVECTOR3(PX1_POS_X, PY2_POS_Y, 0.0f);
	g_contype[2].pos = D3DXVECTOR3(PX2_POS_X, PY1_POS_Y, 0.0f);
	SCONkeypos = 0;
	SCONposy = 0;
	diffsec = 0;
	diffnum = 0;
	// 頂点情報の作成
	MakeVertexContype();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitContype(void)
{
	SCONposy = 0;
	diffsec = 0;
	diffnum = 0;
	SetVertexContype();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitContype(void)
{
	for (int i = 0; i < CONTYPEMAX; i++)
	{
		if (g_contype[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_contype[i].pD3DTexture->Release();
			g_contype[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理　シーンCONTYPEのアップデート
//=============================================================================
void UpdateContype(void)
{
	if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_DIGITAL_UP) || IsButtonTriggered(0, BUTTON_ANALOG_L_UP))
	{
		SCONposy--;
		PlaySound(SOUND_LABEL_SE_enter03);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DIGITAL_DOWN) || IsButtonTriggered(0, BUTTON_ANALOG_L_DOWN))
	{
		SCONposy++;
		PlaySound(SOUND_LABEL_SE_enter03);
	}
	//上限
	if (SCONposy > 1) SCONposy = 0;
	else if (SCONposy < 0) SCONposy = 1;
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_A))
	{
		//デジタル
		if (SCONposy == 0)
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SCONkeypos = 0;
		}
		//アナログ
		else if (SCONposy == 1)
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SCONkeypos = 1;
		}
	}
	if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
	{
		PlaySound(SOUND_LABEL_SE_enter02);
		SetScene(SCENE_OPTION);
	}
	diffsec++;
	if (diffsec == 15) diffnum = 1;
	else if (diffsec == 30)
	{
		diffnum = 0;
		diffsec = 0;
	}
	SetVertexContype();
}


//=============================================================================
// 更新処理　シーンTUTOCONTYPEのアップデート
//=============================================================================
void UpdateTUTOContype(void)
{
	if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_DIGITAL_UP) || IsButtonTriggered(0, BUTTON_ANALOG_L_UP))
	{
		SCONposy--;
		PlaySound(SOUND_LABEL_SE_enter03);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DIGITAL_DOWN) || IsButtonTriggered(0, BUTTON_ANALOG_L_DOWN))
	{
		SCONposy++;
		PlaySound(SOUND_LABEL_SE_enter03);
	}
	//上限
	if (SCONposy > 1) SCONposy = 0;
	else if (SCONposy < 0) SCONposy = 1;
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_A))
	{
		//デジタル
		if (SCONposy == 0)
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SCONkeypos = 0;
		}
		//アナログ
		else if (SCONposy == 1)
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SCONkeypos = 1;
		}
	}
	if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
	{
		PlaySound(SOUND_LABEL_SE_enter02);
		SetScene(SCENE_TUTORIALMENU);
	}
	diffsec++;
	if (diffsec == 15) diffnum = 1;
	else if (diffsec == 30)
	{
		diffnum = 0;
		diffsec = 0;
	}
	SetVertexContype();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawContype(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < CONTYPEMAX; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_contype[i].pD3DTexture);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_contype[i].vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexContype(void)
{
	// テクスチャのパースペクティブコレクト用
	g_contype[0].vertexWk[0].rhw =
		g_contype[0].vertexWk[1].rhw =
		g_contype[0].vertexWk[2].rhw =
		g_contype[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_contype[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_contype[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_contype[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_contype[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_contype[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_contype[1].vertexWk[0].rhw =
		g_contype[1].vertexWk[1].rhw =
		g_contype[1].vertexWk[2].rhw =
		g_contype[1].vertexWk[3].rhw = 1.0f;
	g_contype[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_contype[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_contype[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_contype[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_contype[2].vertexWk[0].rhw =
		g_contype[2].vertexWk[1].rhw =
		g_contype[2].vertexWk[2].rhw =
		g_contype[2].vertexWk[3].rhw = 1.0f;
	g_contype[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_contype[2].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_contype[2].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_contype[2].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_contype[2].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexContype(void)
{

	if (SCONposy == 0) g_contype[2].pos = D3DXVECTOR3(PX2_POS_X, PY1_POS_Y, 0.0f);
	else if (SCONposy == 1) g_contype[2].pos = D3DXVECTOR3(PX2_POS_X, PY2_POS_Y, 0.0f);
	// 頂点座標の設定 
	for (int i = 0; i < CONTYPEMAX; i++)
	{
		g_contype[i].vertexWk[0].vtx.x = g_contype[i].pos.x - TEXTURE_CONTYPEBROAD_SIZE_X;
		g_contype[i].vertexWk[0].vtx.y = g_contype[i].pos.y - TEXTURE_CONTYPEBROAD_SIZE_Y;
		g_contype[i].vertexWk[0].vtx.z = 0.0f;
		g_contype[i].vertexWk[1].vtx.x = g_contype[i].pos.x + TEXTURE_CONTYPEBROAD_SIZE_X;
		g_contype[i].vertexWk[1].vtx.y = g_contype[i].pos.y - TEXTURE_CONTYPEBROAD_SIZE_Y;
		g_contype[i].vertexWk[1].vtx.z = 0.0f;
		g_contype[i].vertexWk[2].vtx.x = g_contype[i].pos.x - TEXTURE_CONTYPEBROAD_SIZE_X;
		g_contype[i].vertexWk[2].vtx.y = g_contype[i].pos.y + TEXTURE_CONTYPEBROAD_SIZE_Y;
		g_contype[i].vertexWk[2].vtx.z = 0.0f;
		g_contype[i].vertexWk[3].vtx.x = g_contype[i].pos.x + TEXTURE_CONTYPEBROAD_SIZE_X;
		g_contype[i].vertexWk[3].vtx.y = g_contype[i].pos.y + TEXTURE_CONTYPEBROAD_SIZE_Y;
		g_contype[i].vertexWk[3].vtx.z = 0.0f;
	}
	if (SCONkeypos == 0)
	{
		g_contype[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_contype[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_contype[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_contype[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_contype[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_contype[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_contype[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_contype[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (SCONkeypos == 1)
	{
		g_contype[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_contype[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_contype[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_contype[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_contype[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_contype[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_contype[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_contype[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	g_contype[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255*diffnum);
	g_contype[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255*diffnum);
	g_contype[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255*diffnum);
	g_contype[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255*diffnum);
}

int GetSCONkeypos(void)
{
	return SCONkeypos;
}


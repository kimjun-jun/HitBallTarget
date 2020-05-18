/**
* @file tutomenu.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "ball.h"
#include "tutomenu.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTutomenu(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TUTOMENU g_tutomenu[TUTOMENUMAX];//0感度、1A/D
static int STUTOMENUposy;			//チュートリアルのメニュカーソルのposy

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutomenu(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_SENSITIV,
			&g_tutomenu[0].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_CONTROLTYPE,
			&g_tutomenu[1].pD3DTexture);
	}

	g_tutomenu[0].pos = D3DXVECTOR3(PX1_POS_X, PY1_POS_Y, 0.0f);
	g_tutomenu[1].pos = D3DXVECTOR3(PX1_POS_X, PY2_POS_Y, 0.0f);

	g_tutomenu[0].use = false;
	STUTOMENUposy = 0;
	// 頂点情報の作成
	MakeVertexTutomenu();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitTutomenu(void)
{
	STUTOMENUposy = 0;
	g_tutomenu[0].use = false;
	SetVertexTutomenu();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutomenu(void)
{
	for (int i = 0; i < TUTOMENUMAX; i++)
	{
		if (g_tutomenu[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_tutomenu[i].pD3DTexture->Release();
			g_tutomenu[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理　シーンポーズのアップデート
//=============================================================================
void UpdateTutomenu(void)
{
	if (g_tutomenu[0].use == true)
	{
		MasterVolumeChange(0.5f);
			if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_DIGITAL_UP) || IsButtonTriggered(0, BUTTON_ANALOG_L_UP))
			{
				STUTOMENUposy--;
				PlaySound(SOUND_LABEL_SE_enter03);
			}
			else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DIGITAL_DOWN) || IsButtonTriggered(0, BUTTON_ANALOG_L_DOWN))
			{
				STUTOMENUposy++;
				PlaySound(SOUND_LABEL_SE_enter03);
			}
		}
		//上限
		if (STUTOMENUposy > 1) STUTOMENUposy = 0;
		else if (STUTOMENUposy < 0) STUTOMENUposy = 1;

		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_A))
		{
			//感度
			if (STUTOMENUposy == 0)
			{
				PlaySound(SOUND_LABEL_SE_enter02);
				SetScene(SCENE_TUTOSENSITIVITY);
			}
			//A/D変更
			else if (STUTOMENUposy == 1)
			{
				PlaySound(SOUND_LABEL_SE_enter02);
				SetScene(SCENE_TUTOCONTYPE);
			}
		}
		if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			MasterVolumeChange(1);
			SetScene(SCENE_TUTORIAL);
			g_tutomenu[0].use = false;
		}
		SetVertexTutomenu();
}


//=============================================================================
// 更新処理　シーンゲームのアップデート
//=============================================================================
void UpdateInTutomenu(void)
{
	if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_START) && g_tutomenu[0].use == false)
	{
		SetScene(SCENE_TUTORIALMENU);
		g_tutomenu[0].use = true;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTutomenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_tutomenu[0].use == true)
	{
		for (int i = 0; i < TUTOMENUMAX; i++)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_tutomenu[i].pD3DTexture);
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_tutomenu[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTutomenu(void)
{
	// テクスチャのパースペクティブコレクト用
	g_tutomenu[0].vertexWk[0].rhw =
		g_tutomenu[0].vertexWk[1].rhw =
		g_tutomenu[0].vertexWk[2].rhw =
		g_tutomenu[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_tutomenu[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tutomenu[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tutomenu[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tutomenu[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_tutomenu[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_tutomenu[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_tutomenu[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_tutomenu[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_tutomenu[1].vertexWk[0].rhw =
		g_tutomenu[1].vertexWk[1].rhw =
		g_tutomenu[1].vertexWk[2].rhw =
		g_tutomenu[1].vertexWk[3].rhw = 1.0f;
	g_tutomenu[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tutomenu[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tutomenu[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tutomenu[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_tutomenu[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_tutomenu[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_tutomenu[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_tutomenu[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexTutomenu(void)
{
	// 頂点座標の設定 
	for (int i = 0; i < TUTOMENUMAX; i++)
	{
		g_tutomenu[i].vertexWk[0].vtx.x = g_tutomenu[i].pos.x - TEXTURE_TUTOMENU_SIZE_X;
		g_tutomenu[i].vertexWk[0].vtx.y = g_tutomenu[i].pos.y - TEXTURE_TUTOMENU_SIZE_Y;
		g_tutomenu[i].vertexWk[0].vtx.z = 0.0f;
		g_tutomenu[i].vertexWk[1].vtx.x = g_tutomenu[i].pos.x + TEXTURE_TUTOMENU_SIZE_X;
		g_tutomenu[i].vertexWk[1].vtx.y = g_tutomenu[i].pos.y - TEXTURE_TUTOMENU_SIZE_Y;
		g_tutomenu[i].vertexWk[1].vtx.z = 0.0f;
		g_tutomenu[i].vertexWk[2].vtx.x = g_tutomenu[i].pos.x - TEXTURE_TUTOMENU_SIZE_X;
		g_tutomenu[i].vertexWk[2].vtx.y = g_tutomenu[i].pos.y + TEXTURE_TUTOMENU_SIZE_Y;
		g_tutomenu[i].vertexWk[2].vtx.z = 0.0f;
		g_tutomenu[i].vertexWk[3].vtx.x = g_tutomenu[i].pos.x + TEXTURE_TUTOMENU_SIZE_X;
		g_tutomenu[i].vertexWk[3].vtx.y = g_tutomenu[i].pos.y + TEXTURE_TUTOMENU_SIZE_Y;
		g_tutomenu[i].vertexWk[3].vtx.z = 0.0f;
	}
	if (STUTOMENUposy == 0)
	{
		g_tutomenu[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (STUTOMENUposy == 1)
	{
		g_tutomenu[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_tutomenu[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_tutomenu[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
}


TUTOMENU *GetTutomenu(void)
{
	return &g_tutomenu[0];
}


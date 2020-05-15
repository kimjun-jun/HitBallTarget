///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	pause.cpp
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "ball.h"
#include "pause.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPause(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PAUSE g_pause[PAUSEMAX];//0はじめから、1あきらめる、2オプション
static int SOposx;			//ポーズカーソルのposx
static int SOposy;			//ポーズカーソルのposy

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPause(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,	
			TEXTURE_HAJIMEKARA,
			&g_pause[0].pD3DTexture);		
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_END,
			&g_pause[1].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_OPTIONMARK,
			&g_pause[2].pD3DTexture);
	}

	g_pause[0].pos = D3DXVECTOR3(PX1_POS_X, PY1_POS_Y, 0.0f);
	g_pause[1].pos = D3DXVECTOR3(PX1_POS_X, PY2_POS_Y, 0.0f);
	g_pause[2].pos = D3DXVECTOR3(PX2_POS_X, PY1_POS_Y, 0.0f);

	g_pause[0].use = false;
	SOposx = 0;
	SOposy = 0;
	// 頂点情報の作成
	MakeVertexPause();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitPause(void)
{
	SOposx = 0;
	SOposy = 0;
	g_pause[0].use = false;
	SetVertexPause();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPause(void)
{
	for (int i = 0; i < PAUSEMAX; i++)
	{
		if (g_pause[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_pause[i].pD3DTexture->Release();
			g_pause[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理　シーンポーズのアップデート
//=============================================================================
void UpdatePause(void)
{
	if (g_pause[0].use == true)
	{
		MasterVolumeChange(0.5f);
		if (SOposx == 0)
		{

			if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_DIGITAL_UP) || IsButtonTriggered(0, BUTTON_ANALOG_L_UP))
			{
				SOposy--;
				PlaySound(SOUND_LABEL_SE_enter03);
			}
			else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DIGITAL_DOWN) || IsButtonTriggered(0, BUTTON_ANALOG_L_DOWN))
			{
				SOposy++;
				PlaySound(SOUND_LABEL_SE_enter03);
			}
		}
		if (SOposy == 0)
		{
			if (GetKeyboardTrigger(DIK_LEFT) || IsButtonTriggered(0, BUTTON_DIGITAL_LEFT) || IsButtonTriggered(0, BUTTON_ANALOG_L_LEFT))
			{
				SOposx--;
				PlaySound(SOUND_LABEL_SE_enter03);
			}
			else if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonTriggered(0, BUTTON_DIGITAL_RIGHT) || IsButtonTriggered(0, BUTTON_ANALOG_L_RIGHT))
			{
				SOposx++;
				PlaySound(SOUND_LABEL_SE_enter03);
			}
		}
		//上限
		if (SOposx > 1) SOposx = 0;
		else if (SOposx < 0) SOposx = 1;
		if (SOposy > 1) SOposy = 0;
		else if (SOposy < 0) SOposy = 1;


		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_A))
		{
			//はじめから
			if (SOposx == 0&&SOposy == 0)
			{
				UpdateReInit();
				//チュートリアル終了後にballのtutoモードを切り替える
				BALL *b = GetBall();
				for (int i = 0; i < BALL_MAX; i++, b++)
				{
					b->tuto = false;
				}
				MasterVolumeChange(0);
				SetFade(FADE_OUT, SCENE_GAMECOUNTDOWN, SOUND_LABEL_BGM_normal01);
			}
			//あきらめる
			else if (SOposx == 0 && SOposy == 1)
			{
				UpdateReInit();
				PlaySound(SOUND_LABEL_SE_enter02);
				MasterVolumeChange(1);
				SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_title01);
			}
			//オプション
			else if (SOposx == 1 && SOposy == 0)
			{
				PlaySound(SOUND_LABEL_SE_enter02);
				SetScene(SCENE_OPTION);
			}
		}
		if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			MasterVolumeChange(1);
			SetScene(SCENE_GAME);
			g_pause[0].use = false;
		}
		SetVertexPause();
	}

}


//=============================================================================
// 更新処理　シーンゲームのアップデート
//=============================================================================
void UpdateInPause(void)
{
	if (GetKeyboardTrigger(DIK_M) || IsButtonTriggered(0, BUTTON_START) && g_pause[0].use == false)
	{
		SetScene(SCENE_PAUSE);
		g_pause[0].use = true;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_pause[0].use == true)
	{
		for (int i = 0; i < PAUSEMAX; i++)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pause[i].pD3DTexture);
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_pause[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPause(void)
{
	// テクスチャのパースペクティブコレクト用
	g_pause[0].vertexWk[0].rhw =
		g_pause[0].vertexWk[1].rhw =
		g_pause[0].vertexWk[2].rhw =
		g_pause[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_pause[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_pause[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_pause[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_pause[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_pause[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_pause[1].vertexWk[0].rhw =
		g_pause[1].vertexWk[1].rhw =
		g_pause[1].vertexWk[2].rhw =
		g_pause[1].vertexWk[3].rhw = 1.0f;
	g_pause[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_pause[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_pause[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_pause[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_pause[2].vertexWk[0].rhw =
		g_pause[2].vertexWk[1].rhw =
		g_pause[2].vertexWk[2].rhw =
		g_pause[2].vertexWk[3].rhw = 1.0f;
	g_pause[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pause[2].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_pause[2].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_pause[2].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_pause[2].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPause(void)
{
	// 頂点座標の設定 
	for (int i = 0; i < PAUSEMAX; i++)
	{
		g_pause[i].vertexWk[0].vtx.x = g_pause[i].pos.x - TEXTURE_RESTART_SIZE_X;
		g_pause[i].vertexWk[0].vtx.y = g_pause[i].pos.y - TEXTURE_RESTART_SIZE_Y;
		g_pause[i].vertexWk[0].vtx.z = 0.0f;
		g_pause[i].vertexWk[1].vtx.x = g_pause[i].pos.x + TEXTURE_RESTART_SIZE_X;
		g_pause[i].vertexWk[1].vtx.y = g_pause[i].pos.y - TEXTURE_RESTART_SIZE_Y;
		g_pause[i].vertexWk[1].vtx.z = 0.0f;
		g_pause[i].vertexWk[2].vtx.x = g_pause[i].pos.x - TEXTURE_RESTART_SIZE_X;
		g_pause[i].vertexWk[2].vtx.y = g_pause[i].pos.y + TEXTURE_RESTART_SIZE_Y;
		g_pause[i].vertexWk[2].vtx.z = 0.0f;
		g_pause[i].vertexWk[3].vtx.x = g_pause[i].pos.x + TEXTURE_RESTART_SIZE_X;
		g_pause[i].vertexWk[3].vtx.y = g_pause[i].pos.y + TEXTURE_RESTART_SIZE_Y;
		g_pause[i].vertexWk[3].vtx.z = 0.0f;
	}
	if (SOposx == 0 && SOposy == 0)
	{
		g_pause[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (SOposx == 0 && SOposy == 1)
	{
		g_pause[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (SOposx == 1 && SOposy == 0)
	{
		g_pause[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_pause[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_pause[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}


PAUSE *GetPause(void)
{
	return &g_pause[0];
}


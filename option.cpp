/**
* @file option.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "ball.h"
#include "option.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexOption(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OPTION g_option[OPTIONMAX];//0感度、1コントローラー、3難易度、4R18、

static int OPposx;			//オプションカーソルのposx
static int OPposy;			//オプションカーソルのposy

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitOption(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_SENSITIV,
			&g_option[0].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_MODESELECT,
			&g_option[1].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_CONTROLTYPE,
			&g_option[2].pD3DTexture);
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_R18,
			&g_option[3].pD3DTexture);
	}

	g_option[0].pos = D3DXVECTOR3(OPTION_PX1_POS_X, OPTION_PY1_POS_Y, 0.0f);
	g_option[1].pos = D3DXVECTOR3(OPTION_PX1_POS_X, OPTION_PY2_POS_Y, 0.0f);
	g_option[2].pos = D3DXVECTOR3(OPTION_PX2_POS_X, OPTION_PY1_POS_Y, 0.0f);
	g_option[3].pos = D3DXVECTOR3(OPTION_PX2_POS_X, OPTION_PY2_POS_Y, 0.0f);

	OPposx = 0;
	OPposy = 0;
	// 頂点情報の作成
	MakeVertexOption();

	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitOption(void)
{
	OPposx = 0;
	OPposy = 0;
	SetVertexOption();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitOption(void)
{
	for (int i = 0; i < OPTIONMAX; i++)
	{
		if (g_option[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_option[i].pD3DTexture->Release();
			g_option[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// 更新処理　シーンオプションでアップデート
//=============================================================================
void UpdateOption(void)
{
		if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_DIGITAL_UP) || IsButtonTriggered(0, BUTTON_ANALOG_L_UP))
		{
			OPposy--;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DIGITAL_DOWN) || IsButtonTriggered(0, BUTTON_ANALOG_L_DOWN))
		{
			OPposy++;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
		else if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonTriggered(0, BUTTON_DIGITAL_RIGHT) || IsButtonTriggered(0, BUTTON_ANALOG_L_RIGHT))
		{
			OPposx++;
			PlaySound(SOUND_LABEL_SE_enter03);
		}
		else if (GetKeyboardTrigger(DIK_LEFT) || IsButtonTriggered(0, BUTTON_DIGITAL_LEFT) || IsButtonTriggered(0, BUTTON_ANALOG_L_LEFT))
		{
			OPposx--;
			PlaySound(SOUND_LABEL_SE_enter03);
		}

		//上限
		if (OPposx > 1) OPposx = 0;
		else if (OPposx < 0) OPposx = 1;
		if (OPposy > 1) OPposy = 0;
		else if (OPposy < 0) OPposy = 1;


		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_A))
		{
			//感度
			if (OPposx == 0 && OPposy == 0)
			{
				PlaySound(SOUND_LABEL_SE_enter02);
				SetScene(SCENE_SENSITIVITY);
			}
			//コントローラー
			else if (OPposx == 1 && OPposy == 0)
			{
				PlaySound(SOUND_LABEL_SE_enter02);
				SetScene(SCENE_CONTYPE);
			}
			//難易度
			else if (OPposx == 0 && OPposy == 1)
			{
				PlaySound(SOUND_LABEL_SE_enter02);
				UpdateReInit();
				//チュートリアル終了後にballのtutoモードを切り替える
				BALL *b = GetBall();
				for (int i = 0; i < BALL_MAX; i++, b++)
				{
					b->tuto = false;
				}
				SetFade(FADE_OUT, SCENE_SELECT, SOUND_LABEL_BGM_select01);
				MasterVolumeChange(1);
			}
			//R18
			else if (OPposx == 1 && OPposy == 1)
			{
				PlaySound(SOUND_LABEL_SE_enter02);
				SetScene(SCENE_R18SELECT);
			}
		}
		if (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_B))
		{
			PlaySound(SOUND_LABEL_SE_enter02);
			SetScene(SCENE_PAUSE);
		}
		SetVertexOption();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawOption(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		for (int i = 0; i < OPTIONMAX; i++)
		{
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_option[i].pD3DTexture);
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_option[i].vertexWk, sizeof(VERTEX_2D));
		}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexOption(void)
{
	// テクスチャのパースペクティブコレクト用
	g_option[0].vertexWk[0].rhw =
		g_option[0].vertexWk[1].rhw =
		g_option[0].vertexWk[2].rhw =
		g_option[0].vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_option[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_option[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_option[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_option[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_option[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_option[1].vertexWk[0].rhw =
		g_option[1].vertexWk[1].rhw =
		g_option[1].vertexWk[2].rhw =
		g_option[1].vertexWk[3].rhw = 1.0f;
	g_option[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_option[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_option[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_option[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_option[2].vertexWk[0].rhw =
		g_option[2].vertexWk[1].rhw =
		g_option[2].vertexWk[2].rhw =
		g_option[2].vertexWk[3].rhw = 1.0f;
	g_option[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[2].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_option[2].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_option[2].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_option[2].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_option[3].vertexWk[0].rhw =
		g_option[3].vertexWk[1].rhw =
		g_option[3].vertexWk[2].rhw =
		g_option[3].vertexWk[3].rhw = 1.0f;
	g_option[3].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[3].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[3].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[3].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_option[3].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_option[3].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_option[3].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_option[3].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexOption(void)
{
	// 頂点座標の設定 
	for (int i = 0; i < OPTIONMAX ; i++)
	{
		g_option[i].vertexWk[0].vtx.x = g_option[i].pos.x - TEXTURE_SENSITIV_SIZE_X;
		g_option[i].vertexWk[0].vtx.y = g_option[i].pos.y - TEXTURE_SENSITIV_SIZE_Y;
		g_option[i].vertexWk[0].vtx.z = 0.0f;
		g_option[i].vertexWk[1].vtx.x = g_option[i].pos.x + TEXTURE_SENSITIV_SIZE_X;
		g_option[i].vertexWk[1].vtx.y = g_option[i].pos.y - TEXTURE_SENSITIV_SIZE_Y;
		g_option[i].vertexWk[1].vtx.z = 0.0f;
		g_option[i].vertexWk[2].vtx.x = g_option[i].pos.x - TEXTURE_SENSITIV_SIZE_X;
		g_option[i].vertexWk[2].vtx.y = g_option[i].pos.y + TEXTURE_SENSITIV_SIZE_Y;
		g_option[i].vertexWk[2].vtx.z = 0.0f;
		g_option[i].vertexWk[3].vtx.x = g_option[i].pos.x + TEXTURE_SENSITIV_SIZE_X;
		g_option[i].vertexWk[3].vtx.y = g_option[i].pos.y + TEXTURE_SENSITIV_SIZE_Y;
		g_option[i].vertexWk[3].vtx.z = 0.0f;
	}

	if (OPposx == 0 && OPposy == 0)
	{
		g_option[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (OPposx == 0 && OPposy == 1)
	{
		g_option[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (OPposx == 1 && OPposy == 0)
	{
		g_option[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[3].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
	}
	else if (OPposx == 1 && OPposy == 1)
	{
		g_option[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		g_option[3].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[3].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[3].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_option[3].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

}


OPTION *GetOption(void)
{
	return &g_option[0];
}


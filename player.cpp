/**
* @file player.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "game.h"
#include "player.h"

#ifdef _DEBUG
#include "input.h"
#include "fade.h"
#include "sound.h"
#endif



//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER_PIT g_player_pit;
PLAYER_BAT g_player_bat;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < PLAYER_GOUKEI; i++)
	{
		switch (i)
		{
			//ピッチャー初期化
		case TYPE_PIT:
			g_player_pit.pp.pos = D3DXVECTOR3(SCREEN_CENTER_X, 200.0f, 0.0f);
			g_player_pit.pp.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_pit.pp.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_pit.pp.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_pit.pp.direction = 0;
			g_player_pit.pp.fps = 0;
			g_player_pit.pp.nCountAnim = 0;
			g_player_pit.pp.nPatternAnim = 0;
			g_player_pit.pp.motion = false;											//真アニメしている 偽アニメしていない
			g_player_pit.pp.use = true;											//真使用している(表示描画する) 偽使用していない

			// テクスチャの読み込み  
			if (type == 0)	// 初回のみ読み込む
			{
				D3DXCreateTextureFromFile(pDevice,				// デバイスのポインタ
					TEXTURE_GAME_PITCHER,				// ファイルの名前
					&g_player_pit.pp.pD3DTexture);				// 読み込むメモリのポインタ
			}
			// 頂点情報の作成
			MakeVertexPlayer(i);
			break;

			//打者の初期化
		case TYPE_BAT:
			g_player_bat.pb.pos = D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, SCREEN_CENTER_Y + 300.0f, 0.0f);
			g_player_bat.pb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_bat.pb.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_bat.pb.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_bat.pb.direction = 0;
			g_player_bat.pb.fps = 0;
			g_player_bat.pb.nCountAnim = 0;
			g_player_bat.pb.nPatternAnim = 0;
			g_player_bat.pb.motion = false;									//真スイングしている 偽スイングしていない
			g_player_bat.pb.use = true;											//真使用している(表示描画する) 偽使用していない

			// テクスチャの読み込み  
			if (type == 0)	// 初回のみ読み込む
			{
				D3DXCreateTextureFromFile(pDevice,			// デバイスのポインタ
					TEXTURE_GAME_BATTER,				// ファイルの名前
					&g_player_bat.pb.pD3DTexture);			// 読み込むメモリのポインタ
			}
			// 頂点情報の作成
			MakeVertexPlayer(i);
			break;
		}
	}
	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
void ReInitPlayer(void)
{
	g_player_pit.pp.pos = D3DXVECTOR3(SCREEN_CENTER_X, 200.0f, 0.0f);
	g_player_pit.pp.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	g_player_pit.pp.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	g_player_pit.pp.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	g_player_pit.pp.nCountAnim = 0;		
	g_player_pit.pp.fps= 0;
	g_player_pit.pp.nPatternAnim = 0;								
	g_player_pit.pp.motion = false;									
	g_player_pit.pp.use = false;									

	g_player_bat.pb.pos = D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, SCREEN_CENTER_Y + 300.0f, 0.0f);
	g_player_bat.pb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player_bat.pb.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	g_player_bat.pb.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	g_player_bat.pb.direction = 0;
	g_player_bat.pb.fps = 0;
	g_player_bat.pb.nCountAnim = 0;									
	g_player_bat.pb.nPatternAnim = 0;								
	g_player_bat.pb.motion = false;									
	g_player_bat.pb.use = true;										
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	//pit破棄
	if (g_player_pit.pp.pD3DTexture != NULL)	// 画像が読み込まれていたらテクスチャを破棄している
	{	// テクスチャの開放
		g_player_pit.pp.pD3DTexture->Release();
		g_player_pit.pp.pD3DTexture = NULL;
	}

	//bat破棄
	if (g_player_bat.pb.pD3DTexture != NULL)	// 画像が読み込まれていたらテクスチャを破棄している
	{	// テクスチャの開放
		g_player_bat.pb.pD3DTexture->Release();
		g_player_bat.pb.pD3DTexture = NULL;
	}

}


//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Bat();
	Pit();

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_5)) SetFade(FADE_OUT, SCENE_RESULT_FIELD, SOUND_LABEL_BGM_gameover01);
	if (GetKeyboardPress(DIK_6)) SetFade(FADE_OUT, SCENE_RESULT_CLEAR, SOUND_LABEL_BGM_gameclear01);
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//バッター表示
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定  
	pDevice->SetTexture(0, g_player_bat.pb.pD3DTexture);
	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_player_bat.pb.vertexWk, sizeof(VERTEX_2D));
	//ピッチャー表示
	pDevice->SetTexture(0, g_player_pit.pp.pD3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_player_pit.pp.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (i)
	{
	case TYPE_PIT:
	{
		// 頂点座標の設定
		SetVertexPlayer(i);

		// rhwの設定　頂点が重なった時の描画順番
		g_player_pit.pp.vertexWk[0].rhw =
			g_player_pit.pp.vertexWk[1].rhw =
			g_player_pit.pp.vertexWk[2].rhw =
			g_player_pit.pp.vertexWk[3].rhw = 1.0f;

		// 反射光の設定  頂点カラー指定した色とテクスチャの色が混ざってカラーリングされる
		// フェードインは始めに表示したテクスチャの上に透明なテクスチャを表示。RGBAのAを徐々に不透明にしていく
		g_player_pit.pp.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_pit.pp.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_pit.pp.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_pit.pp.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定  
		g_player_pit.pp.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_player_pit.pp.vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_X, 0.0f);
		g_player_pit.pp.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_Y);
		g_player_pit.pp.vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_X, 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_Y);
		break;
	}
	case TYPE_BAT:
	{
		// 頂点座標の設定
		SetVertexPlayer(i);

		// rhwの設定　頂点が重なった時の描画順番
		g_player_bat.pb.vertexWk[0].rhw =
			g_player_bat.pb.vertexWk[1].rhw =
			g_player_bat.pb.vertexWk[2].rhw =
			g_player_bat.pb.vertexWk[3].rhw = 1.0f;

		// 反射光の設定  頂点カラー指定した色とテクスチャの色が混ざってカラーリングされる
		// フェードインは始めに表示したテクスチャの上に透明なテクスチャを表示。RGBAのAを徐々に不透明にしていく
		g_player_bat.pb.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_bat.pb.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_bat.pb.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_bat.pb.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定  
		g_player_bat.pb.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_player_bat.pb.vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_X, 0.0f);
		g_player_bat.pb.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_Y);
		g_player_bat.pb.vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_X, 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_Y);
		break;
	}
	default:
		break;
	}
	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer(int cntPattern, int i)
{
	switch (i)
	{
	case TYPE_PIT:
	{
		// テクスチャ座標の設定
		int x_pit = cntPattern % TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		int y_pit = cntPattern / TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		float sizeX_pit = 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		float sizeY_pit = 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_Y;

		g_player_pit.pp.vertexWk[0].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit, (float)(y_pit)* sizeY_pit);
		g_player_pit.pp.vertexWk[1].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit + sizeX_pit, (float)(y_pit)* sizeY_pit);
		g_player_pit.pp.vertexWk[2].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit, (float)(y_pit)* sizeY_pit + sizeY_pit);
		g_player_pit.pp.vertexWk[3].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit + sizeX_pit, (float)(y_pit)* sizeY_pit + sizeY_pit);
		break;
	}
	case TYPE_BAT:
	{
		// テクスチャ座標の設定
		int x_bat = cntPattern % TEXTURE_BATTER_PATTERN_DIVIDE_X;
		int y_bat = cntPattern / TEXTURE_BATTER_PATTERN_DIVIDE_X;
		float sizeX_bat = 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_X;
		float sizeY_bat = 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_Y;

		g_player_bat.pb.vertexWk[0].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat, (float)(y_bat)* sizeY_bat);
		g_player_bat.pb.vertexWk[1].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat + sizeX_bat, (float)(y_bat)* sizeY_bat);
		g_player_bat.pb.vertexWk[2].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat, (float)(y_bat)* sizeY_bat + sizeY_bat);
		g_player_bat.pb.vertexWk[3].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat + sizeX_bat, (float)(y_bat)* sizeY_bat + sizeY_bat);
		break;
	}
	default:
		break;
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(int i)
{
	switch (i)
	{
	case TYPE_PIT:
	{
		// 頂点座標の設定 
		g_player_pit.pp.vertexWk[0].vtx.x = g_player_pit.pp.pos.x - TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[0].vtx.y = g_player_pit.pp.pos.y - TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[0].vtx.z = 0.0f;

		g_player_pit.pp.vertexWk[1].vtx.x = g_player_pit.pp.pos.x + TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[1].vtx.y = g_player_pit.pp.pos.y - TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[1].vtx.z = 0.0f;

		g_player_pit.pp.vertexWk[2].vtx.x = g_player_pit.pp.pos.x - TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[2].vtx.y = g_player_pit.pp.pos.y + TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[2].vtx.z = 0.0f;

		g_player_pit.pp.vertexWk[3].vtx.x = g_player_pit.pp.pos.x + TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[3].vtx.y = g_player_pit.pp.pos.y + TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[3].vtx.z = 0.0f;
		break;
	}
	case TYPE_BAT:
	{
		// 頂点座標の設定 
		g_player_bat.pb.vertexWk[0].vtx.x = g_player_bat.pb.pos.x - TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[0].vtx.y = g_player_bat.pb.pos.y - TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[0].vtx.z = 0.0f;

		g_player_bat.pb.vertexWk[1].vtx.x = g_player_bat.pb.pos.x + TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[1].vtx.y = g_player_bat.pb.pos.y - TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[1].vtx.z = 0.0f;

		g_player_bat.pb.vertexWk[2].vtx.x = g_player_bat.pb.pos.x - TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[2].vtx.y = g_player_bat.pb.pos.y + TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[2].vtx.z = 0.0f;

		g_player_bat.pb.vertexWk[3].vtx.x = g_player_bat.pb.pos.x + TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[3].vtx.y = g_player_bat.pb.pos.y + TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[3].vtx.z = 0.0f;
		break;
	}
	default:
		break;
	}
}

//=============================================================================
// 各プレイヤーのアドレスを返す
//=============================================================================
PLAYER_PIT *GetPlayerPit(void)
{
	return &g_player_pit;
}
PLAYER_BAT *GetPlayerBat(void)
{
	return &g_player_bat;
}

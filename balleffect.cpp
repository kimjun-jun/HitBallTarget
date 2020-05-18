/**
* @file balleffect.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "ball.h"
#include "balleffect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define EMISSION_FULL 0
#define EMISSION_RATE 1

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBalleffect(int i);
void SetTextureBalleffect(int i, int n, int cntPattern);
void SetVertexBalleffect(int i, int n);
void ResetParticle(int i, int n);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureBalleffectType0 = NULL;		// テクスチャへのポリゴン
static LPDIRECT3DTEXTURE9		g_pD3DTextureBalleffectType1 = NULL;		// テクスチャへのポリゴン

static BALLEFFECT					balleffectWk[BALLEFFECT_NUM_BALLEFFECTS];	// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBalleffect(int type)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			BALLEFFECT_TEXTURETYPE0,										// ファイルの名前
			&g_pD3DTextureBalleffectType0);								// 読み込むメモリのポインタ
				// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
			BALLEFFECT_TEXTURETYPE1,										// ファイルの名前
			&g_pD3DTextureBalleffectType1);								// 読み込むメモリのポインタ
	}

	// 初期化処理
	for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
	{
		balleffectWk[i].use = false;
		balleffectWk[i].elapsed = 0;

		MakeVertexBalleffect(i);										// 頂点情報の作成

		for (int n = 0; n < BALLEFFECT_NUM_PARTS; n++)
		{
			balleffectWk[i].pParticle[n].Texture = g_pD3DTextureBalleffectType0;
			ResetParticle(i, n);
		}
	}

	return S_OK;
}

//=============================================================================
// パーティクルのリセット
//=============================================================================
void ResetParticle(int i, int n)
{
	balleffectWk[i].pParticle[n].pos = D3DXVECTOR3(balleffectWk[i].pos.x + rand() % 30 - 15, balleffectWk[i].pos.y + rand() % 30 - 15, 0.0f);	// 座標データを初期化
	balleffectWk[i].pParticle[n].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 移動量

	balleffectWk[i].pParticle[n].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
	balleffectWk[i].pParticle[n].CountAnim = 0;										// アニメカウントを初期化
	balleffectWk[i].pParticle[n].liveTime = 10;
	balleffectWk[i].pParticle[n].isFinish = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBalleffect(void)
{
	if (g_pD3DTextureBalleffectType0 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBalleffectType0->Release();
		g_pD3DTextureBalleffectType0 = NULL;
	}
	if (g_pD3DTextureBalleffectType1 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBalleffectType1->Release();
		g_pD3DTextureBalleffectType1 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBalleffect(void)
{
	for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
	{
		if (balleffectWk[i].use)
		{
			if (balleffectWk[i].isEnding) {
				balleffectWk[i].use = FALSE;
				continue;
			}

			//エミットが有効であればエフェクト作成処理を行う
			if (balleffectWk[i].isRemoveOnFinish == FALSE)
			{

				//エフェクト作成レートの増加処理
				if (balleffectWk[i].balleffectCount < BALLEFFECT_NUM_PARTS)
					balleffectWk[i].emitCounter++;

				//バッファに空きがあり、追加タイミングが来ていれば新たなエフェクトを追加する
				while ((balleffectWk[i].balleffectCount < BALLEFFECT_NUM_PARTS) && (balleffectWk[i].emitCounter > EMISSION_RATE))
				{
					//全体追加フラグがONであれば空き領域全てに新たなエフェクトを追加する
					if (EMISSION_FULL)
						balleffectWk[i].balleffectCount = BALLEFFECT_NUM_PARTS;
					else
						balleffectWk[i].balleffectCount++;

					//エフェクト作成レートの初期化
					balleffectWk[i].emitCounter = 0;
				}

				balleffectWk[i].elapsed++;

				//時間超過
				if ((balleffectWk[i].duration != -1) && (balleffectWk[i].duration < balleffectWk[i].elapsed)) {
					balleffectWk[i].isRemoveOnFinish = TRUE;
				}
			}

			int balleffectIndex = 0;

			//エフェクトの更新処理
			while (balleffectIndex < balleffectWk[i].balleffectCount)
			{
				if (balleffectWk[i].pParticle[balleffectIndex].liveTime > 0)
				{
					//生存フレーム減少
					balleffectWk[i].pParticle[balleffectIndex].liveTime--;

					//アニメパターン進行
					if (++balleffectWk[i].pParticle[balleffectIndex].CountAnim > BALLEFFECT_TIME_ANIMATION) {
						//アニメパターンが最大値に達した場合でも終了
						if (++balleffectWk[i].pParticle[balleffectIndex].PatternAnim >= (BALLEFFECT_ANIM_PATTERN_NUM - 1))
						{
							balleffectWk[i].pParticle[balleffectIndex].PatternAnim = BALLEFFECT_ANIM_PATTERN_NUM - 1;
							balleffectWk[i].pParticle[balleffectIndex].liveTime = 0;
						}

						balleffectWk[i].pParticle[balleffectIndex].CountAnim = 0;
					}

					SetTextureBalleffect(i, balleffectIndex, balleffectWk[i].pParticle[balleffectIndex].PatternAnim);

					SetVertexBalleffect(i, balleffectIndex);						// 移動後の座標で頂点を設定

					balleffectIndex++;
				}
				else {
					if (balleffectWk[i].isRemoveOnFinish) {
						if (balleffectWk[i].pParticle[balleffectIndex].isFinish == 0)
						{
							balleffectWk[i].pParticle[balleffectIndex].isFinish = 1;
							balleffectWk[i].numFinish++;
						}
						//終了処理
						if (balleffectWk[i].pParticle[balleffectIndex].pos.x <= SCREEN_W - SCREEN_W || balleffectWk[i].pParticle[balleffectIndex].pos.x >= SCREEN_W ||
							balleffectWk[i].pParticle[balleffectIndex].pos.y <= SCREEN_H - SCREEN_H || balleffectWk[i].pParticle[balleffectIndex].pos.y >= SCREEN_H)
						{
							balleffectWk[i].isEnding = TRUE;
							break;
						}
						if (balleffectWk[i].numFinish == balleffectWk[i].balleffectCount)
						{
							balleffectWk[i].isEnding = TRUE;
							break;
						}
						balleffectIndex++;
					}
					else {
						//バッファを初期化する
						ResetParticle(i, balleffectIndex);

						//末尾でなければインデックスを詰める
						if (balleffectIndex != (balleffectWk[i].balleffectCount - 1))
						{
							balleffectWk[i].pParticle[balleffectIndex] = balleffectWk[i].pParticle[balleffectWk[i].balleffectCount - 1];
							ResetParticle(i, (balleffectWk[i].balleffectCount - 1));
						}
						balleffectWk[i].balleffectCount--;
					}
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBalleffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (GetBall()->effect==false)
	{
		for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
		{
			if (balleffectWk[i].use)
			{
				for (int n = 0; n < balleffectWk[i].balleffectCount; n++)
				{
					if (balleffectWk[i].pParticle[n].isFinish == 0) {
						// テクスチャの設定
						pDevice->SetTexture(0, balleffectWk[i].pParticle[n].Texture);
						// ポリゴンの描画
						pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, balleffectWk[i].pParticle[n].vertexWk, sizeof(VERTEX_2D));
					}
				}
			}
		}
	}
	else if (GetBall()->effect == true)
	{
		for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
		{
			if (balleffectWk[i].use)
			{
				for (int n = 0; n < balleffectWk[i].balleffectCount; n++)
				{
					if (balleffectWk[i].pParticle[n].isFinish == 0) {
						// テクスチャの設定
						pDevice->SetTexture(0, g_pD3DTextureBalleffectType1);
						// ポリゴンの描画
						pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, balleffectWk[i].pParticle[n].vertexWk, sizeof(VERTEX_2D));
					}
				}
			}
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBalleffect(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int n = 0; n < BALLEFFECT_NUM_PARTS; n++) {

		// 頂点座標の設定
		SetVertexBalleffect(i, n);
		// 頂点座標の設定
		SetTextureBalleffect(i, n, 0);

		// rhwの設定
		balleffectWk[i].pParticle[n].vertexWk[0].rhw =
			balleffectWk[i].pParticle[n].vertexWk[1].rhw =
			balleffectWk[i].pParticle[n].vertexWk[2].rhw =
			balleffectWk[i].pParticle[n].vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		balleffectWk[i].pParticle[n].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		balleffectWk[i].pParticle[n].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		balleffectWk[i].pParticle[n].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		balleffectWk[i].pParticle[n].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBalleffect(int i, int n, int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / BALLEFFECT_TEXTURE_PATTERN_DIVIDE_Y;

	balleffectWk[i].pParticle[n].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	balleffectWk[i].pParticle[n].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	balleffectWk[i].pParticle[n].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	balleffectWk[i].pParticle[n].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBalleffect(int i, int n)
{
	// 頂点座標の設定
	balleffectWk[i].pParticle[n].vertexWk[0].vtx.x = balleffectWk[i].pParticle[n].pos.x - BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[0].vtx.y = balleffectWk[i].pParticle[n].pos.y - BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[0].vtx.z = 0.0f;

	balleffectWk[i].pParticle[n].vertexWk[1].vtx.x = balleffectWk[i].pParticle[n].pos.x + BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[1].vtx.y = balleffectWk[i].pParticle[n].pos.y - BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[1].vtx.z = 0.0f;

	balleffectWk[i].pParticle[n].vertexWk[2].vtx.x = balleffectWk[i].pParticle[n].pos.x - BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[2].vtx.y = balleffectWk[i].pParticle[n].pos.y + BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[2].vtx.z = 0.0f;

	balleffectWk[i].pParticle[n].vertexWk[3].vtx.x = balleffectWk[i].pParticle[n].pos.x + BALLEFFECT_TEXTURE_SIZE_X;
	balleffectWk[i].pParticle[n].vertexWk[3].vtx.y = balleffectWk[i].pParticle[n].pos.y + BALLEFFECT_TEXTURE_SIZE_Y;
	balleffectWk[i].pParticle[n].vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エフェクトのセット
//=============================================================================
void SetBalleffect(D3DXVECTOR3 pos, int duration)
{
	// もし未使用のエフェクトが無かったら実行しない( =これ以上表示できないって事 )
	for (int i = 0; i < BALLEFFECT_NUM_BALLEFFECTS; i++)
	{
		if (balleffectWk[i].use == false)		// 未使用状態のエフェクトを見つける
		{
			balleffectWk[i].use = true;
			balleffectWk[i].isEnding = false;
			balleffectWk[i].isRemoveOnFinish = FALSE;

			balleffectWk[i].duration = duration;
			balleffectWk[i].pos.x = pos.x;			// 座標をセット
			balleffectWk[i].pos.y = pos.y;			// 座標をセット

			balleffectWk[i].balleffectCount = 0;
			balleffectWk[i].elapsed = 0;
			balleffectWk[i].emitCounter = 0;
			balleffectWk[i].numFinish = 0;

			//パーティクルの初期化
			for (int n = 0; n < BALLEFFECT_NUM_PARTS; n++)
			{
				ResetParticle(i, n);
			}
			return;							// 1個セットしたので終了する
		}
	}
}

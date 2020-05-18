/**
* @file balleffect.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once


// マクロ定義
#define BALLEFFECT_TEXTURETYPE0			_T("data/TEXTURE/item/ball2.png")	// 画像
#define BALLEFFECT_TEXTURETYPE1			_T("data/TEXTURE/effect/ballbom.png")	// 画像
#define BALLEFFECT_TEXTURE_SIZE_X	(20/2)		// テクスチャサイズ
#define BALLEFFECT_TEXTURE_SIZE_Y	(20/2)		// 同上

#define BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define BALLEFFECT_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define BALLEFFECT_ANIM_PATTERN_NUM			(BALLEFFECT_TEXTURE_PATTERN_DIVIDE_X*BALLEFFECT_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define BALLEFFECT_TIME_ANIMATION			(1)	// アニメーションの切り替わるカウント


#define BALLEFFECT_NUM_PARTS 1
#define BALLEFFECT_NUM_BALLEFFECTS 5


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エフェクト構造体
{
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		move;						// 移動量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	int				liveTime;

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	bool			isFinish;
}PARTICLE;

typedef struct	// エフェクト構造体
{
	int				use;
	int				isEnding;
	bool			isRemoveOnFinish;

	D3DXVECTOR3		pos;						// ポリゴンの移動量

	int				duration;
	int				elapsed;
	int				numFinish;

	int				balleffectCount;
	int				emitCounter;

	PARTICLE		pParticle[BALLEFFECT_NUM_PARTS];

}BALLEFFECT;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBalleffect(int type);
void UninitBalleffect(void);
void UpdateBalleffect(void);
void DrawBalleffect(void);
void SetBalleffect(D3DXVECTOR3 pos, int duration);

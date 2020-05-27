/**
* @file collision.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief 当たり判定BB関数 CollisionBB
* @param[in] D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2
* @return bool
* @details BBで当たり判定したい座標とサイズを渡す
*/
bool CollisionBB(D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2);

/**
* @brief 当たり判定BC関数 CollisionBC
* @param[in] D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2
* @return bool
* @details BCで当たり判定したい座標とサイズを渡す
*/
bool CollisionBC(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2);

/**
* @brief 当たり判定確認関数 CheakHit
*/
void CheakHit(void);

/**
* @brief ボールループの初期化関数 LoopInit
*/
void LoopInit(void);

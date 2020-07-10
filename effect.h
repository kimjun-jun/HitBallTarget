/**
* @file effect.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief Effect設定関数 DeadEffect
* @param[in] EnemyNum	エネミー添え字
* @param[in] EnemyType	エネミー種類(TYPE_CAT=0,TYPE_SURAIMU=1,TYPE_HINOTAMA=2,	TYPE_UFO=3)
)
*/
void DeadEffect(int EnemyNum, int EnemyType);

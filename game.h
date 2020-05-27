/**
* @file game.h
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#pragma once

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
/**
* @brief バッター処理関数 Bat
* @details バッターアニメーションとミートカーソルを処理する
*/
void Bat(void);

/**
* @brief ピッチャー処理関数 Pit
* @details 投球を制御→ボールを発射する
*/
void Pit(void);

/**
* @brief 投球処理関数 Ball
* @details 投球されたボールの処理。変化や影、投球地点を処理
*/
void Ball(void);

/**
* @brief 打球処理関数 Hitball
* @details 打球方向や移動を処理
*/
void Hitball(void);

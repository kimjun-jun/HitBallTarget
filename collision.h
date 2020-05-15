///*******************************************************************************
//* タイトル:		キムジュンデンセツ(3)
//* プログラム名:	collision.h
//* 作成者:			GP11B292 08 キムラジュン
//********************************************************************************/
#pragma once
bool CollisionBB(D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2);
bool CollisionBC(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2);
void CheakHit(void);
void LoopInit(void);

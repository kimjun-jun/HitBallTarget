/**
* @file effect.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"

//=============================================================================
// エフェクト関数(update)
//=============================================================================
void DeadEffect(int EnemyNum, int EnemyType)
{
	switch (EnemyType)
	{
	case TYPE_CAT:
	{
		CAT *cat = GetCat(EnemyNum);
		cat->colori -= TEXTURE_COROLSPEED;
		cat->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		cat->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		cat->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, cat->colori, cat->colori, cat->colori);
		//死んでcoloriが変色終わると消す
		if (cat->use == true && cat->colori <= 0)
		{
			cat->use = false;
			AddScore(1, ENEMY_VAL);
			AddScore(cat->point, SCORE_VAL);
		}
		break;
	}
	case TYPE_SURAIMU:
	{
		SURAIMU *suraimu = GetSuraimu(EnemyNum);
		suraimu->colori -= TEXTURE_COROLSPEED;
		suraimu->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		suraimu->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		suraimu->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, suraimu->colori, suraimu->colori, suraimu->colori);
		//死んでcoloriが変色終わると消す
		if (suraimu->use == true && suraimu->colori <= 0)
		{
			suraimu->use = false;
			AddScore(1, ENEMY_VAL);
			AddScore(suraimu->point, SCORE_VAL);
		}
		break;
	}
	case TYPE_HINOTAMA:
	{
		HINOTAMA *hinotama = GetHinotama(EnemyNum);
		hinotama->colori -= TEXTURE_COROLSPEED;
		hinotama->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		hinotama->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		hinotama->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, hinotama->colori, hinotama->colori, hinotama->colori);
		//死んでcoloriが変色終わると消す
		if (hinotama->use == true && hinotama->colori <= 0)
		{
			hinotama->use = false;
			AddScore(1, ENEMY_VAL);
			AddScore(hinotama->point, SCORE_VAL);
		}
		break;
	}
	case TYPE_UFO:
	{
		UFO *ufo = GetUfo(EnemyNum);
		ufo->colori -= TEXTURE_COROLSPEED;
		ufo->ppos[0] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->ppos[1] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->ppos[2] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->ppos[3] += D3DXVECTOR3(MOTION_EFFECT_SPEED_MID, MOTION_EFFECT_SPEED_MID, 0.0f);
		ufo->vertexWk[0].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[1].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[2].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[3].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[4].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[5].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[6].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[7].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[8].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[9].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[10].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[11].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[12].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[13].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[14].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		ufo->vertexWk[15].diffuse += D3DCOLOR_RGBA(255, ufo->colori, ufo->colori, ufo->colori);
		//死んでcoloriが変色終わると消す
		if (ufo->use == true && ufo->colori <= 0)
		{
			ufo->use = false;
		}
		break;
	}
	}
}


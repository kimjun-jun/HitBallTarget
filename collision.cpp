/**
* @file collision.cpp
* @brief HitBallTarget(2D)的当てゲーム
* @author キムラジュン
* @date 2019/09/01
*/
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"
#include "ui.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
#include "effect.h"
#include "collision.h"


//=============================================================================
// 当たり判定BB
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2)
{
	if (pos1.x + w1 >= pos2.x - w2
		&& pos1.x - w1 <= pos2.x + w2
		&& pos1.y + h1 >= pos2.y - h2
		&& pos1.y - h1 <= pos2.y + h2)
	{
		//当たっている
		return true;
	}
	//当たっていない
	return false;
}

//=============================================================================
// 当たり判定BC
//=============================================================================
bool CollisionBC(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2)
{
	//式1 プレイヤーの中心からエネミーの中心までの距離をplayer_ballettに代入
	//プレイヤー(player->pos)とバレット(enemy->pos)の距離(差、または、-)をplayer_balletに3次元(x,y,z)で定義格納している
	//「推測」→もし2次元ならD3DXVECTOR2を使う。今回player->posとenemy->posを3次元で定義しているためD3DXVECTOR3を使ってplayer_balletを3次元定義している
	D3DXVECTOR3 distance_pos = pos1 - pos2;

	//式2 プレイヤーサークル(ボディ)の半径
	//playerのpos(D3DXVECTOR3なので3次元)のx座標から当たり判定用テクスチャサイズ(プレイヤー半径)を差し引いた値をplayer_r(プレイヤー半径)に代入
	float wr1 = r1;
	//式2 エネミーサークル(ボディ)の半径
	float wr2 = r2;

	//D3DXVec2LengthSq()関数でdistance_pos(3次元)を2乗している
	//D3DXVec2Length()関数だとdistance_pos(3次元)を2乗したものに√をつける
	float dista = D3DXVec3LengthSq(&distance_pos);

	float wr3 = (wr1 + wr2)*(wr1 + wr2);

	//当たり判定
	if (dista <= wr3)
	{
		//当たっている
		return true;
	}
	return false;
}

//=============================================================================
//衝突判定
//=============================================================================
void CheakHit(void)
{
	PLAYER_PIT *pp = GetPlayerPit();
	PLAYER_BAT *pb = GetPlayerBat();
	CAT *cat = GetCat(0);
	SURAIMU *suraimu = GetSuraimu(0);
	HINOTAMA *hinotama = GetHinotama(0);
	UFO *ufo = GetUfo(0);
	BALL *b = GetBall();
	BALLCURSOR *bc = GetBallcursor();
	BALLSHADOW *bs = GetBallshadow();
	CURSOR *cursor = Get_Cursor();
	STRIKE *strike = GetStrike();
	BE *be = GetBE(0);
	char str[256] = { 0 };

	if (b->use == true)
	{
		//ボールカーソルとボール(タイミングZ軸)と打者 BB ok
		D3DXVECTOR3 pb_dead_pos = pb->pb.pos;//batポリゴンの中心が描画されてるテクスチャの中心でないため、デッドボール判定用にテクスチャ中心のposを作成
		pb_dead_pos.x -= 50;
		if (b->OorD == true)
		{
#ifdef _DEBUG
			if (CollisionBB(b->pos, TEXTURE_BALL_SIZE_Y, TEXTURE_BALL_SIZE_X, pb_dead_pos, TEXTURE_BATTER_COLLISION_BB_SIZE_Y, TEXTURE_BATTER_COLLISION_BB_SIZE_X))
			{
				//デッドボール
				if (b->pos.y >= b->pos.y - 10)
				{
					//AddScore(1);
					//UpdateGameODloop(GAME_OD_NEXT);
					sprintf(str, "デッドボール");
					SelectText(str);
				}
			}
#endif
			//ボールカーソルとボール(タイミングY軸)とミートカーソル BC
			float cdeta = 0.0f;
			if (cursor->c.meet % 2 == 0) cdeta = TEXTURE_CURSOR_BIG_COLLISION_BC_SIZE;
			else cdeta = TEXTURE_CURSOR_SMALL_COLLISION_BC_SIZE;
			if (CollisionBC(bc->pos, TEXTURE_BALL_COLLISION_BC_SIZE, cursor->c.pos, cdeta))
			{
				//打球処理 タイミングはパターンとカウントで判定する
				if (pb->pb.motion == true && b->pos.y >= bc->pos.y - BALL_JUST_TIMING_RED && pb->pb.nPatternAnim >= BAT_PATTERN2 && pb->pb.nPatternAnim <= BAT_PATTERN3)
				{
					if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL_KARABURI && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL_FOUL)
					{
#ifdef _DEBUG
						sprintf(str, "1");
						SelectText(str);
#endif
						PlaySound(SOUND_LABEL_SE_attack03);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_PULL_KARABURI;
					}
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL_FOUL && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL_MAX)
					{
#ifdef _DEBUG
						sprintf(str, "2");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_PULL_FOUL;
					}
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL_MAX && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL_MID)
					{
#ifdef _DEBUG
						sprintf(str, "3");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_PULL_MAX;
					}
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL_MID && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL_MIN)
					{
#ifdef _DEBUG
						sprintf(str, "4");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_PULL_MID;
					}
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL_MIN && b->pos.y <= cursor->c.pos.y - BALL_TIMING_JUST_MAX)
					{
#ifdef _DEBUG
						sprintf(str, "5");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_PULL_MIN;
					}
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_JUST_MAX && b->pos.y <= cursor->c.pos.y - BALL_TIMING_JUST)
					{
#ifdef _DEBUG
						sprintf(str, "6");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack02);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_JUST_MAX;
					}
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_JUST && b->pos.y <= cursor->c.pos.y + BALL_TIMING_JUST)
					{
#ifdef _DEBUG
						sprintf(str, "7");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack02);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_JUST;
					}
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_JUST && b->pos.y <= cursor->c.pos.y + BALL_TIMING_JUST_MIN)
					{
#ifdef _DEBUG
						sprintf(str, "8");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack02);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_JUST_MIN;
					}
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_JUST_MIN && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE_MAX)
					{
#ifdef _DEBUG
						sprintf(str, "9");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_OPPO_MAX;
					}
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE_MAX && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE_MID)
					{
#ifdef _DEBUG
						sprintf(str, "10");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_OPPO_MID;
					}
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE_MID && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE_MIN)
					{
#ifdef _DEBUG
						sprintf(str, "11");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_OPPO_MIN;
					}
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE_MIN && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE_FOUL)
					{
#ifdef _DEBUG
						sprintf(str, "12");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack01);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_OPPO_FOUL;
					}
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE_FOUL && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE_KARABURI)
					{
#ifdef _DEBUG
						sprintf(str, "13");
						SelectText(str);
#endif			
						PlaySound(SOUND_LABEL_SE_attack03);
						b->OorD = false;
						pb->pb.motion = false;
						if (cursor->c.meet % 2 == SMALL) b[0].effect = b[1].effect = b[2].effect = true;
						b->direction = BALL_DIRECTION_OPPO_KARABURI;
					}
				}
			}
			//ボールカーソルとボール(タイミングZ軸)とストライクゾーン BB ok	カウント処理
			if (CollisionBB(bc->pos, TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_Y, TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_X,
				strike->s.pos, TEXTURE_STRIKE_COLLISION_BB_SIZE_Y, TEXTURE_STRIKE_COLLISION_BB_SIZE_X))
			{
				if (b->pos.x <= SCREEN_W - SCREEN_W || b->pos.x >= SCREEN_W ||
					b->pos.y <= SCREEN_H - SCREEN_H || b->pos.y >= SCREEN_H)
				{
					//UpdateGameODloop(GAME_OD_NEXT);
#ifdef _DEBUG
					sprintf(str, "ストライク");
					SelectText(str);
#endif
					LoopInit();
				}
			}
			else
			{
				if (b->pos.x <= SCREEN_W - SCREEN_W || b->pos.x >= SCREEN_W ||
					b->pos.y <= SCREEN_H - SCREEN_H || b->pos.y >= SCREEN_H)
				{
					//UpdateGameODloop(GAME_OD_NEXT);
#ifdef _DEBUG
					sprintf(str, "ボール");
					SelectText(str);
#endif
					LoopInit();
				}
			}
		}
	}
	if (b[0].use == true || b[1].use == true || b[2].use == true)
	{
		//continのほうがいい？
			//打球とエネミーの当たり判定
		if (b[0].OorD == false && b[0].tuto == false)
		{
			if (b[0].diffsignal == true || b[1].use == true || b[2].use == true)
			{
				for (int j = 0; j < BALL_MAX; j++)
				{
					for (int i = 0; i < CAT_GOUKEI; i++)
					{
						if (cat[i].use == true && b[j].use == true && cat[i].effect == false)
						{
							if (CollisionBB(b[j].pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
								cat[i].pos, TEXTURE_CAT_COLLISION_BB_SIZE_Y, TEXTURE_CAT_COLLISION_BB_SIZE_X))
							{
								PlaySound(SOUND_LABEL_SE_damage);
								cat[i].effect = true;
								if (cursor->c.meet % 2 == BIG)
								{
									cat[i].point = 10;
									b[j].use = false;
								}
								else if (cursor->c.meet % 2 == SMALL)
								{
									cat[i].point = 20;
									b[j].penetcount++;
									//be->use = true;
									if (b[j].penetcount >= BALL_COUNT_MAX) b[j].use = false;
								}
							}
							if (b[j].pos.x <= SCREEN_W - SCREEN_W || b[j].pos.x >= SCREEN_W ||
								b[j].pos.y <= SCREEN_H - SCREEN_H || b[j].pos.y >= SCREEN_H) b[j].use = false;
							if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
						}
					}
					for (int i = 0; i < SURAIMU_GOUKEI; i++)
					{
						if (suraimu[i].use == true && b[j].use == true && suraimu[i].effect == false)
						{
							if (CollisionBB(b[j].pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
								suraimu[i].pos, TEXTURE_SURAIMU_COLLISION_BB_SIZE_Y, TEXTURE_SURAIMU_COLLISION_BB_SIZE_X))
							{
								PlaySound(SOUND_LABEL_SE_damage);
								suraimu[i].effect = true;
								if (cursor->c.meet % 2 == BIG)
								{
									suraimu[i].point = 10;
									b[j].use = false;
								}
								else if (cursor->c.meet % 2 == SMALL)
								{
									suraimu[i].point = 20;
									b[j].penetcount++;
									//be->use = true;
									if (b[j].penetcount >= BALL_COUNT_MAX) b[j].use = false;
								}
							}
							if (b[j].pos.x <= SCREEN_W - SCREEN_W || b[j].pos.x >= SCREEN_W ||
								b[j].pos.y <= SCREEN_H - SCREEN_H || b[j].pos.y >= SCREEN_H) b[j].use = false;
							if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
						}
					}
					for (int i = 0; i < HINOTAMA_GOUKEI; i++)
					{
						if (hinotama[i].use == true && b[j].use == true && hinotama[i].effect == false)
						{
							if (CollisionBB(b[j].pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
								hinotama[i].pos, TEXTURE_HINOTAMA_COLLISION_BB_SIZE_Y, TEXTURE_HINOTAMA_COLLISION_BB_SIZE_X))
							{
								PlaySound(SOUND_LABEL_SE_damage);
								hinotama[i].effect = true;
								if (cursor->c.meet % 2 == BIG)
								{
									hinotama[i].point = 10;
									b[j].use = false;
								}
								else if (cursor->c.meet % 2 == SMALL)
								{
									hinotama[i].point = 20;
									b[j].penetcount++;
									//be->use = true;
									if (b[j].penetcount >= BALL_COUNT_MAX) b[j].use = false;
								}
							}
							if (b[j].pos.x <= SCREEN_W - SCREEN_W || b[j].pos.x >= SCREEN_W ||
								b[j].pos.y <= SCREEN_H - SCREEN_H || b[j].pos.y >= SCREEN_H) b[j].use = false;
							if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
						}
					}
					for (int i = 0; i < UFO_GOUKEI; i++)
					{
						if (ufo[i].use == true && b[j].use == true && ufo[i].effect == false)
						{
							if (CollisionBB(b[j].pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
								ufo[i].pos, TEXTURE_UFO_COLLISION_BB_SIZE_Y, TEXTURE_UFO_COLLISION_BB_SIZE_X))
							{
								PlaySound(SOUND_LABEL_SE_damage);
								ufo[i].effect = true;
								if (cursor->c.meet % 2 == BIG)
								{
									ufo[i].point = 10;
									b[j].use = false;
								}
								else if (cursor->c.meet % 2 == SMALL)
								{
									ufo[i].point = 20;
									b[j].penetcount++;
									//be->use = true;
									if (b[j].penetcount >= BALL_COUNT_MAX) b[j].use = false;
								}
							}
							if (b[j].pos.x <= SCREEN_W - SCREEN_W || b[j].pos.x >= SCREEN_W ||
								b[j].pos.y <= SCREEN_H - SCREEN_H || b[j].pos.y >= SCREEN_H) b[j].use = false;
							if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < CAT_GOUKEI; i++)
				{
					if (cat[i].use == true && b[0].use == true && cat[i].effect == false)
					{
						if (CollisionBB(b[0].pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
							cat[i].pos, TEXTURE_CAT_COLLISION_BB_SIZE_Y, TEXTURE_CAT_COLLISION_BB_SIZE_X))
						{
							PlaySound(SOUND_LABEL_SE_damage);
							cat[i].effect = true;
							if (cursor->c.meet % 2 == BIG)
							{
								cat[i].point = 10;
								LoopInit();
							}
							else if (cursor->c.meet % 2 == SMALL)
							{
								cat[i].point = 20;
								b[0].penetcount++;
								be->use = true;
								if (b[0].penetcount >= BALL_COUNT_MAX) LoopInit();
							}
						}
						if (b[0].pos.x <= SCREEN_W - SCREEN_W || b[0].pos.x >= SCREEN_W ||
							b[0].pos.y <= SCREEN_H - SCREEN_H || b[0].pos.y >= SCREEN_H) b[0].use = false;
						if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
					}
				}
				for (int i = 0; i < SURAIMU_GOUKEI; i++)
				{
					if (suraimu[i].use == true && b[0].use == true && suraimu[i].effect == false)
					{
						if (CollisionBB(b->pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
							suraimu[i].pos, TEXTURE_SURAIMU_COLLISION_BB_SIZE_Y, TEXTURE_SURAIMU_COLLISION_BB_SIZE_X))
						{
							PlaySound(SOUND_LABEL_SE_damage);
							suraimu[i].effect = true;
							if (cursor->c.meet % 2 == BIG)
							{
								suraimu[i].point = 10;
								LoopInit();
							}
							else if (cursor->c.meet % 2 == SMALL)
							{
								suraimu[i].point = 20;
								b[0].penetcount++;
								be->use = true;
								if (b[0].penetcount >= BALL_COUNT_MAX) LoopInit();
							}
						}
						if (b[0].pos.x <= SCREEN_W - SCREEN_W || b[0].pos.x >= SCREEN_W ||
							b[0].pos.y <= SCREEN_H - SCREEN_H || b[0].pos.y >= SCREEN_H) b[0].use = false;
						if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
					}
				}
				for (int i = 0; i < HINOTAMA_GOUKEI; i++)
				{
					if (hinotama[i].use == true && b[0].use == true && hinotama[i].effect == false)
					{
						if (CollisionBB(b->pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
							hinotama[i].pos, TEXTURE_HINOTAMA_COLLISION_BB_SIZE_Y, TEXTURE_HINOTAMA_COLLISION_BB_SIZE_X))
						{
							PlaySound(SOUND_LABEL_SE_damage);
							hinotama[i].effect = true;
							if (cursor->c.meet % 2 == BIG)
							{
								hinotama[i].point = 10;
								LoopInit();
							}
							else if (cursor->c.meet % 2 == SMALL)
							{
								hinotama[i].point = 20;
								b[0].penetcount++;
								be->use = true;
								if (b[0].penetcount >= BALL_COUNT_MAX) LoopInit();
							}
						}
						if (b[0].pos.x <= SCREEN_W - SCREEN_W || b[0].pos.x >= SCREEN_W ||
							b[0].pos.y <= SCREEN_H - SCREEN_H || b[0].pos.y >= SCREEN_H) b[0].use = false;
						if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
					}
				}
				for (int i = 0; i < UFO_GOUKEI; i++)
				{
					if (ufo[i].use == true && b[0].use == true && ufo[i].effect == false)
					{
						if (CollisionBB(b->pos, TEXTURE_BALL_COLLISION_BB_SIZE_Y, TEXTURE_BALL_COLLISION_BB_SIZE_X,
							ufo[i].pos, TEXTURE_UFO_COLLISION_BB_SIZE_Y, TEXTURE_UFO_COLLISION_BB_SIZE_X))
						{
							PlaySound(SOUND_LABEL_SE_damage);
							ufo[i].effect = true;
							b[0].diffflag = true;
							if (cursor->c.meet % 2 == BIG)
							{
								LoopInit();
							}
							else if (cursor->c.meet % 2 == SMALL)
							{
								be->use = true;
								b[0].penetcount++;
								if (b[0].penetcount >= BALL_COUNT_MAX) LoopInit();
							}
						}
						if (b[0].pos.x <= SCREEN_W - SCREEN_W || b[0].pos.x >= SCREEN_W ||
							b[0].pos.y <= SCREEN_H - SCREEN_H || b[0].pos.y >= SCREEN_H) b[0].use = false;
						if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
					}
				}
			}
		}
	}
}

//1球ループ後すべて初期化
void LoopInit(void)
{
	PLAYER_PIT *pp = GetPlayerPit();
	PLAYER_BAT *pb = GetPlayerBat();
	BALL *b = GetBall();
	BALLCURSOR *bc = GetBallcursor();
	BALLSHADOW *bs = GetBallshadow();
	CURSOR *cursor = Get_Cursor();
	STRIKE *strike = GetStrike();

	pp->pp.motion = false;
	pb->pb.motion = false;
	pb->pb.fps = 0;
	b->changeVal = 1.0f;
	bs->changeVal = 1.0f;
	b->changeValTypeA = 0;
	b[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	b[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	b[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	b[0].penetcount = 0;
	b[1].penetcount = 0;
	b[2].penetcount = 0;
	b[0].effect = false;
	b[1].effect = false;
	b[2].effect = false;
	b[0].use = false;
	b[1].use = false;
	b[2].use = false;
	b->OorD = true;
	bc->use = false;
	bs->use = false;
	b->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bc->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bs->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	b->oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bc->oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bs->oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor->c.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 250.0f, 0.0f);
	//Sleep(100);
}

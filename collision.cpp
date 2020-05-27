/**
* @file collision.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"
#include "meetstrike.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
#include "collision.h"


//=============================================================================
// �����蔻��BB
//=============================================================================
bool CollisionBB(D3DXVECTOR3 pos1, float h1, float w1, D3DXVECTOR3 pos2, float h2, float w2)
{
	if (pos1.x + w1 >= pos2.x - w2
		&& pos1.x - w1 <= pos2.x + w2
		&& pos1.y + h1 >= pos2.y - h2
		&& pos1.y - h1 <= pos2.y + h2)
	{
		//�������Ă���
		return true;
	}
	//�������Ă��Ȃ�
	return false;
}

//=============================================================================
// �����蔻��BC
//=============================================================================
bool CollisionBC(D3DXVECTOR3 pos1, float r1, D3DXVECTOR3 pos2, float r2)
{
	//��1 �v���C���[�̒��S����G�l�~�[�̒��S�܂ł̋�����player_ballett�ɑ��
	//�v���C���[(player->pos)�ƃo���b�g(enemy->pos)�̋���(���A�܂��́A-)��player_ballet��3����(x,y,z)�Œ�`�i�[���Ă���
	//�u�����v������2�����Ȃ�D3DXVECTOR2���g���B����player->pos��enemy->pos��3�����Œ�`���Ă��邽��D3DXVECTOR3���g����player_ballet��3������`���Ă���
	D3DXVECTOR3 distance_pos = pos1 - pos2;

	//��2 �v���C���[�T�[�N��(�{�f�B)�̔��a
	//player��pos(D3DXVECTOR3�Ȃ̂�3����)��x���W���瓖���蔻��p�e�N�X�`���T�C�Y(�v���C���[���a)�������������l��player_r(�v���C���[���a)�ɑ��
	float wr1 = r1;
	//��2 �G�l�~�[�T�[�N��(�{�f�B)�̔��a
	float wr2 = r2;

	//D3DXVec2LengthSq()�֐���distance_pos(3����)��2�悵�Ă���
	//D3DXVec2Length()�֐�����distance_pos(3����)��2�悵�����̂Ɂ������
	float dista = D3DXVec3LengthSq(&distance_pos);

	float wr3 = (wr1 + wr2)*(wr1 + wr2);

	//�����蔻��
	if (dista <= wr3)
	{
		//�������Ă���
		return true;
	}
	return false;
}

//=============================================================================
//�Փ˔���
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
	char str[256] = { 0 };

	if (b->use == true)
	{
		//�{�[���J�[�\���ƃ{�[��(�^�C�~���OZ��)�ƑŎ� BB ok
		D3DXVECTOR3 pb_dead_pos = pb->pb.pos;//bat�|���S���̒��S���`�悳��Ă�e�N�X�`���̒��S�łȂ����߁A�f�b�h�{�[������p�Ƀe�N�X�`�����S��pos���쐬
		pb_dead_pos.x -= 50;
		if (b->OorD == true)
		{
#ifdef _DEBUG
			if (CollisionBB(b->pos, TEXTURE_BALL_SIZE_Y, TEXTURE_BALL_SIZE_X, pb_dead_pos, TEXTURE_BATTER_COLLISION_BB_SIZE_Y, TEXTURE_BATTER_COLLISION_BB_SIZE_X))
			{
				//�f�b�h�{�[��
				if (b->pos.y >= b->pos.y - 10)
				{
					//AddScore(1);
					//UpdateGameODloop(GAME_OD_NEXT);
					sprintf(str, "�f�b�h�{�[��");
					SelectText(str);
				}
			}
#endif
			//�{�[���J�[�\���ƃ{�[��(�^�C�~���OY��)�ƃ~�[�g�J�[�\�� BC
			float cdeta = 0.0f;
			if (cursor->c.meet % 2 == 0) cdeta = TEXTURE_CURSOR_BIG_COLLISION_BC_SIZE;
			else cdeta = TEXTURE_CURSOR_SMALL_COLLISION_BC_SIZE;
			if (CollisionBC(bc->pos, TEXTURE_BALL_COLLISION_BC_SIZE, cursor->c.pos, cdeta))
			{
				//�ŋ����� �^�C�~���O�̓p�^�[���ƃJ�E���g�Ŕ��肷��
				if (pb->pb.motion == true && b->pos.y >= bc->pos.y - BALL_JUST_TIMING_RED && pb->pb.nPatternAnim >= BAT_PATTERN2 && pb->pb.nPatternAnim <= BAT_PATTERN3)
				{
					if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL1 && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL2)
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
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL2 && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL3)
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
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL3 && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL4)
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
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL4 && b->pos.y <= cursor->c.pos.y - BALL_TIMING_PULL5)
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
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_PULL5 && b->pos.y <= cursor->c.pos.y - BALL_TIMING_JUST1)
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
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_JUST1 && b->pos.y <= cursor->c.pos.y - BALL_TIMING_JUST2)
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
					else if (b->pos.y > cursor->c.pos.y - BALL_TIMING_JUST2 && b->pos.y <= cursor->c.pos.y + BALL_TIMING_JUST2)
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
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_JUST2 && b->pos.y <= cursor->c.pos.y + BALL_TIMING_JUST3)
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
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_JUST3 && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE1)
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
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE1 && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE2)
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
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE2 && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE3)
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
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE3 && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE4)
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
					else if (b->pos.y > cursor->c.pos.y + BALL_TIMING_OPPOSITE4 && b->pos.y <= cursor->c.pos.y + BALL_TIMING_OPPOSITE5)
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
			//�{�[���J�[�\���ƃ{�[��(�^�C�~���OZ��)�ƃX�g���C�N�]�[�� BB ok	�J�E���g����
			if (CollisionBB(bc->pos, TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_Y, TEXTURE_BALLCURSOR_COLLISION_BB_SIZE_X,
				strike->s.pos, TEXTURE_STRIKE_COLLISION_BB_SIZE_Y, TEXTURE_STRIKE_COLLISION_BB_SIZE_X))
			{
				if (b->pos.x <= SCREEN_W - SCREEN_W || b->pos.x >= SCREEN_W ||
					b->pos.y <= SCREEN_H - SCREEN_H || b->pos.y >= SCREEN_H)
				{
					//UpdateGameODloop(GAME_OD_NEXT);
#ifdef _DEBUG
					sprintf(str, "�X�g���C�N");
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
					sprintf(str, "�{�[��");
					SelectText(str);
#endif
					LoopInit();
				}
			}
		}
	}
	if (b[0].use == true || b[1].use == true || b[2].use == true)
	{
		//�ŋ��ƃG�l�~�[�̓����蔻��
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

//=============================================================================
//1�����[�v�シ�ׂď�����
//=============================================================================
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
}

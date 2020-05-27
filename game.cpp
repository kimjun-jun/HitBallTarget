/**
* @file game.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "ball.h"
#include "player.h"
#include "meetstrike.h"
#include "enemy.h"
#include "input.h"
#include "collision.h"
#include "sound.h"
#include "controltype.h"
#include "sensitivity.h"
#include "balleffect.h"
#include "game.h"


//=============================================================================
// �Ō��֐�(update)
//=============================================================================
void Bat(void)
{
	PLAYER_BAT *c = GetPlayerBat();
	CURSOR *cursor = Get_Cursor();
	BALL *b = GetBall();
	DIJOYSTATE2 *analog = IsButtonPressedAnalog();
	int sconkey = GetSCONkeypos();
	float sensitivityVal = float(GetSSENSIkey())/10;//���x�̐��l(0-9)��10�Ŋ���������{���ɂ���
	//�o�b�^�[
	if (c->pb.motion == false)
	{
		c->pb.nCountAnim++;
		if (c->pb.nCountAnim % TIME_BATTER_ANIMATION_SLOW == BAT_PATTERN0)
		{
			// �A�j���p�^�[�����\���^�C�~���O��������A�C�h�����O�^�C�~���O�ɐ؂�ւ�
			c->pb.nPatternAnim = BAT_PATTERN4;
		}
		else if (c->pb.nCountAnim % TIME_BATTER_ANIMATION_SLOW == BAT_PATTERN4)
		{
			// �A�j���p�^�[�����A�C�h�����O�^�C�~���O��������\���^�C�~���O�ɐ؂�ւ�
			c->pb.nPatternAnim = BAT_PATTERN0;
		}
	}
	//////////////////////////////////////////////////////////////�~�[�g�J�[�\���ړ�
	//�L�[�{�[�h
		//������
	if (GetKeyboardPress(DIK_LEFT))
	{
		if (GetKeyboardPress(DIK_DOWN))
		{
			cursor->c.pos.x -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.y += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else if (GetKeyboardPress(DIK_UP))
		{
			cursor->c.pos.x -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.y -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else
		{
			cursor->c.pos.x -= BAT_MOTION_SPEED_MID * sensitivityVal;
		}
	}
	//////////////////////////////////////////////////////////////
		//������
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		if (GetKeyboardPress(DIK_DOWN))
		{
			cursor->c.pos.x += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.y += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else if (GetKeyboardPress(DIK_UP))
		{
			cursor->c.pos.x += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.y -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else
		{
			cursor->c.pos.x += BAT_MOTION_SPEED_MID * sensitivityVal;
		}
	}
	//////////////////////////////////////////////////////////////
			//������
	else if (GetKeyboardPress(DIK_UP))
	{
		if (GetKeyboardPress(DIK_LEFT))
		{
			cursor->c.pos.y -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else if (GetKeyboardPress(DIK_RIGHT))
		{
			cursor->c.pos.y -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else
		{
			cursor->c.pos.y -= BAT_MOTION_SPEED_MID * sensitivityVal;
		}
	}
	//////////////////////////////////////////////////////////////
		//������
	else if (GetKeyboardPress(DIK_DOWN))
	{
		if (GetKeyboardPress(DIK_LEFT))
		{
			cursor->c.pos.y += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else if (GetKeyboardPress(DIK_RIGHT))
		{
			cursor->c.pos.y += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		else
		{
			cursor->c.pos.y += BAT_MOTION_SPEED_MID * sensitivityVal;
		}
	}
	//////////////////////////////////////////////////////////////

	//�Q�[���p�b�h�����΂ߗL��(�f�W�^��)
	//��
	if (sconkey==0)
	{
		if (IsButtonPressedDigital(0, BUTTON_DIGITAL_UP))	cursor->c.pos.y -= BAT_MOTION_SPEED_MID * sensitivityVal;
		//�E
		else if (IsButtonPressedDigital(0, BUTTON_DIGITAL_RIGHT)) cursor->c.pos.x += BAT_MOTION_SPEED_MID * sensitivityVal;
		//��
		else if (IsButtonPressedDigital(0, BUTTON_DIGITAL_DOWN)) cursor->c.pos.y += BAT_MOTION_SPEED_MID * sensitivityVal;
		//��
		else if (IsButtonPressedDigital(0, BUTTON_DIGITAL_LEFT)) cursor->c.pos.x -= BAT_MOTION_SPEED_MID * sensitivityVal;
		//�E��
		else if (IsButtonPressedDigital(0, BUTTON_DIGITAL_RIGHTUP))
		{
			cursor->c.pos.y -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		//�E��
		else if (IsButtonPressedDigital(0, BUTTON_DIGITAL_RIGHTDOWN))
		{
			cursor->c.pos.y += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		//����
		else if (IsButtonPressedDigital(0, BUTTON_DIGITAL_LEFTDOWN))
		{
			cursor->c.pos.y += BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
		//����
		else if (IsButtonPressedDigital(0, BUTTON_DIGITAL_LEFTUP))
		{
			cursor->c.pos.y -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
			cursor->c.pos.x -= BAT_MOTION_ROOT_SPEED_MID * sensitivityVal;
		}
	}
	else if (sconkey == 1)
	{
		//�A�i���O
		if (IsButtonPressedAnalog(0, BUTTON_ANALOG_L_UP) ||
			IsButtonPressedAnalog(0, BUTTON_ANALOG_L_RIGHTUP) ||
			IsButtonPressedAnalog(0, BUTTON_ANALOG_L_RIGHT) ||
			IsButtonPressedAnalog(0, BUTTON_ANALOG_L_RIGHTDOWN) ||
			IsButtonPressedAnalog(0, BUTTON_ANALOG_L_DOWN) ||
			IsButtonPressedAnalog(0, BUTTON_ANALOG_L_LEFTDOWN) ||
			IsButtonPressedAnalog(0, BUTTON_ANALOG_L_LEFT) ||
			IsButtonPressedAnalog(0, BUTTON_ANALOG_L_LEFTUP))
		{
			cursor->c.pos.x = float((analog->lX / 15) + SCREEN_CENTER_X);
			cursor->c.pos.y = float((analog->lY / 15) + SCREEN_CENTER_Y + 250.0f);
		}
		//���ꂪ����ƃA�i���O�����ĂȂ��Ƃ���0�ɖ߂�
		else if (!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_UP) ||
			!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_RIGHTUP) ||
			!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_RIGHT) ||
			!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_RIGHTDOWN) ||
			!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_DOWN) ||
			!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_LEFTDOWN) ||
			!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_LEFT) ||
			!IsButtonPressedAnalog(0, BUTTON_ANALOG_L_LEFTUP))
		{
			cursor->c.pos.x = float((analog->lX / 15) + SCREEN_CENTER_X);
			cursor->c.pos.y = float((analog->lY / 15) + SCREEN_CENTER_Y + 250.0f);
		}
	}
	//cursor�̈ړ��͈͐���
	//x
	if (cursor->c.pos.x > BATCURSOR_MOVE_STOP_X_MAX) cursor->c.pos.x = BATCURSOR_MOVE_STOP_X_MAX;
	else if (cursor->c.pos.x < BATCURSOR_MOVE_STOP_X_MIN) cursor->c.pos.x = BATCURSOR_MOVE_STOP_X_MIN;
	//y
	if (cursor->c.pos.y > BATCURSOR_MOVE_STOP_Y_MAX) cursor->c.pos.y = BATCURSOR_MOVE_STOP_Y_MAX;
	else if (cursor->c.pos.y < BATCURSOR_MOVE_STOP_Y_MIN) cursor->c.pos.y = BATCURSOR_MOVE_STOP_Y_MIN;

	//////////////////////////////////////////////////////////////�X�C���O
		//A�{�^��or�X�y�[�X�L�[����
	if (IsButtonTriggered(0, BUTTON_A) || GetKeyboardTrigger(DIK_B) || c->pb.motion == true)//�g���K�[�g���Ƃ�����
	{
		if (c->pb.motion == false)
		{
			c->pb.nPatternAnim = BAT_PATTERN1;
			c->pb.nCountAnim = 0;
			c->pb.motion = true;
		}
		c->pb.nCountAnim++;
		c->pb.fps++;
		if ((c->pb.nCountAnim % (TIME_BATTER_ANIMATION_FAST)) == 0)//�������]�肪0�Ȃ�if���˓�
		{
			// �p�^�[���̐؂�ւ�
			if(c->pb.nPatternAnim <= BAT_PATTERN3 )c->pb.nPatternAnim++;
			if (b->use == false )
			{
				c->pb.nPatternAnim = BAT_PATTERN0;
				c->pb.motion = false;
			}
			else if (c->pb.fps >= 30 && c->pb.nPatternAnim == BAT_PATTERN4)
			{
				c->pb.nPatternAnim = BAT_PATTERN0;
				c->pb.motion = false;
				c->pb.fps = 0;
			}
		}
	}
	//�ď�����
 	if (c->pb.nCountAnim > 100) c->pb.nCountAnim = 0;

	// �ړ���̍��W�Ńe�N�X�`���ƒ��_��ݒ�
	SetTexturePlayer(c->pb.nPatternAnim, TYPE_BAT);
	SetVertexPlayer(TYPE_BAT);

}

//=============================================================================
// �����֐�(update)
//=============================================================================
void Pit(void)
{
	PLAYER_PIT *c = GetPlayerPit();
	BALL *b = GetBall();

	if (b->OorD == true)
	{
		c->pp.nCountAnim++;
		if (c->pp.nCountAnim % (TIME_PITCHER_ANIMATION) == 0 && b[0].use == false && b[1].use == false && b[2].use == false)
		{
			if (c->pp.motion == false)
			{
				PlaySound(SOUND_LABEL_SE_swing);
				SetBall(c->pp.pos);
				if (b[0].diffsignal == true) b[1].use = b[2].use = true;
			}
			c->pp.motion = true;
			c->pp.nCountAnim++;
		}
	}
	//�ď�����
	if (c->pp.nCountAnim > 10) c->pp.nCountAnim = 0;
	//////////////////////////////////////////////////////////////���W�Z�b�g
	SetTexturePlayer(c->pp.nPatternAnim, TYPE_PIT);		// �e�N�X�`�����W��ݒ�
	SetVertexPlayer(TYPE_PIT);	// �ړ���̍��W�Œ��_��ݒ�
}

//=============================================================================
// �����֐�(update)
//=============================================================================
void Ball(void)
{
	BALL *b = GetBall();
	BALLCURSOR *bc = GetBallcursor();
	BALLSHADOW *bs = GetBallshadow();
	PLAYER_BAT *pb = GetPlayerBat();
	//�����_������
	//���E�Ƀz�[�~���O�Bold�ړ��ʂ��T���Ƃ��āAy����_�ɂȂ����炻��ȍ~��old�ړ��ʂœ�����
	if (b->OorD == true)
	{
		bc->movecount++;
		if (bc->movecount > 100) bc->movecount = 0;
		if (bc->movecount % TIME_BALLCURSOL_MOVECOUNT_MID == 0)
		{
			switch (rand() % 6)
			{
			case DIRECTION_LEFT:
				bc->direction = DIRECTION_LEFT;
				break;
			case DIRECTION_RIGHT:
				bc->direction = DIRECTION_RIGHT;
				break;
			case DIRECTION_UP:
				bc->direction = DIRECTION_UP;
				break;
			case DIRECTION_DOWN:
				bc->direction = DIRECTION_DOWN;
				break;
			default:
				bc->direction = 100;//�ړ����Ȃ�
				break;
			}
		}
		//bc�������_���ŏ㉺���E�Ɉړ�
		if (bc->direction == DIRECTION_LEFT) bc->pos.x -= BALLCURSOR_MOTION_SPEED;
		else if (bc->direction == DIRECTION_RIGHT) bc->pos.x += BALLCURSOR_MOTION_SPEED;
		else if (bc->direction == DIRECTION_UP)
		{
			b->changeValTypeA += BALL_CHENGEVALTYPEA_SIZE;
			b->changeVal += BALL_CHENGEVAL_SIZE;
			bc->pos.y -= BALLCURSOR_MOTION_SPEED;
		}
		else if (bc->direction == DIRECTION_DOWN)
		{
			b->changeValTypeA -= BALL_CHENGEVALTYPEA_SIZE;
			b->changeVal -= BALL_CHENGEVAL_SIZE;
			bc->pos.y += BALLCURSOR_MOTION_SPEED;
		}
		//b��bc�����܂�y���W�オ��
		if (b->pos.y > bc->pos.y)
		{
			b->pos += b->oldmove;
			bs->pos += bs->oldmove;
			b->pos.y += BALL_MOTION_SPEED_FAST;
			bs->pos.y += BALL_MOTION_SPEED_FAST;
		}
		//b��bc�Ƀz�[�~���O����
		else if (b->pos.x + 10 < bc->pos.x || b->pos.x > bc->pos.x + 10)
		{
			D3DXVECTOR3 pos = bc->pos - b->pos;
			float rot = atan2f(pos.y, pos.x);
			b->pos.x += cosf(rot) *  BALL_MOTION_SPEED_FAST;
			b->pos.y += sinf(rot) *  BALL_MOTION_SPEED_FAST;
			bs->pos.x += cosf(rot) *  BALL_MOTION_SPEED_FAST;
			bs->pos.y += sinf(rot) *  BALL_MOTION_SPEED_FAST;
			if (b->pos.y > bc->pos.y - 5)
			{
				b->oldmove.x = cosf(rot) *  BALL_MOTION_SPEED_FAST;
				b->oldmove.y = sinf(rot) *  BALL_MOTION_SPEED_FAST;
				bs->oldmove.x = cosf(rot) *  BALL_MOTION_SPEED_FAST;
				bs->oldmove.y = sinf(rot) *  BALL_MOTION_SPEED_FAST;
			}
		}
		//�z�[�~���O��̌덷���o�Ă������Ŗ������y���グ��
		else
		{
			b->pos.y += BALL_MOTION_SPEED_FAST;
			bs->pos.y += BALL_MOTION_SPEED_FAST;
		}

		//�o�b�e�B���O�\�Ń{�[���J�[�\����ԐF�ɕύX�B������Z���Ŕ��肷�邩Y���Ŕ��肷�邩
		if (b->pos.y >= bc->pos.y - BALL_TIMING_PULL1)
		{
			bc->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			bc->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			bc->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
			bc->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 0, 0, 255);
		}
		else
		{
			bc->vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, 100);
			bc->vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, 100);
			bc->vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, 100);
			bc->vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, 100);
		}
		b[1].pos = b[2].pos = b[0].pos;
		b->changeValTypeA += BALL_CHENGEVALTYPEA_SIZE;
		if (b->changeValTypeA >= BALL_CHENGEVALTYPEA_MIN) b->changeValTypeA -= BALL_CHENGEVALTYPEA_SIZE;
		else if (b->changeValTypeA <= BALL_CHENGEVALTYPEA_MAX) b->changeValTypeA += BALL_CHENGEVALTYPEA_SIZE;
		b->changeVal += BALL_CHENGEVAL_SIZE;
		if (b->changeVal >= BALL_CHENGEVAL_MIN) b->changeVal -= BALL_CHENGEVAL_SIZE;
		else if (b->changeVal <= BALL_CHENGEVAL_MAX) b->changeVal += BALL_CHENGEVAL_SIZE;

	}
}

//=============================================================================
// �ł��ꂽ�ŋ������ł����֐�(update)
//=============================================================================
void Hitball(void)
{
	PLAYER_PIT *pp = GetPlayerPit();
	PLAYER_BAT *pb = GetPlayerBat();
	BALL *b = GetBall();
	BALLCURSOR *bc = GetBallcursor();
	BALLSHADOW *bs = GetBallshadow();
	CURSOR *c = Get_Cursor();
	STRIKE *s = GetStrike();

	for (int i = 0; i < BALL_MAX; i++)
	{
		if (b[0].OorD == false && b[i].use == true)
		{
			//if (b[i].effectcount % 3 == 0) b[i].effectoldpos[b[i].effectcount / 3] = b[i].oldpos;
			//if (b[i].effectcount > 24) b[i].effectcount = 0;
			b[i].oldpos = b[i].pos;
			b[1].direction = b[0].direction - 1;
			b[2].direction = b[0].direction + 1;
			switch (b[i].direction)
			{
			case BALL_DIRECTION_PULL_BUFF:
			{
				b[i].move.x = (BALL_MOTION_SPEED_FAST)*-1;
				b[i].move.y = (BALL_MOTION_SPEED_MID) * -1;
				bs[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_MID) * -1;
				break;
			}
			case BALL_DIRECTION_PULL_KARABURI:
			{
				b[i].move.x = (BALL_MOTION_SPEED_FAST)*-1;
				b[i].move.y = (BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID) * -1;
				bs[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID) * -1;
				break;
			}
			case BALL_DIRECTION_PULL_FOUL:
			{
				b[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				b[i].move.y = (BALL_MOTION_SPEED_FAST - BALL_MOTION_SPEED_MID)* -1;
				bs[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST - BALL_MOTION_SPEED_MID)* -1;
				break;
			}
			case BALL_DIRECTION_PULL_MAX:
			{
				b[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_MID)* -1;
				bs[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_MID) * -1;
				break;
			}
			case BALL_DIRECTION_PULL_MID:
			{
				b[i].move.x = (BALL_MOTION_SPEED_FAST)* -1;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID)* -1;
				bs[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID) * -1;
				break;
			}
			case BALL_DIRECTION_PULL_MIN:
			{
				b[i].move.x = (BALL_MOTION_SPEED_FAST)* -1;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST)* -1;
				bs[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST)* -1;
				break;
			}
			case BALL_DIRECTION_JUST_MAX:
			{
				b[i].move.x = (BALL_MOTION_SPEED_FAST)* -1;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.x = (BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				break;
			}
			case BALL_DIRECTION_JUST:
			{
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST)* -1;
				break;
			}
			case BALL_DIRECTION_JUST_MIN:
			{
				b[i].move.x = BALL_MOTION_SPEED_FAST;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.x = BALL_MOTION_SPEED_FAST;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				break;
			}
			case BALL_DIRECTION_OPPO_MAX:
			{
				b[i].move.x = BALL_MOTION_SPEED_FAST;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.x = BALL_MOTION_SPEED_FAST;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST)* -1;
				break;
			}
			case BALL_DIRECTION_OPPO_MID:
			{
				b[i].move.x = BALL_MOTION_SPEED_FAST;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				bs[i].move.x = BALL_MOTION_SPEED_FAST;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_FAST) * -1;
				break;
			}
			case BALL_DIRECTION_OPPO_MIN:
			{
				b[i].move.x = BALL_MOTION_SPEED_FAST;
				b[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID)* -1;
				bs[i].move.x = BALL_MOTION_SPEED_FAST;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST + BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID) * -1;
				break;
			}
			case BALL_DIRECTION_OPPO_FOUL:
			{
				b[i].move.x = BALL_MOTION_SPEED_FAST;
				b[i].move.y = (BALL_MOTION_SPEED_FAST)* -1;
				bs[i].move.x = BALL_MOTION_SPEED_FAST;
				bs[i].move.y = (BALL_MOTION_SPEED_FAST) * -1;
				break;
			}
			case BALL_DIRECTION_OPPO_KARABURI:
			{
				b[i].move.x = BALL_MOTION_SPEED_FAST;
				b[i].move.y = (BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID) * -1;
				bs[i].move.x = BALL_MOTION_SPEED_FAST;
				bs[i].move.y = (BALL_MOTION_SPEED_MID + BALL_MOTION_SPEED_MID) * -1;
				break;
			}
			case BALL_DIRECTION_OPPO_BUFF:
			{
				b[i].move.x = BALL_MOTION_SPEED_FAST;
				b[i].move.y = (BALL_MOTION_SPEED_MID) * -1;
				bs[i].move.x = BALL_MOTION_SPEED_FAST;
				bs[i].move.y = (BALL_MOTION_SPEED_MID) * -1;
				break;
			}
			default:
				break;
			}
			b[i].pos += b[i].move;
			bs[i].pos += bs[i].move;
			if (b[i].pos.x <= SCREEN_W - SCREEN_W || b[i].pos.x >= SCREEN_W ||
				b[i].pos.y <= SCREEN_H - SCREEN_H || b[i].pos.y >= SCREEN_H) b[i].use = false;
			if (b[0].use == false && b[1].use == false && b[2].use == false) LoopInit();
		}
		b[i].effectcount++;
		SetVertexBall();
		//if (b[i].use == true)
		//{
		//	for (int j = 0; j < BALLEFFECT_NUM_PARTS; j++)
		//	{
		//		SetBalleffect(b[i].effectoldpos[j], 1);
		//	}
		//}
		//SetBalleffect(b[i].oldpos, 1);
	}
}

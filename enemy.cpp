///*******************************************************************************
//* �^�C�g��:		�L���W�����f���Z�c(3)
//* �v���O������:	enemy.cpp
//* �쐬��:			GP11B292 08 �L�����W����
//********************************************************************************/
#include "main.h"
#include "ball.h"
#include "ui.h"
#include "effect.h"
#include "score.h"
#include "select.h"
#include "enemy.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int catmax;
CAT g_cat[CAT_GOUKEI];
SURAIMU g_suraimu[SURAIMU_GOUKEI];
HINOTAMA g_hinotama[HINOTAMA_GOUKEI];
UFO g_ufo[UFO_GOUKEI];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		switch (i)
		{
		case TYPE_CAT:
		{
			for (int j = 0; j < CAT_GOUKEI; j++)
			{
				g_cat[j].pos = D3DXVECTOR3(150.0f + Random(X), 150.0f + Random(Y), 0.0f);
				g_cat[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].point = 0;
				g_cat[j].nPatternAnim = 0;
				g_cat[j].nCountAnim = 0;
				g_cat[j].colori = 255;
				g_cat[j].motion = false;										//�^�A�j�����Ă��� �U�A�j�����Ă��Ȃ�
				g_cat[j].color = false;											//�^�����FA�l���ő�@�U�ő�łȂ�
				g_cat[j].effect = false;										//�^�G�t�F�N�g���Ă���@�U���Ă��Ȃ�
				g_cat[j].chengeval = 0;											//�e�N�X�`���T�C�Y�����W�ʒu�ŕω�������
				g_cat[j].oldchengeval = 0;										//�i���֎~���W�ɍs���Ƃ���ȏ�T�C�Y���ω����Ȃ�
				g_cat[j].use = true;											//�^�g�p���Ă���(�\���`�悷��) �U�g�p���Ă��Ȃ�
				//g_cat[j].use = false;

				// �e�N�X�`���̓ǂݍ���  
				if (type == 0)													// ����̂ݓǂݍ���
				{
					D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�̃|�C���^
						TEXTURE_GAME_CAT1,										// �t�@�C���̖��O
						&g_cat[j].pD3DTexture);								// �ǂݍ��ރ������̃|�C���^
				}
				// ���_���̍쐬
				MakeVertexEnemy(j, i);
			}
			break;
		}
		case TYPE_SURAIMU:
		{
			for (int j = 0; j < SURAIMU_GOUKEI; j++)
			{
				g_suraimu[j].pos = D3DXVECTOR3(200.0f+Random(X), 160.0f + Random(Y), 0.0f);
				g_suraimu[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].colori = 255;
				g_suraimu[j].nCountAnim = 0;
				g_suraimu[j].nPatternAnim = 0;
				g_suraimu[j].point = 0;
				g_suraimu[j].motion = false;									
				g_suraimu[j].color = false;
				g_suraimu[j].use = true;		
				//g_suraimu[j].use = false;
				g_suraimu[j].effect = false;
				g_suraimu[j].chengeval = 0;
				g_suraimu[j].oldchengeval = 0;
				if (type == 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						TEXTURE_GAME_SURAIMU,
						&g_suraimu[j].pD3DTexture);
				}
				MakeVertexEnemy(j, i);
			}
			break;
		}
		case TYPE_HINOTAMA:
		{
			for (int j = 0; j < HINOTAMA_GOUKEI; j++)
			{
				g_hinotama[j].pos = D3DXVECTOR3(200.0f+Random(X), 155.0f + Random(Y), 0.0f);
				g_hinotama[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].colori = 255;
				g_hinotama[j].nCountAnim = 0;
				g_hinotama[j].nPatternAnim = 0;
				g_hinotama[j].point = 0;
				g_hinotama[j].motion = false;
				g_hinotama[j].color = false;
				g_hinotama[j].use = true;		
				//g_hinotama[j].use = false;
				g_hinotama[j].effect = false;
				g_hinotama[j].chengeval = 0;
				g_hinotama[j].oldchengeval = 0;
				if (type == 0)
				{
					D3DXCreateTextureFromFile(pDevice,
							TEXTURE_GAME_HINOTAMA,
							&g_hinotama[j].pD3DTexture);
				}
				MakeVertexEnemy(j, i);
			}
			break;
		}
		case TYPE_UFO:
		{
			for (int j = 0; j < UFO_GOUKEI; j++)
			{
				g_ufo[j].pos = D3DXVECTOR3(250.0f+Random(X), 100.0f + Random(Y), 0.0f);
				g_ufo[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].colori = 255;
				g_ufo[j].nCountAnim = 0;
				g_ufo[j].point = 0;
				g_ufo[j].nPatternAnim = 0;
				g_ufo[j].motion = false;
				g_ufo[j].color = false;
				g_ufo[j].use = true;		
				//g_ufo[j].use = false;
				g_ufo[j].effect = false;
				D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_UFO_SIZE_X, TEXTURE_UFO_SIZE_Y);
				g_ufo[j].rad = D3DXVec2Length(&temp);
				g_ufo[j].angle = atan2f(TEXTURE_UFO_SIZE_Y, TEXTURE_UFO_SIZE_X);
				g_ufo[j].movecount = BALL_MOTION_SPEED_FAST;
				if (type == 0)
				{
					D3DXCreateTextureFromFile(pDevice,
						TEXTURE_GAME_UFO,
						&g_ufo[j].pD3DTexture);
				}
				MakeVertexEnemy(j,i);
			}
			break;
		}
		default:
			break;
		}
	}
	return S_OK;
}

//=============================================================================
// �ď���������
//=============================================================================
void ReInitEnemy(void)
{
	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		switch (i)
		{
		case TYPE_CAT:
		{
			for (int j = 0; j < CAT_GOUKEI; j++)
			{
				g_cat[j].pos = D3DXVECTOR3(150.0f + Random(X), 150.0f + Random(Y), 0.0f);
				g_cat[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_cat[j].point = 0;
				g_cat[j].nPatternAnim = 0;
				g_cat[j].nCountAnim = 0;
				g_cat[j].colori = 255;
				g_cat[j].motion = false;										//�^�A�j�����Ă��� �U�A�j�����Ă��Ȃ�
				g_cat[j].color = false;											//�^�����FA�l���ő�@�U�ő�łȂ�
				g_cat[j].effect = false;										//�^�G�t�F�N�g���Ă���@�U���Ă��Ȃ�
				g_cat[j].chengeval = 0;											//�e�N�X�`���T�C�Y�����W�ʒu�ŕω�������
				g_cat[j].oldchengeval = 0;										//�i���֎~���W�ɍs���Ƃ���ȏ�T�C�Y���ω����Ȃ�
				MakeVertexEnemy(j, i);
				SetTextureEnemy(g_cat[j].nPatternAnim, j, TYPE_CAT);
			}

			SCORE * score = GetScore();
			CAT *catmax = GetCat(0);
			int cat = GetSpos();
			if (cat == L)
			{
				for (int k = 0; k < CAT_GOUKEI; k++, catmax++)
				{
					if (k < CAT_L_LEVEL) catmax->use = true;
					else catmax->use = false;
				}
				score->level = CAT_L_LEVEL;
			}
			else if (cat == M)
			{
				for (int k = 0; k < CAT_GOUKEI; k++, catmax++)
				{
					if (k < CAT_M_LEVEL) catmax->use = true;
					else catmax->use = false;
				}
				score->level = CAT_M_LEVEL;
			}
			else if (cat == H)
			{
				for (int k = 0; k < CAT_GOUKEI; k++, catmax++)
				{
					if (k < CAT_H_LEVEL) catmax->use = true;
					else catmax->use = false;
				}
				score->level = CAT_H_LEVEL;
			}
			break;
		}
		case TYPE_SURAIMU:
		{
			for (int j = 0; j < SURAIMU_GOUKEI; j++)
			{
				g_suraimu[j].pos = D3DXVECTOR3(200.0f + Random(X), 160.0f + Random(Y), 0.0f);
				g_suraimu[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_suraimu[j].colori = 255;
				g_suraimu[j].nCountAnim = 0;
				g_suraimu[j].nPatternAnim = 0;
				g_suraimu[j].point = 0;
				g_suraimu[j].motion = false;
				g_suraimu[j].color = false;
				g_suraimu[j].use = true;
				//g_suraimu[j].use = false;
				g_suraimu[j].effect = false;
				g_suraimu[j].chengeval = 0;
				g_suraimu[j].oldchengeval = 0;
				MakeVertexEnemy(j, i);
				SetTextureEnemy(g_suraimu[j].nPatternAnim, j, TYPE_SURAIMU);
			}
			break;
		}
		case TYPE_HINOTAMA:
		{
			for (int j = 0; j < HINOTAMA_GOUKEI; j++)
			{
				g_hinotama[j].pos = D3DXVECTOR3(200.0f + Random(X), 155.0f + Random(Y), 0.0f);
				g_hinotama[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_hinotama[j].colori = 255;
				g_hinotama[j].nCountAnim = 0;
				g_hinotama[j].nPatternAnim = 0;
				g_hinotama[j].point = 0;
				g_hinotama[j].motion = false;
				g_hinotama[j].color = false;
				g_hinotama[j].use = true;
				//g_hinotama[j].use = false;
				g_hinotama[j].effect = false;
				g_hinotama[j].chengeval = 0;
				g_hinotama[j].oldchengeval = 0;
				MakeVertexEnemy(j, i);
				SetTextureEnemy(g_hinotama[j].nPatternAnim, j, TYPE_HINOTAMA);
			}
			break;
		}
		case TYPE_UFO:
		{
			for (int j = 0; j < UFO_GOUKEI; j++)
			{
				g_ufo[j].pos = D3DXVECTOR3(250.0f + Random(X), 100.0f + Random(Y), 0.0f);
				g_ufo[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].ppos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_ufo[j].colori = 255;
				g_ufo[j].nCountAnim = 0;
				g_ufo[j].point = 0;
				g_ufo[j].nPatternAnim = 0;
				g_ufo[j].motion = false;
				g_ufo[j].color = false;
				g_ufo[j].use = true;
				//g_ufo[j].use = false;
				g_ufo[j].effect = false;
				D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_UFO_SIZE_X, TEXTURE_UFO_SIZE_Y);
				g_ufo[j].rad = D3DXVec2Length(&temp);
				g_ufo[j].angle = atan2f(TEXTURE_UFO_SIZE_Y, TEXTURE_UFO_SIZE_X);
				g_ufo[j].movecount = BALL_MOTION_SPEED_FAST;
				MakeVertexEnemy(j, i);
				SetTextureEnemy(g_ufo[j].nPatternAnim, j, TYPE_UFO);
			}
			break;
		}
		default:
			break;
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < CAT_GOUKEI; i++)
	{
		if (g_cat[i].pD3DTexture != NULL)	// �摜���ǂݍ��܂�Ă�����e�N�X�`����j�����Ă���
		{
			g_cat[i].pD3DTexture->Release();
			g_cat[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < SURAIMU_GOUKEI; i++)
	{
		if (g_suraimu[i].pD3DTexture != NULL)
		{
			g_suraimu[i].pD3DTexture->Release();
			g_suraimu[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < HINOTAMA_GOUKEI; i++)
	{
		if (g_hinotama[i].pD3DTexture != NULL)
		{
			g_hinotama[i].pD3DTexture->Release();
			g_hinotama[i].pD3DTexture = NULL;
		}
	}
	for (int i = 0; i < UFO_GOUKEI; i++)
	{
		if (g_ufo[i].pD3DTexture != NULL)	
		{
			g_ufo[i].pD3DTexture->Release();
			g_ufo[i].pD3DTexture = NULL;
		}
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	for (int i = 0; i < CAT_GOUKEI; i++)
	{
		if (g_cat[i].effect == false&& g_cat[i].use == true)
		{
			//�����������_���ŏ����B�ړ������ɍ��킹�ăe�N�X�`���p�^�[����ύX�B�w��͈͊O�ɍs���Ɩ߂�
			g_cat[i].movecount++;
			if (g_cat[i].movecount > 100) g_cat[i].movecount = 0;
			if (g_cat[i].chengeval > 20.0f) g_cat[i].chengeval = g_cat[i].oldchengeval;
			if (g_cat[i].chengeval < -20.0f) g_cat[i].chengeval = g_cat[i].oldchengeval;
			if (g_cat[i].nCountAnim > 100) g_cat[i].nCountAnim = 0;
			if (g_cat[i].movecount % TIME_CAT_MOVECOUNT_MID == 0)
			{
				switch (rand() % 6)
				{
				case DIRECTION_LEFT:
					g_cat[i].direction = DIRECTION_LEFT;
					break;
				case DIRECTION_RIGHT:
					g_cat[i].direction = DIRECTION_RIGHT;
					break;
				case DIRECTION_UP:
					g_cat[i].direction = DIRECTION_UP;
					break;
				case DIRECTION_DOWN:
					g_cat[i].direction = DIRECTION_DOWN;
					break;
				default:
					g_cat[i].direction = 100;//�ړ����Ȃ�
					break;
				}
			}
			//������
			if (g_cat[i].direction == DIRECTION_LEFT)
			{
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.x -= MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{
					if (g_cat[i].nPatternAnim != ENEMY_PATTERN3 && g_cat[i].nPatternAnim != ENEMY_PATTERN4 && g_cat[i].nPatternAnim != ENEMY_PATTERN5) g_cat[i].nPatternAnim = ENEMY_PATTERN3;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN3) g_cat[i].nPatternAnim = ENEMY_PATTERN4;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN4) g_cat[i].nPatternAnim = ENEMY_PATTERN5;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN5) g_cat[i].nPatternAnim = ENEMY_PATTERN3;

				}
			}
			//�E����
			else if (g_cat[i].direction == DIRECTION_RIGHT)
			{
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.x += MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{
					if (g_cat[i].nPatternAnim != ENEMY_PATTERN6 && g_cat[i].nPatternAnim != ENEMY_PATTERN7 && g_cat[i].nPatternAnim != ENEMY_PATTERN8) g_cat[i].nPatternAnim = ENEMY_PATTERN6;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN6) g_cat[i].nPatternAnim = ENEMY_PATTERN7;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN7) g_cat[i].nPatternAnim = ENEMY_PATTERN8;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN8) g_cat[i].nPatternAnim = ENEMY_PATTERN6;
				}
			}
			//�����
			else if (g_cat[i].direction == DIRECTION_UP)
			{
				g_cat[i].oldchengeval = g_cat[i].chengeval;
				g_cat[i].chengeval -= ENEMY_CHENGEVAL_SIZE;
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.y -= MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{
					if (g_cat[i].nPatternAnim != ENEMY_PATTERN9 && g_cat[i].nPatternAnim != ENEMY_PATTERN10 && g_cat[i].nPatternAnim != ENEMY_PATTERN11) g_cat[i].nPatternAnim = ENEMY_PATTERN9;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN9) g_cat[i].nPatternAnim = ENEMY_PATTERN10;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN10)g_cat[i].nPatternAnim = ENEMY_PATTERN11;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN11)g_cat[i].nPatternAnim = ENEMY_PATTERN9;

				}
			}
			//������
			else if (g_cat[i].direction == DIRECTION_DOWN)
			{
				g_cat[i].oldchengeval = g_cat[i].chengeval;
				g_cat[i].chengeval += ENEMY_CHENGEVAL_SIZE;
				g_cat[i].nCountAnim++;
				g_cat[i].oldpos = g_cat[i].pos;
				g_cat[i].pos.y += MOTION_SPEED_MID;
				if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0)
				{

					if (g_cat[i].nPatternAnim != ENEMY_PATTERN0 && g_cat[i].nPatternAnim != ENEMY_PATTERN1 && g_cat[i].nPatternAnim != ENEMY_PATTERN2) g_cat[i].nPatternAnim = ENEMY_PATTERN0;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN0) g_cat[i].nPatternAnim = ENEMY_PATTERN1;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN1) g_cat[i].nPatternAnim = ENEMY_PATTERN2;
					else if (g_cat[i].nPatternAnim == ENEMY_PATTERN2) g_cat[i].nPatternAnim = ENEMY_PATTERN0;
				}
			}
			//�����ĂȂ��Ă��A�j���͂���
			else
			{
				g_cat[i].nCountAnim++;
			if ((g_cat[i].nCountAnim % (TIME_CAT_ANIMATION_MID)) == 0) g_cat[i].nPatternAnim++;
			}
			//��ʊO�ɍs�����Ƃ�����
			if (g_cat[i].pos.y < BG_SIZE_H_TTOP) g_cat[i].pos.y = g_cat[i].oldpos.y;
			if (g_cat[i].pos.x <= TEXTURE_CAT_SIZE_X || g_cat[i].pos.x >= SCREEN_W- TEXTURE_CAT_SIZE_X)	g_cat[i].pos.x = g_cat[i].oldpos.x;
			else if (g_cat[i].pos.y >= BG_SIZE_H_TOP && g_cat[i].pos.x <= BG_SIZE_W_TOP) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_MID && g_cat[i].pos.x <= BG_SIZE_W_MID) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_UNDER && g_cat[i].pos.x <= BG_SIZE_W_UNDER) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_TOP && g_cat[i].pos.x >= SCREEN_W - BG_SIZE_W_TOP) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_MID && g_cat[i].pos.x >= SCREEN_W - BG_SIZE_W_MID) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_UNDER && g_cat[i].pos.x >= SCREEN_W - BG_SIZE_W_UNDER) g_cat[i].pos = g_cat[i].oldpos;
			else if (g_cat[i].pos.y >= BG_SIZE_H_UUNDER) g_cat[i].pos = g_cat[i].oldpos;
		}
		//���񂾂�G�t�F�N�g������
		else if (g_cat[i].effect == true) DeadEffect(i,TYPE_CAT);
		SetVertexEnemy(i, TYPE_CAT);
		SetTextureEnemy(g_cat[i].nPatternAnim, i, TYPE_CAT);
	}
	for (int i = 0; i < SURAIMU_GOUKEI; i++)
	{
		if (g_suraimu[i].effect == false && g_suraimu[i].use == true)
		{
			//�����������_���ŏ����B�ړ������ɍ��킹�ăe�N�X�`���p�^�[����ύX�B�w��͈͊O�ɍs���Ɩ߂�
			g_suraimu[i].movecount++;
			if (g_suraimu[i].movecount > 100) g_suraimu[i].movecount = 0;
			if (g_suraimu[i].chengeval > 20.0f) g_suraimu[i].chengeval = g_suraimu[i].oldchengeval;
			if (g_suraimu[i].chengeval < -20.0f) g_suraimu[i].chengeval = g_suraimu[i].oldchengeval;
			if (g_suraimu[i].nCountAnim > 100) g_suraimu[i].nCountAnim = 0;
			if (g_suraimu[i].movecount % TIME_SURAIMU_MOVECOUNT_MID == 0)
			{
				switch (rand() % 6)
				{
				case DIRECTION_LEFT:
					g_suraimu[i].direction = DIRECTION_LEFT;
					break;
				case DIRECTION_RIGHT:
					g_suraimu[i].direction = DIRECTION_RIGHT;
					break;
				case DIRECTION_UP:
					g_suraimu[i].direction = DIRECTION_UP;
					break;
				case DIRECTION_DOWN:
					g_suraimu[i].direction = DIRECTION_DOWN;
					break;
				default:
					g_suraimu[i].direction = 100;//�ړ����Ȃ�
					break;
				}
			}
			//������
			if (g_suraimu[i].direction == DIRECTION_LEFT)
			{
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.x -= MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{
					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN3 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN4 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN5) g_suraimu[i].nPatternAnim = ENEMY_PATTERN3;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN3) g_suraimu[i].nPatternAnim = ENEMY_PATTERN4;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN4) g_suraimu[i].nPatternAnim = ENEMY_PATTERN5;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN5) g_suraimu[i].nPatternAnim = ENEMY_PATTERN3;

				}
			}
			//�E����
			else if (g_suraimu[i].direction == DIRECTION_RIGHT)
			{
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.x += MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{
					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN6 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN7 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN8) g_suraimu[i].nPatternAnim = ENEMY_PATTERN6;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN6) g_suraimu[i].nPatternAnim = ENEMY_PATTERN7;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN7) g_suraimu[i].nPatternAnim = ENEMY_PATTERN8;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN8) g_suraimu[i].nPatternAnim = ENEMY_PATTERN6;
				}
			}
			//�����
			else if (g_suraimu[i].direction == DIRECTION_UP)
			{
				g_suraimu[i].oldchengeval = g_suraimu[i].chengeval;
				g_suraimu[i].chengeval -= ENEMY_CHENGEVAL_SIZE;
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.y -= MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{
					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN9 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN10 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN11) g_suraimu[i].nPatternAnim = ENEMY_PATTERN9;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN9) g_suraimu[i].nPatternAnim = ENEMY_PATTERN10;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN10)g_suraimu[i].nPatternAnim = ENEMY_PATTERN11;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN11)g_suraimu[i].nPatternAnim = ENEMY_PATTERN9;

				}
			}
			//������
			else if (g_suraimu[i].direction == DIRECTION_DOWN)
			{
				g_suraimu[i].oldchengeval = g_suraimu[i].chengeval;
				g_suraimu[i].chengeval += ENEMY_CHENGEVAL_SIZE;
				g_suraimu[i].nCountAnim++;
				g_suraimu[i].oldpos = g_suraimu[i].pos;
				g_suraimu[i].pos.y += MOTION_SPEED_MID;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0)
				{

					if (g_suraimu[i].nPatternAnim != ENEMY_PATTERN0 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN1 && g_suraimu[i].nPatternAnim != ENEMY_PATTERN2) g_suraimu[i].nPatternAnim = ENEMY_PATTERN0;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN0) g_suraimu[i].nPatternAnim = ENEMY_PATTERN1;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN1) g_suraimu[i].nPatternAnim = ENEMY_PATTERN2;
					else if (g_suraimu[i].nPatternAnim == ENEMY_PATTERN2) g_suraimu[i].nPatternAnim = ENEMY_PATTERN0;
				}
			}
			//�����ĂȂ��Ă��A�j���͂���
			else
			{
				g_suraimu[i].nCountAnim++;
				if ((g_suraimu[i].nCountAnim % (TIME_SURAIMU_ANIMATION_MID)) == 0) g_suraimu[i].nPatternAnim++;
			}
			//��ʊO�ɍs�����Ƃ�����
			if (g_suraimu[i].pos.y < BG_SIZE_H_TTOP)
			{
				g_suraimu[i].pos.y = g_suraimu[i].oldpos.y;
			}
			if (g_suraimu[i].pos.x <= TEXTURE_CAT_SIZE_X || g_suraimu[i].pos.x >= SCREEN_W - TEXTURE_CAT_SIZE_X)
			{
				g_suraimu[i].pos.x = g_suraimu[i].oldpos.x;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_TOP && g_suraimu[i].pos.x <= BG_SIZE_W_TOP)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_MID && g_suraimu[i].pos.x <= BG_SIZE_W_MID)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_UNDER && g_suraimu[i].pos.x <= BG_SIZE_W_UNDER)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_TOP && g_suraimu[i].pos.x >= SCREEN_W - BG_SIZE_W_TOP)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_MID && g_suraimu[i].pos.x >= SCREEN_W - BG_SIZE_W_MID)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_UNDER && g_suraimu[i].pos.x >= SCREEN_W - BG_SIZE_W_UNDER)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
			else if (g_suraimu[i].pos.y >= BG_SIZE_H_UUNDER)
			{
				g_suraimu[i].pos = g_suraimu[i].oldpos;
			}
		}
			//���񂾂�G�t�F�N�g������
		else if (g_suraimu[i].effect == true ) DeadEffect(i, TYPE_SURAIMU);
		SetVertexEnemy(i, TYPE_SURAIMU);
		SetTextureEnemy(g_suraimu[i].nPatternAnim, i, TYPE_SURAIMU);
	}
	for (int i = 0; i < HINOTAMA_GOUKEI; i++)
	{
		if (g_hinotama[i].effect == false && g_hinotama[i].use == true)
		{
			//�����������_���ŏ����B�ړ������ɍ��킹�ăe�N�X�`���p�^�[����ύX�B�w��͈͊O�ɍs���Ɩ߂�
			g_hinotama[i].movecount++;
			if (g_hinotama[i].chengeval > 20.0f) g_hinotama[i].chengeval = g_hinotama[i].oldchengeval;
			if (g_hinotama[i].chengeval < -20.0f) g_hinotama[i].chengeval = g_hinotama[i].oldchengeval;
			if (g_hinotama[i].movecount > 100) g_hinotama[i].movecount = 0;
			if (g_hinotama[i].nCountAnim > 100) g_hinotama[i].nCountAnim = 0;
			if (g_hinotama[i].movecount % TIME_HINOTAMA_MOVECOUNT_MID == 0)
			{
				switch (rand() % 6)
				{
				case DIRECTION_LEFT:
					g_hinotama[i].direction = DIRECTION_LEFT;
					break;
				case DIRECTION_RIGHT:
					g_hinotama[i].direction = DIRECTION_RIGHT;
					break;
				case DIRECTION_UP:
					g_hinotama[i].direction = DIRECTION_UP;
					break;
				case DIRECTION_DOWN:
					g_hinotama[i].direction = DIRECTION_DOWN;
					break;
				default:
					g_hinotama[i].direction = 100;//�ړ����Ȃ�
					break;
				}
			}
			//������
			if (g_hinotama[i].direction == DIRECTION_LEFT)
			{
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.x -= MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{
					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN3 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN4 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN5) g_hinotama[i].nPatternAnim = ENEMY_PATTERN3;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN3) g_hinotama[i].nPatternAnim = ENEMY_PATTERN4;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN4) g_hinotama[i].nPatternAnim = ENEMY_PATTERN5;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN5) g_hinotama[i].nPatternAnim = ENEMY_PATTERN3;

				}
			}
			//�E����
			else if (g_hinotama[i].direction == DIRECTION_RIGHT)
			{
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.x += MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{
					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN6 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN7 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN8) g_hinotama[i].nPatternAnim = ENEMY_PATTERN6;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN6) g_hinotama[i].nPatternAnim = ENEMY_PATTERN7;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN7) g_hinotama[i].nPatternAnim = ENEMY_PATTERN8;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN8) g_hinotama[i].nPatternAnim = ENEMY_PATTERN6;
				}
			}
			//�����
			else if (g_hinotama[i].direction == DIRECTION_UP)
			{
				g_hinotama[i].oldchengeval = g_hinotama[i].chengeval;
				g_hinotama[i].chengeval -= ENEMY_CHENGEVAL_SIZE;
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.y -= MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{
					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN9 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN10 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN11) g_hinotama[i].nPatternAnim = ENEMY_PATTERN9;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN9) g_hinotama[i].nPatternAnim = ENEMY_PATTERN10;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN10)g_hinotama[i].nPatternAnim = ENEMY_PATTERN11;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN11)g_hinotama[i].nPatternAnim = ENEMY_PATTERN9;

				}
			}
			//������
			else if (g_hinotama[i].direction == DIRECTION_DOWN)
			{
				g_hinotama[i].oldchengeval = g_hinotama[i].chengeval;
				g_hinotama[i].chengeval += ENEMY_CHENGEVAL_SIZE;
				g_hinotama[i].nCountAnim++;
				g_hinotama[i].oldpos = g_hinotama[i].pos;
				g_hinotama[i].pos.y += MOTION_SPEED_MID;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0)
				{

					if (g_hinotama[i].nPatternAnim != ENEMY_PATTERN0 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN1 && g_hinotama[i].nPatternAnim != ENEMY_PATTERN2) g_hinotama[i].nPatternAnim = ENEMY_PATTERN0;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN0) g_hinotama[i].nPatternAnim = ENEMY_PATTERN1;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN1) g_hinotama[i].nPatternAnim = ENEMY_PATTERN2;
					else if (g_hinotama[i].nPatternAnim == ENEMY_PATTERN2) g_hinotama[i].nPatternAnim = ENEMY_PATTERN0;
				}
			}
			//�����ĂȂ��Ă��A�j���͂���
			else
			{
				g_hinotama[i].nCountAnim++;
				if ((g_hinotama[i].nCountAnim % (TIME_HINOTAMA_ANIMATION_MID)) == 0) g_hinotama[i].nPatternAnim++;
			}
			//��ʊO�ɍs�����Ƃ�����
			if (g_hinotama[i].pos.y < BG_SIZE_H_TTOP)
			{
				g_hinotama[i].pos.y = g_hinotama[i].oldpos.y;
			}
			if (g_hinotama[i].pos.x <= TEXTURE_CAT_SIZE_X || g_hinotama[i].pos.x >= SCREEN_W - TEXTURE_CAT_SIZE_X)
			{
				g_hinotama[i].pos.x = g_hinotama[i].oldpos.x;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_TOP && g_hinotama[i].pos.x <= BG_SIZE_W_TOP)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_MID && g_hinotama[i].pos.x <= BG_SIZE_W_MID)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_UNDER && g_hinotama[i].pos.x <= BG_SIZE_W_UNDER)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_TOP && g_hinotama[i].pos.x >= SCREEN_W - BG_SIZE_W_TOP)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_MID && g_hinotama[i].pos.x >= SCREEN_W- BG_SIZE_W_MID)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_UNDER && g_hinotama[i].pos.x >= SCREEN_W - BG_SIZE_W_UNDER)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
			else if (g_hinotama[i].pos.y >= BG_SIZE_H_UUNDER)
			{
				g_hinotama[i].pos = g_hinotama[i].oldpos;
			}
		}
		//���񂾂�G�t�F�N�g������
		else if (g_hinotama[i].effect == true) DeadEffect(i, TYPE_HINOTAMA);
		SetVertexEnemy(i, TYPE_HINOTAMA);
		SetTextureEnemy(g_hinotama[i].nPatternAnim, i, TYPE_HINOTAMA);
	}
	for (int i = 0; i < UFO_GOUKEI; i++)
	{
		if (g_ufo[i].use == true && g_ufo[i].effect == false)
		{
			if (i & 1) g_ufo[i].rot.z += 0.1f;
			else
			{
				D3DXVECTOR3 pos = GetStrike()->s.pos - g_ufo[i].pos;
				g_ufo[i].rot.z = atan2f(pos.y, pos.x) - D3DX_PI / 2;
			}
			g_ufo[i].pos.x += g_ufo[i].movecount;
			if ((g_ufo[i].pos.x < TEXTURE_UFO_SIZE_X) || (g_ufo[i].pos.x > SCREEN_W - TEXTURE_UFO_SIZE_X)) g_ufo[i].movecount *= -1;
		}
		else if (g_ufo[i].effect == true) DeadEffect(i, TYPE_UFO);
		SetVertexEnemy(i, TYPE_UFO);
		SetTextureEnemy(g_ufo[i].nPatternAnim, i, TYPE_UFO);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < CAT_GOUKEI; i++)
	{
		if (g_cat[i].use == true)
		{
				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_2D);
				// �e�N�X�`���̐ݒ�  
				pDevice->SetTexture(0, g_cat[i].pD3DTexture);
				// �|���S���̕`��
				//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, g_cat[i].vertexWk, sizeof(VERTEX_2D));

				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[0], sizeof(VERTEX_2D));
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[4], sizeof(VERTEX_2D));
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[8], sizeof(VERTEX_2D));
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_cat[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
	for (int i = 0; i < SURAIMU_GOUKEI; i++)
	{
		if (g_suraimu[i].use == true)
		{
			pDevice->SetFVF(FVF_VERTEX_2D);
			pDevice->SetTexture(0, g_suraimu[i].pD3DTexture);
			//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, g_suraimu[i].vertexWk, sizeof(VERTEX_2D));

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[0], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[4], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[8], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_suraimu[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
	for (int i = 0; i < HINOTAMA_GOUKEI; i++)
	{
		if (g_hinotama[i].use == true)
		{
			pDevice->SetFVF(FVF_VERTEX_2D);
			pDevice->SetTexture(0, g_hinotama[i].pD3DTexture);
			//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, g_hinotama[i].vertexWk, sizeof(VERTEX_2D));

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[0], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[4], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[8], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_hinotama[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
	for (int i = 0; i < UFO_GOUKEI; i++)
	{
		if (g_ufo[i].use == true)
		{
			pDevice->SetFVF(FVF_VERTEX_2D);
			pDevice->SetTexture(0, g_ufo[i].pD3DTexture);
			//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, g_ufo[i].vertexWk, sizeof(VERTEX_2D));

			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[0], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[4], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[8], sizeof(VERTEX_2D));
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &g_ufo[i].vertexWk[12], sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy(int i, int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (type)
	{
	case TYPE_CAT:
	{
		// rhw�̐ݒ�@���_���d�Ȃ������̕`�揇��
		g_cat[i].vertexWk[0].rhw =
			g_cat[i].vertexWk[1].rhw =
			g_cat[i].vertexWk[2].rhw =
			g_cat[i].vertexWk[3].rhw =
			g_cat[i].vertexWk[4].rhw =
			g_cat[i].vertexWk[5].rhw =
			g_cat[i].vertexWk[6].rhw =
			g_cat[i].vertexWk[7].rhw =
			g_cat[i].vertexWk[8].rhw =
			g_cat[i].vertexWk[9].rhw =
			g_cat[i].vertexWk[10].rhw =
			g_cat[i].vertexWk[11].rhw =
			g_cat[i].vertexWk[12].rhw =
			g_cat[i].vertexWk[13].rhw =
			g_cat[i].vertexWk[14].rhw =
			g_cat[i].vertexWk[15].rhw = 1.0f;
		// ���ˌ��̐ݒ�  ���_�J���[�w�肵���F�ƃe�N�X�`���̐F���������ăJ���[�����O�����
		// �t�F�[�h�C���͎n�߂ɕ\�������e�N�X�`���̏�ɓ����ȃe�N�X�`����\���BRGBA��A�����X�ɕs�����ɂ��Ă���
		g_cat[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[4].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[5].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[6].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[7].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[8].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[9].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[10].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[11].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		g_cat[i].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cat[i].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cat[i].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_cat[i].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		// �e�N�X�`�����W�̐ݒ�  
		g_cat[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_cat[i].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.0f);
		g_cat[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[i].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);

		g_cat[i].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_cat[i].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.0f);
		g_cat[i].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[i].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y);

		g_cat[i].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_cat[i].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f);
		g_cat[i].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[i].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);

		g_cat[i].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_cat[i].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 0.5f);
		g_cat[i].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		g_cat[i].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X, 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y);
		// ���_���W�̐ݒ�
		SetVertexEnemy(i, type);
		break;
	}
	case TYPE_SURAIMU:
	{
		g_suraimu[i].vertexWk[0].rhw =
			g_suraimu[i].vertexWk[1].rhw =
			g_suraimu[i].vertexWk[2].rhw =
			g_suraimu[i].vertexWk[3].rhw =
			g_suraimu[i].vertexWk[4].rhw =
			g_suraimu[i].vertexWk[5].rhw =
			g_suraimu[i].vertexWk[6].rhw =
			g_suraimu[i].vertexWk[7].rhw =
			g_suraimu[i].vertexWk[8].rhw =
			g_suraimu[i].vertexWk[9].rhw =
			g_suraimu[i].vertexWk[10].rhw =
			g_suraimu[i].vertexWk[11].rhw =
			g_suraimu[i].vertexWk[12].rhw =
			g_suraimu[i].vertexWk[13].rhw =
			g_suraimu[i].vertexWk[14].rhw =
			g_suraimu[i].vertexWk[15].rhw = 1.0f;
		g_suraimu[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[4].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[5].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[6].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[7].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[8].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[9].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[10].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[11].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_suraimu[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_suraimu[i].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.0f);
		g_suraimu[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[i].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[i].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_suraimu[i].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.0f);
		g_suraimu[i].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[i].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[i].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_suraimu[i].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f);
		g_suraimu[i].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[i].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[i].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_suraimu[i].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 0.5f);
		g_suraimu[i].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		g_suraimu[i].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X, 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y);
		SetVertexEnemy(i, type);
		break;
	}
	case TYPE_HINOTAMA:
	{
		g_hinotama[i].vertexWk[0].rhw =
			g_hinotama[i].vertexWk[1].rhw =
			g_hinotama[i].vertexWk[2].rhw =
			g_hinotama[i].vertexWk[3].rhw =
			g_hinotama[i].vertexWk[4].rhw =
			g_hinotama[i].vertexWk[5].rhw =
			g_hinotama[i].vertexWk[6].rhw =
			g_hinotama[i].vertexWk[7].rhw =
			g_hinotama[i].vertexWk[8].rhw =
			g_hinotama[i].vertexWk[9].rhw =
			g_hinotama[i].vertexWk[10].rhw =
			g_hinotama[i].vertexWk[11].rhw =
			g_hinotama[i].vertexWk[12].rhw =
			g_hinotama[i].vertexWk[13].rhw =
			g_hinotama[i].vertexWk[14].rhw =
			g_hinotama[i].vertexWk[15].rhw = 1.0f;
		g_hinotama[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[4].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[5].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[6].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[7].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[8].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[9].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[10].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[11].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_hinotama[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_hinotama[i].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.0f);
		g_hinotama[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[i].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[i].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_hinotama[i].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.0f);
		g_hinotama[i].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[i].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[i].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_hinotama[i].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f);
		g_hinotama[i].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[i].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[i].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_hinotama[i].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 0.5f);
		g_hinotama[i].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		g_hinotama[i].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X, 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y);
		SetVertexEnemy(i, type);
		break;
	}
	case TYPE_UFO:
	{
		g_ufo[i].vertexWk[0].rhw =
			g_ufo[i].vertexWk[1].rhw =
			g_ufo[i].vertexWk[2].rhw =
			g_ufo[i].vertexWk[3].rhw =
			g_ufo[i].vertexWk[4].rhw =
			g_ufo[i].vertexWk[5].rhw =
			g_ufo[i].vertexWk[6].rhw =
			g_ufo[i].vertexWk[7].rhw =
			g_ufo[i].vertexWk[8].rhw =
			g_ufo[i].vertexWk[9].rhw =
			g_ufo[i].vertexWk[10].rhw =
			g_ufo[i].vertexWk[11].rhw =
			g_ufo[i].vertexWk[12].rhw =
			g_ufo[i].vertexWk[13].rhw =
			g_ufo[i].vertexWk[14].rhw =
			g_ufo[i].vertexWk[15].rhw = 1.0f;
		g_ufo[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[4].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[5].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[6].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[7].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[8].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[9].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[10].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[11].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[12].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[13].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[14].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[15].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_ufo[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_ufo[i].vertexWk[1].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.0f);
		g_ufo[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[i].vertexWk[3].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[i].vertexWk[4].tex = D3DXVECTOR2(0.5f, 0.0f);
		g_ufo[i].vertexWk[5].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.0f);
		g_ufo[i].vertexWk[6].tex = D3DXVECTOR2(0.5f, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[i].vertexWk[7].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[i].vertexWk[8].tex = D3DXVECTOR2(0.0f, 0.5f);
		g_ufo[i].vertexWk[9].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f);
		g_ufo[i].vertexWk[10].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[i].vertexWk[11].tex = D3DXVECTOR2(0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[i].vertexWk[12].tex = D3DXVECTOR2(0.5f, 0.5f);
		g_ufo[i].vertexWk[13].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 0.5f);
		g_ufo[i].vertexWk[14].tex = D3DXVECTOR2(0.5f, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		g_ufo[i].vertexWk[15].tex = D3DXVECTOR2(1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X, 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y);
		SetVertexEnemy(i, type);
		break;
	}
	default:
		break;
	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy(int cntPattern, int i, int type)
{
	switch (type)
	{
	case TYPE_CAT:
	{
		// �e�N�X�`�����W�̐ݒ�000,122,241,360,482,,,,000,122,244,360,482,5104,,,,,051,13,25
		int x = cntPattern % TEXTURE_CAT_PATTERN_DIVIDE_X;	//x���̃A�j���p�^�[������x�Ƃ���								x�p�^�[����3
		int y = cntPattern / TEXTURE_CAT_PATTERN_DIVIDE_X;	//y���̃A�j���p�^�[������y�Ƃ���								y�p�^�[����4
		float sizeX = 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_X;		//x���̃A�j���p�^�[�����ɉ�����sizeX�Â�x���������				x1�p�^�[�������
		float sizeY = 1.0f / TEXTURE_CAT_PATTERN_DIVIDE_Y;		//y���̃A�j���p�^�[�����ɉ�����sizeY�Â�y���������
		float sizeXofs = 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_X;		//x���̃A�j���p�^�[�����ɉ�����sizeX�Â�x���������				x1�p�^�[�������
		float sizeYofs = 0.5f / TEXTURE_CAT_PATTERN_DIVIDE_Y;		//y���̃A�j���p�^�[�����ɉ�����sizeY�Â�y���������
		/*

		                     1                                    3                                  5                  
		0.0,0.0              0.16             0.3              0.5,0.0            0.66              0.83              1.0,0.0
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll     p1         ll                l
			l       p1       ll       p2       ll                ll      p2        ll                ll     p2         l
			l                ll                ll         p1     ll      2         ll     3          ll                l
			l       1        ll       1        ll       2        ll                ll                ll    3           l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.125		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l       p3       ll     p4         ll        p3      ll      p4        ll                ll      p4        l
			l       1        ll       1        ll                ll                ll        p3      ll                l
			l                ll                ll        2       ll                ll                ll                l
			l                ll                ll                ll       2        ll                ll    3           l
			l                ll                ll                ll                ll      3         ll                l
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l                ll     4          ll      5         ll                ll                ll                l
			l       4        ll                ll                ll                ll           6    ll        6       l
			l                ll                ll                ll  5             ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.375		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l         4      ll                ll                ll                ll                ll        6       l
			l                ll        4       ll        5       ll     5          ll         6      ll                l
			l                ll                ll                ll                ll                ll                l
 0.0,0.5	l                ll                ll                ll                ll                ll                l  1.0,0.5
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll 7              ll                ll                ll                ll                l
			l        7       ll                ll                ll                ll   9            ll       9        l
			l                ll                ll                ll         8      ll                ll                l
			l                ll                ll   8            ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.625		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l                ll      7         ll                ll                ll        9       ll                l
			l        7       ll                ll       8        ll       8        ll                ll       9        l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll 10             ll                ll                ll                ll                l
			l        10      ll                ll                ll                ll   12           ll       12       l
			l                ll                ll                ll         11     ll                ll                l
			l                ll                ll  11            ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
0.875		l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l                ll      10        ll                ll                ll       12       ll                l
			l       10       ll                ll       11       ll      11        ll                ll       12       l
			l                ll                ll                ll                ll                ll                l
			l                ll                ll                ll                ll                ll                l
			l----------------ll----------------ll----------------ll----------------ll----------------ll----------------l

		0.0,1.0													0.5,1.0													1.0,1.0




		*/



		g_cat[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);												//0.0,0.0
		g_cat[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);									//0.5,0.0
		g_cat[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);									//0.0,0.5
		g_cat[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
																															
		g_cat[i].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);									//0.5,0.0
		g_cat[i].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);							//1.0,0.0
		g_cat[i].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
		g_cat[i].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);				//1.0,0.5
																															
		g_cat[i].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);									//0.0,0.5
		g_cat[i].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
		g_cat[i].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);						//0.0,1.0
		g_cat[i].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);				//0.5,1.0
																															
		g_cat[i].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX+ sizeXofs, (float)(y)* sizeY + sizeYofs);							//0.5,0.5
		g_cat[i].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);				//1.0,0.5
		g_cat[i].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);				//0.5,1.0
		g_cat[i].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);	//1.0,1.0
		break;
	}
	case TYPE_SURAIMU:
	{
		int x = cntPattern % TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		int y = cntPattern / TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y;
		float sizeXofs = 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_X;
		float sizeYofs = 0.5f / TEXTURE_SURAIMU_PATTERN_DIVIDE_Y;
		g_suraimu[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_suraimu[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_suraimu[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_suraimu[i].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);
		g_suraimu[i].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_suraimu[i].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_suraimu[i].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_suraimu[i].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_suraimu[i].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		break;
	}
	case TYPE_HINOTAMA:
	{
		int x = cntPattern % TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		int y = cntPattern / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y;
		float sizeXofs = 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_X;
		float sizeYofs = 0.5f / TEXTURE_HINOTAMA_PATTERN_DIVIDE_Y;
		g_hinotama[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_hinotama[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_hinotama[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_hinotama[i].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);
		g_hinotama[i].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_hinotama[i].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_hinotama[i].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_hinotama[i].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_hinotama[i].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		break;
	}
	case TYPE_UFO:
	{
		int x = cntPattern % TEXTURE_UFO_PATTERN_DIVIDE_X;
		int y = cntPattern / TEXTURE_UFO_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / TEXTURE_UFO_PATTERN_DIVIDE_Y;
		float sizeXofs = 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_X;
		float sizeYofs = 0.5f / TEXTURE_UFO_PATTERN_DIVIDE_Y;
		g_ufo[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_ufo[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_ufo[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[4].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY);
		g_ufo[i].vertexWk[5].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY);
		g_ufo[i].vertexWk[6].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[7].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[8].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[9].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[10].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_ufo[i].vertexWk[11].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_ufo[i].vertexWk[12].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[13].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs);
		g_ufo[i].vertexWk[14].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		g_ufo[i].vertexWk[15].tex = D3DXVECTOR2((float)(x)* sizeX + sizeXofs + sizeXofs, (float)(y)* sizeY + sizeYofs + sizeYofs);
		break;
	}
	default:
		break;
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy(int i, int type)
{
	switch (type)
	{
	case TYPE_CAT:
	{
		// ���_���W�̐ݒ� 
		g_cat[i].vertexWk[0].vtx.x = g_cat[i].pos.x - TEXTURE_CAT_SIZE_X - g_cat[i].chengeval - g_cat[i].ppos[0].x;
		g_cat[i].vertexWk[0].vtx.y = g_cat[i].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[i].chengeval - g_cat[i].ppos[0].y;
		g_cat[i].vertexWk[0].vtx.z = 0.0f;
		g_cat[i].vertexWk[1].vtx.x = g_cat[i].pos.x - g_cat[i].ppos[0].x;
		g_cat[i].vertexWk[1].vtx.y = g_cat[i].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[i].chengeval - g_cat[i].ppos[0].y;
		g_cat[i].vertexWk[1].vtx.z = 0.0f;
		g_cat[i].vertexWk[2].vtx.x = g_cat[i].pos.x - TEXTURE_CAT_SIZE_X - g_cat[i].chengeval - g_cat[i].ppos[0].x;
		g_cat[i].vertexWk[2].vtx.y = g_cat[i].pos.y - g_cat[i].ppos[0].y;
		g_cat[i].vertexWk[2].vtx.z = 0.0f;
		g_cat[i].vertexWk[3].vtx.x = g_cat[i].pos.x - g_cat[i].ppos[0].x;
		g_cat[i].vertexWk[3].vtx.y = g_cat[i].pos.y - g_cat[i].ppos[0].y;
		g_cat[i].vertexWk[3].vtx.z = 0.0f;
		g_cat[i].vertexWk[4].vtx.x = g_cat[i].pos.x + g_cat[i].ppos[1].x;
		g_cat[i].vertexWk[4].vtx.y = g_cat[i].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[i].chengeval + g_cat[i].ppos[1].y;
		g_cat[i].vertexWk[4].vtx.z = 0.0f;
		g_cat[i].vertexWk[5].vtx.x = g_cat[i].pos.x + TEXTURE_CAT_SIZE_X + g_cat[i].chengeval + g_cat[i].ppos[1].x;
		g_cat[i].vertexWk[5].vtx.y = g_cat[i].pos.y - TEXTURE_CAT_SIZE_Y - g_cat[i].chengeval + g_cat[i].ppos[1].y;
		g_cat[i].vertexWk[5].vtx.z = 0.0f;
		g_cat[i].vertexWk[6].vtx.x = g_cat[i].pos.x + g_cat[i].ppos[1].x;
		g_cat[i].vertexWk[6].vtx.y = g_cat[i].pos.y + g_cat[i].ppos[1].y;
		g_cat[i].vertexWk[6].vtx.z = 0.0f;
		g_cat[i].vertexWk[7].vtx.x = g_cat[i].pos.x + TEXTURE_CAT_SIZE_X + g_cat[i].chengeval + g_cat[i].ppos[1].x;
		g_cat[i].vertexWk[7].vtx.y = g_cat[i].pos.y + g_cat[i].ppos[1].y;
		g_cat[i].vertexWk[7].vtx.z = 0.0f;
		g_cat[i].vertexWk[8].vtx.x = g_cat[i].pos.x - TEXTURE_CAT_SIZE_X - g_cat[i].chengeval - g_cat[i].ppos[2].x;
		g_cat[i].vertexWk[8].vtx.y = g_cat[i].pos.y - g_cat[i].ppos[2].y;
		g_cat[i].vertexWk[8].vtx.z = 0.0f;
		g_cat[i].vertexWk[9].vtx.x = g_cat[i].pos.x - g_cat[i].ppos[2].x;
		g_cat[i].vertexWk[9].vtx.y = g_cat[i].pos.y - g_cat[i].ppos[2].y;
		g_cat[i].vertexWk[9].vtx.z = 0.0f;
		g_cat[i].vertexWk[10].vtx.x = g_cat[i].pos.x - TEXTURE_CAT_SIZE_X - g_cat[i].chengeval - g_cat[i].ppos[2].x;
		g_cat[i].vertexWk[10].vtx.y = g_cat[i].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[i].chengeval - g_cat[i].ppos[2].y;
		g_cat[i].vertexWk[10].vtx.z = 0.0f;
		g_cat[i].vertexWk[11].vtx.x = g_cat[i].pos.x - g_cat[i].ppos[2].x;
		g_cat[i].vertexWk[11].vtx.y = g_cat[i].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[i].chengeval - g_cat[i].ppos[2].y;
		g_cat[i].vertexWk[11].vtx.z = 0.0f;
		g_cat[i].vertexWk[12].vtx.x = g_cat[i].pos.x + g_cat[i].ppos[3].x;
		g_cat[i].vertexWk[12].vtx.y = g_cat[i].pos.y + g_cat[i].ppos[3].y;
		g_cat[i].vertexWk[12].vtx.z = 0.0f;
		g_cat[i].vertexWk[13].vtx.x = g_cat[i].pos.x + TEXTURE_CAT_SIZE_X + g_cat[i].chengeval + g_cat[i].ppos[3].x;
		g_cat[i].vertexWk[13].vtx.y = g_cat[i].pos.y + g_cat[i].ppos[3].y;
		g_cat[i].vertexWk[13].vtx.z = 0.0f;
		g_cat[i].vertexWk[14].vtx.x = g_cat[i].pos.x + g_cat[i].ppos[3].x;
		g_cat[i].vertexWk[14].vtx.y = g_cat[i].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[i].chengeval + g_cat[i].ppos[3].y;
		g_cat[i].vertexWk[14].vtx.z = 0.0f;
		g_cat[i].vertexWk[15].vtx.x = g_cat[i].pos.x + TEXTURE_CAT_SIZE_X + g_cat[i].chengeval + g_cat[i].ppos[3].x;
		g_cat[i].vertexWk[15].vtx.y = g_cat[i].pos.y + TEXTURE_CAT_SIZE_Y + g_cat[i].chengeval + g_cat[i].ppos[3].y;
		g_cat[i].vertexWk[15].vtx.z = 0.0f;

		break;
	}
	case TYPE_SURAIMU:
	{
		g_suraimu[i].vertexWk[0].vtx.x = g_suraimu[i].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[i].chengeval - g_suraimu[i].ppos[0].x;
		g_suraimu[i].vertexWk[0].vtx.y = g_suraimu[i].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[i].chengeval - g_suraimu[i].ppos[0].y;
		g_suraimu[i].vertexWk[0].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[1].vtx.x = g_suraimu[i].pos.x - g_suraimu[i].ppos[0].x;
		g_suraimu[i].vertexWk[1].vtx.y = g_suraimu[i].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[i].chengeval - g_suraimu[i].ppos[0].y;
		g_suraimu[i].vertexWk[1].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[2].vtx.x = g_suraimu[i].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[i].chengeval - g_suraimu[i].ppos[0].x;
		g_suraimu[i].vertexWk[2].vtx.y = g_suraimu[i].pos.y - g_suraimu[i].ppos[0].y;
		g_suraimu[i].vertexWk[2].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[3].vtx.x = g_suraimu[i].pos.x - g_suraimu[i].ppos[0].x;
		g_suraimu[i].vertexWk[3].vtx.y = g_suraimu[i].pos.y - g_suraimu[i].ppos[0].y;
		g_suraimu[i].vertexWk[3].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[4].vtx.x = g_suraimu[i].pos.x + g_suraimu[i].ppos[1].x;
		g_suraimu[i].vertexWk[4].vtx.y = g_suraimu[i].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[i].chengeval + g_suraimu[i].ppos[1].y;
		g_suraimu[i].vertexWk[4].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[5].vtx.x = g_suraimu[i].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[i].chengeval + g_suraimu[i].ppos[1].x;
		g_suraimu[i].vertexWk[5].vtx.y = g_suraimu[i].pos.y - TEXTURE_SURAIMU_SIZE_Y - g_suraimu[i].chengeval + g_suraimu[i].ppos[1].y;
		g_suraimu[i].vertexWk[5].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[6].vtx.x = g_suraimu[i].pos.x + g_suraimu[i].ppos[1].x;
		g_suraimu[i].vertexWk[6].vtx.y = g_suraimu[i].pos.y + g_suraimu[i].ppos[1].y;
		g_suraimu[i].vertexWk[6].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[7].vtx.x = g_suraimu[i].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[i].chengeval + g_suraimu[i].ppos[1].x;
		g_suraimu[i].vertexWk[7].vtx.y = g_suraimu[i].pos.y + g_suraimu[i].ppos[1].y;
		g_suraimu[i].vertexWk[7].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[8].vtx.x = g_suraimu[i].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[i].chengeval - g_suraimu[i].ppos[2].x;
		g_suraimu[i].vertexWk[8].vtx.y = g_suraimu[i].pos.y - g_suraimu[i].ppos[2].y;
		g_suraimu[i].vertexWk[8].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[9].vtx.x = g_suraimu[i].pos.x - g_suraimu[i].ppos[2].x;
		g_suraimu[i].vertexWk[9].vtx.y = g_suraimu[i].pos.y - g_suraimu[i].ppos[2].y;
		g_suraimu[i].vertexWk[9].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[10].vtx.x = g_suraimu[i].pos.x - TEXTURE_SURAIMU_SIZE_X - g_suraimu[i].chengeval - g_suraimu[i].ppos[2].x;
		g_suraimu[i].vertexWk[10].vtx.y = g_suraimu[i].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[i].chengeval - g_suraimu[i].ppos[2].y;
		g_suraimu[i].vertexWk[10].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[11].vtx.x = g_suraimu[i].pos.x - g_suraimu[i].ppos[2].x;
		g_suraimu[i].vertexWk[11].vtx.y = g_suraimu[i].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[i].chengeval - g_suraimu[i].ppos[2].y;
		g_suraimu[i].vertexWk[11].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[12].vtx.x = g_suraimu[i].pos.x + g_suraimu[i].ppos[3].x;
		g_suraimu[i].vertexWk[12].vtx.y = g_suraimu[i].pos.y + g_suraimu[i].ppos[3].y;
		g_suraimu[i].vertexWk[12].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[13].vtx.x = g_suraimu[i].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[i].chengeval + g_suraimu[i].ppos[3].x;
		g_suraimu[i].vertexWk[13].vtx.y = g_suraimu[i].pos.y + g_suraimu[i].ppos[3].y;
		g_suraimu[i].vertexWk[13].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[14].vtx.x = g_suraimu[i].pos.x + g_suraimu[i].ppos[3].x;
		g_suraimu[i].vertexWk[14].vtx.y = g_suraimu[i].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[i].chengeval + g_suraimu[i].ppos[3].y;
		g_suraimu[i].vertexWk[14].vtx.z = 0.0f;
		g_suraimu[i].vertexWk[15].vtx.x = g_suraimu[i].pos.x + TEXTURE_SURAIMU_SIZE_X + g_suraimu[i].chengeval + g_suraimu[i].ppos[3].x;
		g_suraimu[i].vertexWk[15].vtx.y = g_suraimu[i].pos.y + TEXTURE_SURAIMU_SIZE_Y + g_suraimu[i].chengeval + g_suraimu[i].ppos[3].y;
		g_suraimu[i].vertexWk[15].vtx.z = 0.0f;
		break;
	}
	case TYPE_HINOTAMA:
	{
		g_hinotama[i].vertexWk[0].vtx.x = g_hinotama[i].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[i].chengeval - g_hinotama[i].ppos[0].x;
		g_hinotama[i].vertexWk[0].vtx.y = g_hinotama[i].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[i].chengeval - g_hinotama[i].ppos[0].y;
		g_hinotama[i].vertexWk[0].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[1].vtx.x = g_hinotama[i].pos.x - g_hinotama[i].ppos[0].x;
		g_hinotama[i].vertexWk[1].vtx.y = g_hinotama[i].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[i].chengeval - g_hinotama[i].ppos[0].y;
		g_hinotama[i].vertexWk[1].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[2].vtx.x = g_hinotama[i].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[i].chengeval - g_hinotama[i].ppos[0].x;
		g_hinotama[i].vertexWk[2].vtx.y = g_hinotama[i].pos.y - g_hinotama[i].ppos[0].y;
		g_hinotama[i].vertexWk[2].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[3].vtx.x = g_hinotama[i].pos.x - g_hinotama[i].ppos[0].x;
		g_hinotama[i].vertexWk[3].vtx.y = g_hinotama[i].pos.y - g_hinotama[i].ppos[0].y;
		g_hinotama[i].vertexWk[3].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[4].vtx.x = g_hinotama[i].pos.x + g_hinotama[i].ppos[1].x;
		g_hinotama[i].vertexWk[4].vtx.y = g_hinotama[i].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[i].chengeval + g_hinotama[i].ppos[1].y;
		g_hinotama[i].vertexWk[4].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[5].vtx.x = g_hinotama[i].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[i].chengeval + g_hinotama[i].ppos[1].x;
		g_hinotama[i].vertexWk[5].vtx.y = g_hinotama[i].pos.y - TEXTURE_HINOTAMA_SIZE_Y - g_hinotama[i].chengeval + g_hinotama[i].ppos[1].y;
		g_hinotama[i].vertexWk[5].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[6].vtx.x = g_hinotama[i].pos.x + g_hinotama[i].ppos[1].x;
		g_hinotama[i].vertexWk[6].vtx.y = g_hinotama[i].pos.y + g_hinotama[i].ppos[1].y;
		g_hinotama[i].vertexWk[6].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[7].vtx.x = g_hinotama[i].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[i].chengeval + g_hinotama[i].ppos[1].x;
		g_hinotama[i].vertexWk[7].vtx.y = g_hinotama[i].pos.y + g_hinotama[i].ppos[1].y;
		g_hinotama[i].vertexWk[7].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[8].vtx.x = g_hinotama[i].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[i].chengeval - g_hinotama[i].ppos[2].x;
		g_hinotama[i].vertexWk[8].vtx.y = g_hinotama[i].pos.y - g_hinotama[i].ppos[2].y;
		g_hinotama[i].vertexWk[8].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[9].vtx.x = g_hinotama[i].pos.x - g_hinotama[i].ppos[2].x;
		g_hinotama[i].vertexWk[9].vtx.y = g_hinotama[i].pos.y - g_hinotama[i].ppos[2].y;
		g_hinotama[i].vertexWk[9].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[10].vtx.x = g_hinotama[i].pos.x - TEXTURE_HINOTAMA_SIZE_X - g_hinotama[i].chengeval - g_hinotama[i].ppos[2].x;
		g_hinotama[i].vertexWk[10].vtx.y = g_hinotama[i].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[i].chengeval - g_hinotama[i].ppos[2].y;
		g_hinotama[i].vertexWk[10].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[11].vtx.x = g_hinotama[i].pos.x - g_hinotama[i].ppos[2].x;
		g_hinotama[i].vertexWk[11].vtx.y = g_hinotama[i].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[i].chengeval - g_hinotama[i].ppos[2].y;
		g_hinotama[i].vertexWk[11].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[12].vtx.x = g_hinotama[i].pos.x + g_hinotama[i].ppos[3].x;
		g_hinotama[i].vertexWk[12].vtx.y = g_hinotama[i].pos.y + g_hinotama[i].ppos[3].y;
		g_hinotama[i].vertexWk[12].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[13].vtx.x = g_hinotama[i].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[i].chengeval + g_hinotama[i].ppos[3].x;
		g_hinotama[i].vertexWk[13].vtx.y = g_hinotama[i].pos.y + g_hinotama[i].ppos[3].y;
		g_hinotama[i].vertexWk[13].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[14].vtx.x = g_hinotama[i].pos.x + g_hinotama[i].ppos[3].x;
		g_hinotama[i].vertexWk[14].vtx.y = g_hinotama[i].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[i].chengeval + g_hinotama[i].ppos[3].y;
		g_hinotama[i].vertexWk[14].vtx.z = 0.0f;
		g_hinotama[i].vertexWk[15].vtx.x = g_hinotama[i].pos.x + TEXTURE_HINOTAMA_SIZE_X + g_hinotama[i].chengeval + g_hinotama[i].ppos[3].x;
		g_hinotama[i].vertexWk[15].vtx.y = g_hinotama[i].pos.y + TEXTURE_HINOTAMA_SIZE_Y + g_hinotama[i].chengeval + g_hinotama[i].ppos[3].y;
		g_hinotama[i].vertexWk[15].vtx.z = 0.0f;
		break;
	}
	case TYPE_UFO:
	{
		g_ufo[i].vertexWk[0].vtx.x = g_ufo[i].pos.x - TEXTURE_UFO_SIZE_X  - g_ufo[i].ppos[0].x;
		g_ufo[i].vertexWk[0].vtx.y = g_ufo[i].pos.y - TEXTURE_UFO_SIZE_Y  - g_ufo[i].ppos[0].y;
		g_ufo[i].vertexWk[0].vtx.z = 0.0f;
		g_ufo[i].vertexWk[1].vtx.x = g_ufo[i].pos.x - g_ufo[i].ppos[0].x;
		g_ufo[i].vertexWk[1].vtx.y = g_ufo[i].pos.y - TEXTURE_UFO_SIZE_Y  - g_ufo[i].ppos[0].y;
		g_ufo[i].vertexWk[1].vtx.z = 0.0f;
		g_ufo[i].vertexWk[2].vtx.x = g_ufo[i].pos.x - TEXTURE_UFO_SIZE_X  - g_ufo[i].ppos[0].x;
		g_ufo[i].vertexWk[2].vtx.y = g_ufo[i].pos.y - g_ufo[i].ppos[0].y;
		g_ufo[i].vertexWk[2].vtx.z = 0.0f;
		g_ufo[i].vertexWk[3].vtx.x = g_ufo[i].pos.x - g_ufo[i].ppos[0].x;
		g_ufo[i].vertexWk[3].vtx.y = g_ufo[i].pos.y - g_ufo[i].ppos[0].y;
		g_ufo[i].vertexWk[3].vtx.z = 0.0f;
		g_ufo[i].vertexWk[4].vtx.x = g_ufo[i].pos.x + g_ufo[i].ppos[1].x;
		g_ufo[i].vertexWk[4].vtx.y = g_ufo[i].pos.y - TEXTURE_UFO_SIZE_Y + g_ufo[i].ppos[1].y;
		g_ufo[i].vertexWk[4].vtx.z = 0.0f;
		g_ufo[i].vertexWk[5].vtx.x = g_ufo[i].pos.x + TEXTURE_UFO_SIZE_X + g_ufo[i].ppos[1].x;
		g_ufo[i].vertexWk[5].vtx.y = g_ufo[i].pos.y - TEXTURE_UFO_SIZE_Y + g_ufo[i].ppos[1].y;
		g_ufo[i].vertexWk[5].vtx.z = 0.0f;
		g_ufo[i].vertexWk[6].vtx.x = g_ufo[i].pos.x + g_ufo[i].ppos[1].x;
		g_ufo[i].vertexWk[6].vtx.y = g_ufo[i].pos.y + g_ufo[i].ppos[1].y;
		g_ufo[i].vertexWk[6].vtx.z = 0.0f;
		g_ufo[i].vertexWk[7].vtx.x = g_ufo[i].pos.x + TEXTURE_UFO_SIZE_X + g_ufo[i].ppos[1].x;
		g_ufo[i].vertexWk[7].vtx.y = g_ufo[i].pos.y + g_ufo[i].ppos[1].y;
		g_ufo[i].vertexWk[7].vtx.z = 0.0f;
		g_ufo[i].vertexWk[8].vtx.x = g_ufo[i].pos.x - TEXTURE_UFO_SIZE_X - g_ufo[i].ppos[2].x;
		g_ufo[i].vertexWk[8].vtx.y = g_ufo[i].pos.y - g_ufo[i].ppos[2].y;
		g_ufo[i].vertexWk[8].vtx.z = 0.0f;
		g_ufo[i].vertexWk[9].vtx.x = g_ufo[i].pos.x - g_ufo[i].ppos[2].x;
		g_ufo[i].vertexWk[9].vtx.y = g_ufo[i].pos.y - g_ufo[i].ppos[2].y;
		g_ufo[i].vertexWk[9].vtx.z = 0.0f;
		g_ufo[i].vertexWk[10].vtx.x = g_ufo[i].pos.x - TEXTURE_UFO_SIZE_X - g_ufo[i].ppos[2].x;
		g_ufo[i].vertexWk[10].vtx.y = g_ufo[i].pos.y + TEXTURE_UFO_SIZE_Y - g_ufo[i].ppos[2].y;
		g_ufo[i].vertexWk[10].vtx.z = 0.0f;
		g_ufo[i].vertexWk[11].vtx.x = g_ufo[i].pos.x - g_ufo[i].ppos[2].x;
		g_ufo[i].vertexWk[11].vtx.y = g_ufo[i].pos.y + TEXTURE_UFO_SIZE_Y  - g_ufo[i].ppos[2].y;
		g_ufo[i].vertexWk[11].vtx.z = 0.0f;
		g_ufo[i].vertexWk[12].vtx.x = g_ufo[i].pos.x + g_ufo[i].ppos[3].x;
		g_ufo[i].vertexWk[12].vtx.y = g_ufo[i].pos.y + g_ufo[i].ppos[3].y;
		g_ufo[i].vertexWk[12].vtx.z = 0.0f;
		g_ufo[i].vertexWk[13].vtx.x = g_ufo[i].pos.x + TEXTURE_UFO_SIZE_X  + g_ufo[i].ppos[3].x;
		g_ufo[i].vertexWk[13].vtx.y = g_ufo[i].pos.y + g_ufo[i].ppos[3].y;
		g_ufo[i].vertexWk[13].vtx.z = 0.0f;
		g_ufo[i].vertexWk[14].vtx.x = g_ufo[i].pos.x + g_ufo[i].ppos[3].x;
		g_ufo[i].vertexWk[14].vtx.y = g_ufo[i].pos.y + TEXTURE_UFO_SIZE_Y  + g_ufo[i].ppos[3].y;
		g_ufo[i].vertexWk[14].vtx.z = 0.0f;
		g_ufo[i].vertexWk[15].vtx.x = g_ufo[i].pos.x + TEXTURE_UFO_SIZE_X  + g_ufo[i].ppos[3].x;
		g_ufo[i].vertexWk[15].vtx.y = g_ufo[i].pos.y + TEXTURE_UFO_SIZE_Y  + g_ufo[i].ppos[3].y;
		g_ufo[i].vertexWk[15].vtx.z = 0.0f;
		break;
	}
	default :
		break;
	}
}

//=============================================================================
// �e�G�l�~�[�̃A�h���X��Ԃ�
//=============================================================================
CAT *GetCat(int i)
{
	return &g_cat[i];
}
SURAIMU *GetSuraimu(int i)
{
	return &g_suraimu[i];
}
HINOTAMA *GetHinotama(int i)
{
	return &g_hinotama[i];
}
UFO *GetUfo(int i)
{
	return &g_ufo[i];
}

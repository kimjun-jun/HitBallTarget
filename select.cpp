/**
* @file select.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "ball.h"
#include "score.h"
#include "select.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
/**
* @brief ���_�����֐� MakeVertexSelect
* @return HRESULT
*/
HRESULT MakeVertexSelect(void);

/**
* @brief �e�N�X�`���ݒ�֐� SetTextureSelect
*/
void SetTextureSelect(void);

/**
* @brief ���_�ݒ�֐� SetVertexSelect
*/
void SetVertexSelect(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
SELECT g_select[SMAX];					//!< 0�C�[�W�[,1�m�[�}��,2�n�[�h,3���x��,4�G���^�[	�\���̕ϐ�
static int spos;						//!< �Z���N�g�J�[�\����pos
static int cat;							//!< ��Փx���Ƃ̃l�R�̐�
//=============================================================================
// ����������
//=============================================================================
HRESULT InitSelect(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_EASY,										// �t�@�C���̖��O
			&g_select[0].pD3DTexture);							// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_NORMAL,
			&g_select[1].pD3DTexture);

		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_HARD,
			&g_select[2].pD3DTexture);

		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_LEVEL,
			&g_select[3].pD3DTexture);

		D3DXCreateTextureFromFile(pDevice,
			TEXTURE_ENTER,
			&g_select[4].pD3DTexture);
	}

		g_select[0].pos = D3DXVECTOR3(EASY_POS_X,EASY_POS_Y, 0.0f);
		g_select[1].pos = D3DXVECTOR3(EASY_POS_X,NORMAL_POS_Y, 0.0f);
		g_select[2].pos = D3DXVECTOR3(EASY_POS_X,HRAD_POS_Y, 0.0f);
		g_select[3].pos = D3DXVECTOR3(LEVEL_POS_X, LEVEL_POS_Y, 0.0f);
		g_select[4].pos = D3DXVECTOR3(ENTERorSTART_POS_X, ENTERorSTART_POS_Y, 0.0f);
		spos = 0;
	// ���_���̍쐬
	MakeVertexSelect();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSelect(void)
{
	for (int i = 0; i < SMAX; i++)
	{
		if (g_select[i].pD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_select[i].pD3DTexture->Release();
			g_select[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelect(void)
{
	MasterVolumeChange(1);
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_B))
	{// Enter��������A�X�e�[�W��؂�ւ���
		PlaySound(SOUND_LABEL_SE_strat);
		//�`���[�g���A���Ŏg�������̂�������
		ReInitTuto();
		//�`���[�g���A���I�����ball��tuto���[�h��؂�ւ���
		BALL *b = GetBall();
		for (int i = 0; i < BALL_MAX; i++, b++)	b->tuto = false;
		//��Փx�ɂ���ăl�R�̐���ύX
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
		SetFade(FADE_OUT, SCENE_GAMECOUNTDOWN, SOUND_LABEL_BGM_normal01);
	}
	else if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_DIGITAL_UP) || IsButtonTriggered(0, BUTTON_ANALOG_L_UP))
	{
		spos--;
		PlaySound(SOUND_LABEL_SE_enter03);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DIGITAL_DOWN) || IsButtonTriggered(0, BUTTON_ANALOG_L_DOWN))
	{
		spos++;
		PlaySound(SOUND_LABEL_SE_enter03);
	}
	if (spos > H) spos = L;
	else if (spos < L) spos = H;
	SetVertexSelect();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < SMAX; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_select[i].pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_select[i].vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSelect(void)
{
	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_select[0].vertexWk[0].rhw =
		g_select[0].vertexWk[1].rhw =
		g_select[0].vertexWk[2].rhw =
		g_select[0].vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_select[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_select[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_select[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_select[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_select[1].vertexWk[0].rhw =
		g_select[1].vertexWk[1].rhw =
		g_select[1].vertexWk[2].rhw =
		g_select[1].vertexWk[3].rhw = 1.0f;
	g_select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_select[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_select[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_select[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	g_select[2].vertexWk[0].rhw =
		g_select[2].vertexWk[1].rhw =
		g_select[2].vertexWk[2].rhw =
		g_select[2].vertexWk[3].rhw = 1.0f;
	g_select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[2].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_select[2].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_select[2].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_select[2].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_select[3].vertexWk[0].rhw =
		g_select[3].vertexWk[1].rhw =
		g_select[3].vertexWk[2].rhw =
		g_select[3].vertexWk[3].rhw = 1.0f;
	g_select[3].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[3].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[3].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[3].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[3].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_select[3].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_select[3].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_select[3].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_select[4].vertexWk[0].rhw =
	g_select[4].vertexWk[1].rhw =
	g_select[4].vertexWk[2].rhw =
	g_select[4].vertexWk[3].rhw = 1.0f;
	g_select[4].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[4].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[4].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[4].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_select[4].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_select[4].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_select[4].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_select[4].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureSelect(void)
{
		g_select[0].vertexWk[0].tex = D3DXVECTOR2(0.0f,0.0f);
		g_select[0].vertexWk[1].tex = D3DXVECTOR2(1.0f,0.0f);
		g_select[0].vertexWk[2].tex = D3DXVECTOR2(0.0f,1.0f);
		g_select[0].vertexWk[3].tex = D3DXVECTOR2(1.0f,1.0f);

		g_select[1].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_select[1].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_select[1].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_select[1].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_select[2].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_select[2].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_select[2].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_select[2].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_select[3].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_select[3].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_select[3].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_select[3].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_select[4].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_select[4].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_select[4].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_select[4].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);


}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSelect(void)
{
		// ���_���W�̐ݒ� 
	for (int i = 0; i < SMAX; i++)
	{
		g_select[i].vertexWk[0].vtx.x = g_select[i].pos.x - TEXTURE_EASY_SIZE_X;
		g_select[i].vertexWk[0].vtx.y = g_select[i].pos.y - TEXTURE_EASY_SIZE_Y;
		g_select[i].vertexWk[0].vtx.z = 0.0f;
		g_select[i].vertexWk[1].vtx.x = g_select[i].pos.x + TEXTURE_EASY_SIZE_X;
		g_select[i].vertexWk[1].vtx.y = g_select[i].pos.y - TEXTURE_EASY_SIZE_Y;
		g_select[i].vertexWk[1].vtx.z = 0.0f;
		g_select[i].vertexWk[2].vtx.x = g_select[i].pos.x - TEXTURE_EASY_SIZE_X;
		g_select[i].vertexWk[2].vtx.y = g_select[i].pos.y + TEXTURE_EASY_SIZE_Y;
		g_select[i].vertexWk[2].vtx.z = 0.0f;
		g_select[i].vertexWk[3].vtx.x = g_select[i].pos.x + TEXTURE_EASY_SIZE_X;
		g_select[i].vertexWk[3].vtx.y = g_select[i].pos.y + TEXTURE_EASY_SIZE_Y;
		g_select[i].vertexWk[3].vtx.z = 0.0f;
	}

	g_select[4].vertexWk[0].vtx.x = g_select[4].pos.x - TEXTURE_ENTER_SIZE_X;
	g_select[4].vertexWk[0].vtx.y = g_select[4].pos.y - TEXTURE_ENTER_SIZE_Y;
	g_select[4].vertexWk[0].vtx.z = 0.0f;						
	g_select[4].vertexWk[1].vtx.x = g_select[4].pos.x + TEXTURE_ENTER_SIZE_X;
	g_select[4].vertexWk[1].vtx.y = g_select[4].pos.y - TEXTURE_ENTER_SIZE_Y;
	g_select[4].vertexWk[1].vtx.z = 0.0f;						
	g_select[4].vertexWk[2].vtx.x = g_select[4].pos.x - TEXTURE_ENTER_SIZE_X;
	g_select[4].vertexWk[2].vtx.y = g_select[4].pos.y + TEXTURE_ENTER_SIZE_Y;
	g_select[4].vertexWk[2].vtx.z = 0.0f;						
	g_select[4].vertexWk[3].vtx.x = g_select[4].pos.x + TEXTURE_ENTER_SIZE_X;
	g_select[4].vertexWk[3].vtx.y = g_select[4].pos.y + TEXTURE_ENTER_SIZE_Y;
	g_select[4].vertexWk[3].vtx.z = 0.0f;

		if (spos==L)
		{
			g_select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

			g_select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

			g_select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		}
		else if (spos == M )
		{
			g_select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

			g_select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

			g_select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
		}
		else if(spos== H)
		{
			g_select[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

			g_select[1].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[1].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[1].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);
			g_select[1].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 50);

			g_select[2].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[2].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[2].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_select[2].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
}

//=============================================================================
// �Z���N�g���Ă����Փx(�l�R�̐�)���擾
//=============================================================================
int GetSpos(void)
{
	return spos;
}


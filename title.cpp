/**
* @file title.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include"sound.h"
#include "title.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TITLE g_title[TITLE_GOUKEI];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (type == 0)
	{
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_TITLE_LOGO,			// �t�@�C���̖��O
			&g_title[0].pD3DTexture);	// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	for (int i = 0; i < TITLE_GOUKEI; i++)
	{
		if (g_title[i].pD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_title[i].pD3DTexture->Release();
			g_title[i].pD3DTexture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	MasterVolumeChange(1);
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_B))
	{// Enter��������A�X�e�[�W��؂�ւ���
		PlaySound(SOUND_LABEL_SE_enter01);
		SetFade(FADE_OUT, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial01);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < TITLE_GOUKEI; i++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_title[i].pD3DTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_title[i].vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	g_title[0].vertexWk[0].vtx = D3DXVECTOR3(TITLELOGO_POS_X - TITLELOGO_SIZE_X, TITLELOGO_POS_Y - TITLELOGO_SIZE_Y, 0.0f);
	g_title[0].vertexWk[1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y - TITLELOGO_SIZE_Y, 0.0f);
	g_title[0].vertexWk[2].vtx = D3DXVECTOR3(TITLELOGO_POS_X - TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	g_title[0].vertexWk[3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + TITLELOGO_SIZE_Y, 0.0f);
	g_title[0].vertexWk[0].rhw =
	g_title[0].vertexWk[1].rhw =
	g_title[0].vertexWk[2].rhw =
	g_title[0].vertexWk[3].rhw = 1.0f;
	g_title[0].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_title[0].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_title[0].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_title[0].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_title[0].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_title[0].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_title[0].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_title[0].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}


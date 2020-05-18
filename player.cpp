/**
* @file player.cpp
* @brief HitBallTarget(2D)�I���ăQ�[��
* @author �L�����W����
* @date 2019/09/01
*/
#include "main.h"
#include "game.h"
#include "player.h"

#ifdef _DEBUG
#include "input.h"
#include "fade.h"
#include "sound.h"
#endif



//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER_PIT g_player_pit;
PLAYER_BAT g_player_bat;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < PLAYER_GOUKEI; i++)
	{
		switch (i)
		{
			//�s�b�`���[������
		case TYPE_PIT:
			g_player_pit.pp.pos = D3DXVECTOR3(SCREEN_CENTER_X, 200.0f, 0.0f);
			g_player_pit.pp.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_pit.pp.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_pit.pp.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_pit.pp.direction = 0;
			g_player_pit.pp.fps = 0;
			g_player_pit.pp.nCountAnim = 0;
			g_player_pit.pp.nPatternAnim = 0;
			g_player_pit.pp.motion = false;											//�^�A�j�����Ă��� �U�A�j�����Ă��Ȃ�
			g_player_pit.pp.use = true;											//�^�g�p���Ă���(�\���`�悷��) �U�g�p���Ă��Ȃ�

			// �e�N�X�`���̓ǂݍ���  
			if (type == 0)	// ����̂ݓǂݍ���
			{
				D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�̃|�C���^
					TEXTURE_GAME_PITCHER,				// �t�@�C���̖��O
					&g_player_pit.pp.pD3DTexture);				// �ǂݍ��ރ������̃|�C���^
			}
			// ���_���̍쐬
			MakeVertexPlayer(i);
			break;

			//�Ŏ҂̏�����
		case TYPE_BAT:
			g_player_bat.pb.pos = D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, SCREEN_CENTER_Y + 300.0f, 0.0f);
			g_player_bat.pb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_bat.pb.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_bat.pb.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player_bat.pb.direction = 0;
			g_player_bat.pb.fps = 0;
			g_player_bat.pb.nCountAnim = 0;
			g_player_bat.pb.nPatternAnim = 0;
			g_player_bat.pb.motion = false;									//�^�X�C���O���Ă��� �U�X�C���O���Ă��Ȃ�
			g_player_bat.pb.use = true;											//�^�g�p���Ă���(�\���`�悷��) �U�g�p���Ă��Ȃ�

			// �e�N�X�`���̓ǂݍ���  
			if (type == 0)	// ����̂ݓǂݍ���
			{
				D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�̃|�C���^
					TEXTURE_GAME_BATTER,				// �t�@�C���̖��O
					&g_player_bat.pb.pD3DTexture);			// �ǂݍ��ރ������̃|�C���^
			}
			// ���_���̍쐬
			MakeVertexPlayer(i);
			break;
		}
	}
	return S_OK;
}

//=============================================================================
// �ď���������
//=============================================================================
void ReInitPlayer(void)
{
	g_player_pit.pp.pos = D3DXVECTOR3(SCREEN_CENTER_X, 200.0f, 0.0f);
	g_player_pit.pp.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	g_player_pit.pp.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	g_player_pit.pp.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	g_player_pit.pp.nCountAnim = 0;		
	g_player_pit.pp.fps= 0;
	g_player_pit.pp.nPatternAnim = 0;								
	g_player_pit.pp.motion = false;									
	g_player_pit.pp.use = false;									

	g_player_bat.pb.pos = D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, SCREEN_CENTER_Y + 300.0f, 0.0f);
	g_player_bat.pb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player_bat.pb.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	g_player_bat.pb.oldmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	g_player_bat.pb.direction = 0;
	g_player_bat.pb.fps = 0;
	g_player_bat.pb.nCountAnim = 0;									
	g_player_bat.pb.nPatternAnim = 0;								
	g_player_bat.pb.motion = false;									
	g_player_bat.pb.use = true;										
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	//pit�j��
	if (g_player_pit.pp.pD3DTexture != NULL)	// �摜���ǂݍ��܂�Ă�����e�N�X�`����j�����Ă���
	{	// �e�N�X�`���̊J��
		g_player_pit.pp.pD3DTexture->Release();
		g_player_pit.pp.pD3DTexture = NULL;
	}

	//bat�j��
	if (g_player_bat.pb.pD3DTexture != NULL)	// �摜���ǂݍ��܂�Ă�����e�N�X�`����j�����Ă���
	{	// �e�N�X�`���̊J��
		g_player_bat.pb.pD3DTexture->Release();
		g_player_bat.pb.pD3DTexture = NULL;
	}

}


//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	Bat();
	Pit();

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_5)) SetFade(FADE_OUT, SCENE_RESULT_FIELD, SOUND_LABEL_BGM_gameover01);
	if (GetKeyboardPress(DIK_6)) SetFade(FADE_OUT, SCENE_RESULT_CLEAR, SOUND_LABEL_BGM_gameclear01);
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�o�b�^�[�\��
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�  
	pDevice->SetTexture(0, g_player_bat.pb.pD3DTexture);
	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_player_bat.pb.vertexWk, sizeof(VERTEX_2D));

	//�s�b�`���[�\��
	pDevice->SetTexture(0, g_player_pit.pp.pD3DTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_player_pit.pp.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	switch (i)
	{
	case TYPE_PIT:
	{
		// ���_���W�̐ݒ�
		SetVertexPlayer(i);

		// rhw�̐ݒ�@���_���d�Ȃ������̕`�揇��
		g_player_pit.pp.vertexWk[0].rhw =
			g_player_pit.pp.vertexWk[1].rhw =
			g_player_pit.pp.vertexWk[2].rhw =
			g_player_pit.pp.vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�  ���_�J���[�w�肵���F�ƃe�N�X�`���̐F���������ăJ���[�����O�����
		// �t�F�[�h�C���͎n�߂ɕ\�������e�N�X�`���̏�ɓ����ȃe�N�X�`����\���BRGBA��A�����X�ɕs�����ɂ��Ă���
		g_player_pit.pp.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_pit.pp.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_pit.pp.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_pit.pp.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�  
		g_player_pit.pp.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_player_pit.pp.vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_X, 0.0f);
		g_player_pit.pp.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_Y);
		g_player_pit.pp.vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_X, 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_Y);
		break;
	}
	case TYPE_BAT:
	{
		// ���_���W�̐ݒ�
		SetVertexPlayer(i);

		// rhw�̐ݒ�@���_���d�Ȃ������̕`�揇��
		g_player_bat.pb.vertexWk[0].rhw =
			g_player_bat.pb.vertexWk[1].rhw =
			g_player_bat.pb.vertexWk[2].rhw =
			g_player_bat.pb.vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�  ���_�J���[�w�肵���F�ƃe�N�X�`���̐F���������ăJ���[�����O�����
		// �t�F�[�h�C���͎n�߂ɕ\�������e�N�X�`���̏�ɓ����ȃe�N�X�`����\���BRGBA��A�����X�ɕs�����ɂ��Ă���
		g_player_bat.pb.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_bat.pb.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_bat.pb.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_player_bat.pb.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�  
		g_player_bat.pb.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_player_bat.pb.vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_X, 0.0f);
		g_player_bat.pb.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_Y);
		g_player_bat.pb.vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_X, 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_Y);
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
void SetTexturePlayer(int cntPattern, int i)
{
	switch (i)
	{
	case TYPE_PIT:
	{
		// �e�N�X�`�����W�̐ݒ�
		int x_pit = cntPattern % TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		int y_pit = cntPattern / TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		float sizeX_pit = 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_X;
		float sizeY_pit = 1.0f / TEXTURE_PITCHER_PATTERN_DIVIDE_Y;

		g_player_pit.pp.vertexWk[0].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit, (float)(y_pit)* sizeY_pit);
		g_player_pit.pp.vertexWk[1].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit + sizeX_pit, (float)(y_pit)* sizeY_pit);
		g_player_pit.pp.vertexWk[2].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit, (float)(y_pit)* sizeY_pit + sizeY_pit);
		g_player_pit.pp.vertexWk[3].tex = D3DXVECTOR2((float)(x_pit)* sizeX_pit + sizeX_pit, (float)(y_pit)* sizeY_pit + sizeY_pit);
		break;
	}
	case TYPE_BAT:
	{
		// �e�N�X�`�����W�̐ݒ�
		int x_bat = cntPattern % TEXTURE_BATTER_PATTERN_DIVIDE_X;
		int y_bat = cntPattern / TEXTURE_BATTER_PATTERN_DIVIDE_X;
		float sizeX_bat = 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_X;
		float sizeY_bat = 1.0f / TEXTURE_BATTER_PATTERN_DIVIDE_Y;

		g_player_bat.pb.vertexWk[0].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat, (float)(y_bat)* sizeY_bat);
		g_player_bat.pb.vertexWk[1].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat + sizeX_bat, (float)(y_bat)* sizeY_bat);
		g_player_bat.pb.vertexWk[2].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat, (float)(y_bat)* sizeY_bat + sizeY_bat);
		g_player_bat.pb.vertexWk[3].tex = D3DXVECTOR2((float)(x_bat)* sizeX_bat + sizeX_bat, (float)(y_bat)* sizeY_bat + sizeY_bat);
		break;
	}
	default:
		break;
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(int i)
{
	switch (i)
	{
	case TYPE_PIT:
	{
		// ���_���W�̐ݒ� 
		g_player_pit.pp.vertexWk[0].vtx.x = g_player_pit.pp.pos.x - TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[0].vtx.y = g_player_pit.pp.pos.y - TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[0].vtx.z = 0.0f;

		g_player_pit.pp.vertexWk[1].vtx.x = g_player_pit.pp.pos.x + TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[1].vtx.y = g_player_pit.pp.pos.y - TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[1].vtx.z = 0.0f;

		g_player_pit.pp.vertexWk[2].vtx.x = g_player_pit.pp.pos.x - TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[2].vtx.y = g_player_pit.pp.pos.y + TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[2].vtx.z = 0.0f;

		g_player_pit.pp.vertexWk[3].vtx.x = g_player_pit.pp.pos.x + TEXTURE_PITCHER_SIZE_X;
		g_player_pit.pp.vertexWk[3].vtx.y = g_player_pit.pp.pos.y + TEXTURE_PITCHER_SIZE_Y;
		g_player_pit.pp.vertexWk[3].vtx.z = 0.0f;
		break;
	}
	case TYPE_BAT:
	{
		// ���_���W�̐ݒ� 
		g_player_bat.pb.vertexWk[0].vtx.x = g_player_bat.pb.pos.x - TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[0].vtx.y = g_player_bat.pb.pos.y - TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[0].vtx.z = 0.0f;

		g_player_bat.pb.vertexWk[1].vtx.x = g_player_bat.pb.pos.x + TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[1].vtx.y = g_player_bat.pb.pos.y - TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[1].vtx.z = 0.0f;

		g_player_bat.pb.vertexWk[2].vtx.x = g_player_bat.pb.pos.x - TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[2].vtx.y = g_player_bat.pb.pos.y + TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[2].vtx.z = 0.0f;

		g_player_bat.pb.vertexWk[3].vtx.x = g_player_bat.pb.pos.x + TEXTURE_BATTER_SIZE_X;
		g_player_bat.pb.vertexWk[3].vtx.y = g_player_bat.pb.pos.y + TEXTURE_BATTER_SIZE_Y;
		g_player_bat.pb.vertexWk[3].vtx.z = 0.0f;
		break;
	}
	default:
		break;
	}
}

//=============================================================================
// �e�v���C���[�̃A�h���X��Ԃ�
//=============================================================================
PLAYER_PIT *GetPlayerPit(void)
{
	return &g_player_pit;
}
PLAYER_BAT *GetPlayerBat(void)
{
	return &g_player_bat;
}

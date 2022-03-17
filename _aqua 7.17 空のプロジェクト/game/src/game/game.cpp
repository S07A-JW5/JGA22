
/*!
 *  @file       game.cpp
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"

const unsigned int  CGame::m_clear_color = 0xff808080;
const float         CGame::m_gravity = 9.8f;

/*
 *  �R���X�g���N�^
 */
CGame::
CGame( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "Game" )
{
}

/*
 *  ������
 */
void
CGame::
Initialize(void)
{
    m_Sprite.Create("data\\abe.png");
}

/*
 *  �X�V
 */
void
CGame::
Update(void)
{
    if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
    {
        m_Accelerator.y += -500.0f;
    }

    m_Accelerator.y += m_gravity * aqua::GetDeltaTimeScale();

    m_Velocity += m_Accelerator * aqua::GetDeltaTime();

    m_Sprite.position += m_Velocity * aqua::GetDeltaTime();

    float h = (float)(aqua::GetWindowHeight() - m_Sprite.GetTextureHeight());

    if (m_Sprite.position.y > h)
    {
        m_Sprite.position.y = h;

        m_Accelerator.y = 0.0f;
        m_Velocity.y = 0.0f;
    }
}

/*
 *  �`��
 */
void
CGame::
Draw(void)
{
    // ��ʂ̃N���A
    aqua::Clear(m_clear_color);

    m_Sprite.Draw();
}

/*
 *  ���
 */
void
CGame::
Finalize(void)
{
    m_Sprite.Delete();
}

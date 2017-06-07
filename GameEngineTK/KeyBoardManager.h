//************************************************/
//* @file  :KeyBoardManager.h
//* @brief :�L�[�{�[�h�̏�Ԃ��Ǘ�����N���X
//* @date  :2016/06/07
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <Keyboard.h>
#include "MacroConstants.h"

class KeyBoardManager
{
public:
	static KeyBoardManager* m_instance;

public:
	// �V���O���g��
	static KeyBoardManager* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new KeyBoardManager();
		}
		return m_instance;
	}

	//���̂̍폜
	static void DeleteInstance() { DELETE_POINTER(m_instance); }

private:
	std::unique_ptr<DirectX::Keyboard>m_key;

public:
	DirectX::Keyboard::State GetState() { return m_key->GetState(); }
	DirectX::Keyboard* GetKeyBoard() { return m_key.get(); }

private:
	KeyBoardManager() {
		m_key = std::make_unique<DirectX::Keyboard>();
	}

};
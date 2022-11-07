#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = NULL;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	delete sharedInstance;
}

void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		//THERE IS MOUSE MOVE EVENT
		std::vector<InputListener*>::iterator it = inputListenerList.begin();

		while (it != inputListenerList.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x - m_old_mouse_pos.m_x, current_mouse_pos.y - m_old_mouse_pos.m_y));
			++it;
		}
	}
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);



	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::vector<InputListener*>::iterator it = inputListenerList.begin();

				while (it != inputListenerList.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i]) 
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else
						(*it)->onKeyDown(i);

					++it;
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::vector<InputListener*>::iterator it = inputListenerList.begin();

					while (it != inputListenerList.end())
					{
						if (i == VK_LBUTTON)
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else if (i == VK_RBUTTON)
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else
							(*it)->onKeyUp(i);

						++it;
					}
				}
			}
		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	inputListenerList.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	inputListenerList.push_back(listener);
}

void InputSystem::setCursorPosition(const Point & pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

bool InputSystem::isKeyDown(int key)
{
	if (::GetKeyboardState(m_keys_state))
	{
		if (m_keys_state[key] & 0x80)
		{
			return true;
		}
	}

	return false;
}

bool InputSystem::isKeyUp(int key)
{
	if (::GetKeyboardState(m_keys_state))
	{
		if (!m_keys_state[key] & 0x80)
		{
			return true;
		}
	}

	return false;
}

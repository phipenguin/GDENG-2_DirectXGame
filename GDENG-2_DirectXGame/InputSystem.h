#pragma once
#include "InputListener.h"
#include "Point.h"
#include <vector>

class InputSystem
{
public:
	typedef std::vector<InputListener*> List;

	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Point& pos);
	void showCursor(bool show);

	bool isKeyDown(int key);
	bool isKeyUp(int key);

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};
	static InputSystem* sharedInstance;

	List inputListenerList;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};

	Point m_old_mouse_pos;
	bool m_first_time = true;
};
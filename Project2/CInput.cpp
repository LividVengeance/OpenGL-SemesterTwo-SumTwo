#include "CInput.h"

CInput::CInput()
{
}

CInput::~CInput()
{
}

void CInput::ProcessInput()
{
	for (int i = 0; i < 255; i++)
	{
		if (KeyState[i] == INPUT_DOWN_FIRST)
		{
			KeyState[i] = INPUT_DOWN;
		}
		else if (KeyState[i] == INPUT_UP_FIRST)
		{
			KeyState[i] = INPUT_UP;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (MouseState[i] == INPUT_DOWN_FIRST)
		{
			MouseState[i] = INPUT_DOWN;
		}
		else if (MouseState[i] == INPUT_UP_FIRST)
		{
			MouseState[i] = INPUT_UP;
		}
	}
}

void CInput::MouseClick(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	if (button >= 3)
	{
		return;
	}

	MouseState[button] = ((state == GLUT_DOWN) ? INPUT_DOWN_FIRST : INPUT_UP_FIRST);
}

void CInput::KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN_FIRST;
}

void CInput::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP_FIRST;
}

void CInput::MousePassiveMove(int x, int y)
{
	//std::cout << "Passive x: " << x << " | y: " << y << std::endl;
}

void CInput::MouseMove(int x, int y)
{
	//std::cout << "Clicked x: " << x << " | y: " << y << std::endl;
}

bool CInput::getKeyState(char key)
{
	// Gets KeyBoard State
	if (KeyState[key] == INPUT_DOWN)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

int CInput::getMouseX()
{
	return(mouseX);
}

int CInput::getMouseY()
{
	return(mouseY);
}

bool CInput::getClick(int button)
{
	if (MouseState[button] == INPUT_DOWN)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

bool CInput::GetFirstDown(int button)
{
	if (MouseState[button] == INPUT_DOWN_FIRST)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

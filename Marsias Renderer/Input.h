#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

class Input
{
public:
	enum class KeyCode
	{
		Space = 32, Apostrophe = 39, Comma = 44, Minus, Period, Slash, Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Semicolon = 59, Equal = 61,
		A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		LeftBracket, Backslash, RightBracket, GraveAccent = 96, World1 = 161, World2, Escape = 256, Enter, Tab, Backspace,
		Insert, Delete, Right, Left, Down, Up, PageUp, PageDown, Home, End, CapsLock = 280, ScrollLock, NumLock, PrintScreen, Pause,
		F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
		Kp0 = 320, Kp1, Kp2, Kp3, Kp4, Kp5, Kp6, Kp7, Kp8, Kp9, KpDecimal, KpDivide, KpMultiply, KpSubtract, KpAdd, KpEnter, KpEqual,
		LeftShift = 340, LeftControl, LeftAlt, LeftSuper, RightShift, RightControl, RightAlt, RightSuper, Menu, Unknown = -1
	};
	enum class KeyState { Release, Press, Down, Up };

private:
	std::map<KeyCode, KeyState> m_states;
	GLFWwindow* window;

public:
	Input(GLFWwindow* window);

	void updateStates();
	
	bool getKeyDown(KeyCode keyCode);
	bool getKeyUp(KeyCode keyCode);
	bool isKeyPressed(KeyCode keyCode);
	KeyState getKeyState(KeyCode keyCode);
};
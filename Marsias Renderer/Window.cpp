#include "Window.h"
#include "Log.h"
#include "Sprite.h"
#include "Camera.h"

#include <stb_image.h>

Window::Window(int width, int height, const char* title, Camera* camera)
{
	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		LOG("Failed to create glfw window!");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG("Failed to initialize GLAD!");
	}

	glViewport(0, 0, width, height);

	this->defaultShader = new Shader("defaultShader.vert", "defaultShader.frag");
	this->camera = camera;

	std::initializer_list<KeyCode> KeyList = {
		KeyCode::Space, KeyCode::Apostrophe, KeyCode::Comma, KeyCode::Minus, KeyCode::Period, KeyCode::Slash, KeyCode::Num0, KeyCode::Num1, KeyCode::Num2, KeyCode::Num3, KeyCode::Num4, KeyCode::Num5, KeyCode::Num6, KeyCode::Num7, KeyCode::Num8, KeyCode::Num9, KeyCode::Semicolon, KeyCode::Equal,
		KeyCode::A, KeyCode::B, KeyCode::C, KeyCode::D, KeyCode::E, KeyCode::F, KeyCode::G, KeyCode::H, KeyCode::I, KeyCode::J, KeyCode::K, KeyCode::L, KeyCode::M, KeyCode::N, KeyCode::O, KeyCode::P, KeyCode::Q, KeyCode::R, KeyCode::S, KeyCode::T, KeyCode::U, KeyCode::V, KeyCode::W, KeyCode::X, KeyCode::Y, KeyCode::Z,
		KeyCode::LeftBracket, KeyCode::Backslash, KeyCode::RightBracket, KeyCode::GraveAccent, KeyCode::World1, KeyCode::World2, KeyCode::Escape, KeyCode::Enter, KeyCode::Tab, KeyCode::Backspace,
		KeyCode::Insert, KeyCode::Delete, KeyCode::Right, KeyCode::Left, KeyCode::Down, KeyCode::Up, KeyCode::PageUp, KeyCode::PageDown, KeyCode::Home, KeyCode::End, KeyCode::CapsLock, KeyCode::ScrollLock, KeyCode::NumLock, KeyCode::PrintScreen, KeyCode::Pause,
		KeyCode::F1, KeyCode::F2, KeyCode::F3, KeyCode::F4, KeyCode::F5, KeyCode::F6, KeyCode::F7, KeyCode::F8, KeyCode::F9, KeyCode::F10, KeyCode::F11, KeyCode::F12, KeyCode::F13, KeyCode::F14, KeyCode::F15, KeyCode::F16, KeyCode::F17, KeyCode::F18, KeyCode::F19, KeyCode::F20, KeyCode::F21, KeyCode::F22, KeyCode::F23, KeyCode::F24, KeyCode::F25,
		KeyCode::Kp0, KeyCode::Kp1, KeyCode::Kp2, KeyCode::Kp3, KeyCode::Kp4, KeyCode::Kp5, KeyCode::Kp6, KeyCode::Kp7, KeyCode::Kp8, KeyCode::Kp9, KeyCode::KpDecimal, KeyCode::KpDivide, KeyCode::KpMultiply, KeyCode::KpSubtract, KeyCode::KpAdd, KeyCode::KpEnter, KeyCode::KpEqual,
		KeyCode::LeftShift , KeyCode::LeftControl, KeyCode::LeftAlt, KeyCode::LeftSuper, KeyCode::RightShift, KeyCode::RightControl, KeyCode::RightAlt, KeyCode::RightSuper, KeyCode::Menu, KeyCode::Unknown };

	// Input register
	for (auto& key : KeyList)
	{
		m_states[key] = KeyState::Release;
	}
}

void Window::prepareShader()
{
	defaultShader->use();
	defaultShader->setInt("u_texture", 0);
	defaultShader->setMat4f("u_PV", camera->getPV());
}

void Window::render(Sprite* sprite)
{
	sprite->render(this->defaultShader);
}

void Window::prepareNextFrame()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
	this->processInputs();
}

void Window::setFramebufferSizeCallback(void(*size_callback)(GLFWwindow*, int, int))
{
	glfwSetFramebufferSizeCallback(window, size_callback);
}

void Window::processInputs()
{
	for (auto& pair : m_states)
	{
		int state = glfwGetKey(window, (int)pair.first);
		if (state == GLFW_PRESS)
		{
			if (pair.second == KeyState::Release || pair.second == KeyState::Up)
				pair.second = KeyState::Down;
			else if (pair.second == KeyState::Down)
				pair.second = KeyState::Press;
		}
		else if(state == GLFW_RELEASE)
		{
			if (pair.second == KeyState::Press || pair.second == KeyState::Down)
				pair.second = KeyState::Up;
			else if (pair.second == KeyState::Up)
				pair.second = KeyState::Release;
		}
	}
}

void Window::PrepareWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	stbi_set_flip_vertically_on_load(true);
}
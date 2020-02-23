#include "Log.h"
#include "Window.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Sprite.h"

#include <string>
#include <sstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput();

// Window
Window* window;

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
const char* TITLE = "Renderer Sandbox";

// Camera
Camera camera(1.0f * SCR_WIDTH / SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 1.0f));
float deltaTime;
Sprite* sprite;

int main()
{
	Window::PrepareWindow();
	window = new Window(SCR_WIDTH, SCR_HEIGHT, TITLE, &camera);
	window->setFramebufferSizeCallback(framebuffer_size_callback);

	// Texture
	Texture texture("Resources/awesomeface.png");

	// Rectangle
	sprite = new Sprite(0, 0, texture);
	sprite->setScale(0.2f, 0.2f);
	const int nSprite = 100;
	Sprite* sprites = new Sprite[nSprite];
	for (size_t i = 0; i < nSprite; i++)
	{
		sprites[i] = Sprite(2.0f * rand() / RAND_MAX - 1.0f, 2.0f * rand() / RAND_MAX - 1.0f, texture);
		sprites[i].setScale(0.1f, 0.1f);
	}

	float prevTime = glfwGetTime();

	float totalTime = 0.0f;
	int n = 0;
	int maxN = 500;

	while (!window->shouldWindowClose())
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;
		
		if (totalTime >= 0.2f)
		{
			std::stringstream ss;
			ss << TITLE << "    FPS: " << n / totalTime;
			std::string str = ss.str();
			const char* title = str.c_str();
			glfwSetWindowTitle(window->getGLFWwindow(), title);
			totalTime = 0.0f;
			n = 0;
		}
		totalTime += deltaTime;
		n++;

		processInput();

		window->clear();
		window->prepareShader();

		window->render(sprite);
		for (int i = 0; i < nSprite; i++)
			window->render(&sprites[i]);

		window->prepareNextFrame();
	}

	Window::Terminate();
	return 0;
}

void processInput()
{
	if (window->getKey(KeyCode::Escape) == KeyState::Press)
		window->close();

	if (window->getKey(KeyCode::W) == KeyState::Press)
		sprite->move(deltaTime * glm::vec3(0.0f, 1.0f, 0.0f));
	if (window->getKey(KeyCode::S) == KeyState::Press)
		sprite->move(deltaTime * glm::vec3(0.0f, -1.0f, 0.0f));
	if (window->getKey(KeyCode::D) == KeyState::Press)
		sprite->move(deltaTime * glm::vec3(1.0f, 0.0f, 0.0f));
	if (window->getKey(KeyCode::A) == KeyState::Press)
		sprite->move(deltaTime * glm::vec3(-1.0f, 0.0f, 0.0f));
	if (window->getKey(KeyCode::Q) == KeyState::Press)
		sprite->rotate(deltaTime * 90.0f);
	if (window->getKey(KeyCode::E) == KeyState::Press)
		sprite->rotate(-deltaTime * 90.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camera.setAspectRatio(1.0f * width / height);
}
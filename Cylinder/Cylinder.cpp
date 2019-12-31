#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void setProj();

#define PI 3.14159

static int longti = 4;
static int lat = 20;

float f(int i, int j) {

	return (cos((-1 + 2 * (float)i / longti) * PI));

}

float g(int i, int j) {

	return (sin((-1 + 2 * (float)i / longti) * PI));

}

float h(int i, int j) {

	return (-1 + 2 * (float)j / lat);

}

void fillVertexArray(void) {
	int i, int j;
}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // glBegin只在低版本opengl中运行
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	
	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 输入
		processInput(window);

		// 渲染指令
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0., 1.0, 1.0);
		glPolygonMode(GL_FRONT, GL_LINE);

		setProj();
		glRotatef(21.1, 11., 1.,1.);

		fillVertexArray();
		int i, j; 
		for (j = 0; j <= longti; j++) {
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i <= lat; i++) {
				glArrayElement((j + 1) * (lat + 1) + i);
				glArrayElement(j * (lat + 1) + i);
			}
			glEnd();
		}
		
		

		glFlush();
		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	setProj();
}

void setProj() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-15.0, 15.0, -15.0, 25.0, 5, 120.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//是否按下了返回键
		glfwSetWindowShouldClose(window, true);
}
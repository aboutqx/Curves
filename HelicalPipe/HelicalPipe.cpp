#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void setProj();

#define PI 3.14159265358979324

static int longti = 20;
static int lat = 24;
static float* vertices = NULL;
static float Xangle = 20.0, Yangle = 120.0, Zangle = 0.0; // Angles to rotate the cylinder.

float f(int i, int j) {

	return (cos((-1 + 2 * (float)i / lat) * PI)+ sin((-1 + 2 * (float)j / longti) * PI));

}

float g(int i, int j) {

	return (sin((-1 + 2 * (float)i / lat) * PI)+cos((-1 + 2 * (float)j / longti) * PI));

}

float h(int i, int j) {

	return (-1 + 2 * (float)i / lat) * PI;

}

void fillVertexArray(void) {
	int i, j, sum;
	sum = 0;
	for (j = 0; j <= longti; j++) {
		for (i = 0; i <= lat; i++) {
			vertices[sum++] = f(i, j);
			vertices[sum++] = g(i, j);
			vertices[sum++] = h(i, j);
		}
	}
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
	glfwSetKeyCallback(window, keyCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}




	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 输入

		glEnableClientState(GL_VERTEX_ARRAY);

		// 渲染指令
		vertices = new float[3 * (lat + 1) * (longti + 1)]; // Dynamic array allocation with new value of p and q. 
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0., 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		setProj();
		glTranslatef(0, 0., -4);
		glRotatef(Zangle, 0., 0., 1.);
		glRotatef(Yangle, 0., 1., 0.);
		glRotatef(Xangle, 1., 0., 0.);

		fillVertexArray();
		int i, j;
		for (j = 0; j < longti; j++) {
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
	glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 150.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_PRESS)//是否按下了返回键
		glfwSetWindowShouldClose(window, true);
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		//glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		//glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		//glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		//glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		//glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		//glutPostRedisplay();
		break;
	default:
		break;
	}
}
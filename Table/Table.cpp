#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void setProj();

#define PI 3.14159265358979324

static int t = 42;
static int lat = 20;
static float* vertices = NULL;
static float Xangle = 10.0, Yangle = 60.0, Zangle = 0.0; // Angles to rotate the cylinder.

//������µ㵽����ľ������������ӵ�x��yֵ
float x(int t, float theta) {
	int tmp;
	if (0 <= t && t <= 4) {
		tmp = t;
	}
	else if (4 < t && t <= 5) {
		tmp = 4;
	}
	else if (5 < t && t <= 8) {
		tmp = (9 - t);
	}
	else if (8 < t && t <= 22) {
		tmp = 1;
	}
	else if (22 < t && t <= 31) {
		tmp = (t - 21);
	}
	else if (31 < t && t <= 32) {
		tmp = 10;
	}
	else if (32 < t && t <= 42) {
		tmp = (42-t) ;
	}
	return tmp * cos(theta);

}

float y(int t) {

	if (0 <= t && t <= 4) {
		return -8;
	}
	else if (4<t && t<=5) {
		return t - 12;
	}
	else if (5 < t && t <= 8) {
		return -7;
	}
	else if (8 < t && t <= 22) {
		return t - 15;
	}
	else if (22 < t && t <= 31) {
		return 7;
	}
	else if (31 < t && t <= 32) {
		return t - 24;
	}
	else if (32 < t && t <= 42) {
		return 8;
	}
}

float z(int t, float theta) {
	int tmp;

	if (0 <= t && t <= 4) {
		tmp = t;
	}
	else if (4 < t && t <= 5) {
		tmp = 4;
	}
	else if (5 < t && t <= 8) {
		tmp = (9 - t);
	}
	else if (8 < t && t <= 22) {
		tmp = 1 ;
	}
	else if (22 < t && t <= 31) {
		tmp = (t - 21) ;
	}
	else if (31 < t && t <= 32) {
		tmp = 10;
	}
	else if (32 < t && t <= 42) {
		tmp = (42 - t);
	}
	return tmp * sin(theta);

}

void fillVertexArray(void) {
	int i, j, sum;
	sum = 0;
	for (j = 0; j <= t; j++) {
		for (i = 0; i <= lat; i++) {
			float convert = (-1 + 2 * (float)i / lat) * PI;
			vertices[sum++] = x(j, convert);
			vertices[sum++] = y(j);
			vertices[sum++] = z(j, convert);
		}
	}
}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // glBeginֻ�ڵͰ汾opengl������
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




	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ����

		glEnableClientState(GL_VERTEX_ARRAY);

		// ��Ⱦָ��
		vertices = new float[3 * (lat + 1) * (t + 1)]; // Dynamic array allocation with new value of p and q. 
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0., 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		setProj();
		glTranslatef(0, 5., -6);
		glRotatef(Zangle, 0., 0., 1.);
		glRotatef(Yangle, 0., 1., 0.);
		glRotatef(Xangle, 1., 0., 0.);

		fillVertexArray();
		int i, j;
		for (j = 0; j < t; j++) {
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i <= lat; i++) {

				glArrayElement((j + 1) * (lat + 1) + i);
				glArrayElement(j * (lat + 1) + i);
			}
			glEnd();
		}


		glFlush();
		// ��鲢�����¼�����������
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
	glFrustum(-5.5, 5.5, -5.5, 5.5, 1.5, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_PRESS)//�Ƿ����˷��ؼ�
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
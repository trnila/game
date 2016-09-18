//Include GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>



static void error_callback(int error, const char* description){ fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height){
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow *window, double x, double y){ printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

char* readFile(const char *path) {
	FILE* f = fopen(path, "r");
	if(!f) {
		perror("readFile: ");
		exit(1);
	}

	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	rewind(f);
	char *content = new char[size + 1];
	if(fread(content, size, 1, f) != 1) {
		perror("readfile fread");
		exit(1);
	}
	content[size] = '\0';
	printf("%s", content);
	return content;
}

GLuint createShader(const char *path, GLenum type) {
	const GLchar* source = readFile(path);

	GLuint res = glCreateShader(type);
	const GLchar* sources[] = {
#ifdef GL_ES_VERSION_2_0
		"#version 100\n",  // OpenGL ES 2.0
#else
		"#version 120\n",  // OpenGL 2.1
#endif
		source
	};
	glShaderSource(res, 2, sources, NULL);
	delete[] source;	

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		//print_log(res);
		glDeleteShader(res);
		return 0;
	}

	return res;
}

//GLM test

// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
	glm::mat4 View = glm::lookAt(
			glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	GLuint program;
	GLint attribute_coord2d;
int init_resources()
{
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
	GLuint vs = createShader("triangle.v.glsl", GL_VERTEX_SHADER);
	GLuint fs = createShader("triangle.f.glsl", GL_FRAGMENT_SHADER);
	
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		return 0;
	}
	const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord2d == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		return 0;
	}
	return 1;
}


int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

	glewInit();
	init_resources();


	while (!glfwWindowShouldClose(window)) {
		glClearColor(.0, .0, .0, .0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glEnableVertexAttribArray(attribute_coord2d);
		GLfloat triangle_vertices[] = {
			-0.8,  0.8,
			-0.8, -0.8,
			0.8, -0.8,

			0.8, 0.8,
			-0.8, 0.8,
			0.8, -0.8
		};
		/* Describe our vertices array to OpenGL (it can't guess its format automatically) */
		glVertexAttribPointer(
				attribute_coord2d, // attribute
				2,                 // number of elements per vertex, here (x,y)
				GL_FLOAT,          // the type of each element
				GL_FALSE,          // take our values as-is
				0,                 // no extra data between each position
				triangle_vertices  // pointer to the C array
				);


		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

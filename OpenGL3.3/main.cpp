#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"out vec3 OurColor;\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	OurColor = aColor;"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 OurColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(OurColor, 1.0f);\n"
"}\0";

const char* fragmentShaderYellowSource = "#version 330 core\n"
"in vec3 OurColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Erro na criação de janela" << std::endl;
		glfwTerminate();
		return-1;
	}
	glfwMakeContextCurrent(window); // Contexto do glfw

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Erro na criação do glad" << std::endl;
		return-1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	/* Rectangle
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // top right
		0.5f,-0.5f, 0.0f,   0.0f, 0.0f, 0.0f, // bottom right
		-0.5f,-0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // top left
	};
	unsigned int index[] = { // note that we start from 0!
		0, 2, 3, // first triangle
		0, 1, 2, // second triangle
	};*/

	/* Two Triangles
	float vertices[] = {
		-0.5f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		0.5f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
	};

	unsigned int index[] = {
		0, 1, 2,
		3, 4, 5,
	};
	*/

	float vertices1[] = {
		-0.5f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	};
	unsigned int index1[] = {
		0, 1, 2,
	};

	float vertices2[] = {
		0.5f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
	};

	unsigned int index2[] = {
		0, 1, 2,
	};


	// Vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Fragment Shader do amarelo bizoho ui
	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
	glCompileShader(fragmentShaderYellow);

	// Criação e linkagem do shaderProgram
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Shader program 2.0 com o fragment shader amarelo
	unsigned int shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);


	// Deletando os shaders depois de linkar no shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderYellow);

	unsigned int VBO, VAO, EBO, VBO2, VAO2, EBO2;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	// Modo de gravação do VAO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index1), index1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Debindar os bufferss
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Triângulo 2
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index2), index2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		glUseProgram(shaderProgramYellow);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
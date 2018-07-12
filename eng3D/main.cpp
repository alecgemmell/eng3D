
#include <loophelp.cpp>
#include <common/loadShader.hpp>

GLFWwindow* window;

void setupHints() {
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return;
}
int initGLFW() {
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	return 0;
}
int openWindow() {
	window = glfwCreateWindow(1280, 720, "73Engine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	return 0;
}
int initGLEW() {
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	return 0;
}

int main(void)
{
	
	// Initialise GLFW
	initGLFW();
	//setup GLFW window hints
	setupHints();
	// Open a window and create its OpenGL context
	openWindow();
	// Initialize GLEW
	initGLEW();

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Create vertex array object and set it as the current one
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// create glsl program from shaders
	GLuint programID = LoadShaders("vertexshader.vs", "fragmentshader.fs");

	//get handle for mvp matrix
	GLuint MatrixID = glGetUniformLocation(programID, "mvp");
	// Create array of triangle vertices
	static const GLfloat g_tri_vertex_buffer_data[] = {
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	std::vector<GLfloat> g_vertex_buffer_data;
	getRectVertices(2.0f, 2.0f, 2.0f, g_vertex_buffer_data);
	static const GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
	//int size = g_vertex_buffer_data.size();

	// proj matrix
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);
	// cam matrix
	Camera cam;
	cam.position(glm::vec3(0, 0, 8));
	glm::mat4 View = cam.getView();
	// cube model mat
	glm::mat4 CubeModel = glm::mat4(1.0f);
	glm::mat4 CubeTranslation = glm::translate(glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 CubeRotation = glm::rotate(45.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 CubeScale = glm::scale(glm::vec3(0.5f, 0.5f, 2.0f));
	CubeModel = CubeTranslation*CubeRotation*CubeScale*CubeModel;
	// model view projection matrix
	glm::mat4 cubeMVP = Projection * View * CubeModel;

	// tri model mat
	glm::mat4 TriModel = glm::mat4(1.0f);
	glm::mat4 TriTranslation = glm::translate(glm::vec3(-1.0f, 1.0f, 0.0f));
	glm::mat4 TriRotation = glm::rotate(0.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 TriScale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	TriModel = TriTranslation*TriRotation*TriScale*TriModel;
	// mvp matrix for triangle
	glm::mat4 triMVP = Projection * View * TriModel;


	// Create Identifier for vertex buffer
	GLuint vertexbuffer;
	// generate a buffer and put the reseulting identifier in the identifier
	glGenBuffers(1, &vertexbuffer);
	// set the buffer as an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// give vertices to OpenGL by putting array into the buffer
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size()*sizeof(g_vertex_buffer_data[0]), &g_vertex_buffer_data[0], GL_STATIC_DRAW);
	
	GLuint trivertexbuffer;
	glGenBuffers(1, &trivertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, trivertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_tri_vertex_buffer_data), g_tri_vertex_buffer_data, GL_STATIC_DRAW);

	// Create Identifier for color buffer
	GLuint colorbuffer;
	//generate a buffer and put identifier in the colorbuffer GLuint
	glGenBuffers(1, &colorbuffer);
	// set to array buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	std::chrono::time_point<std::chrono::system_clock> prev, current;
	double prev_x, prev_y;
	double cur_x=0, cur_y=0;
	float dx, dy;
	current = std::chrono::system_clock::now();
	float rotation = 0.0f;
	double frame_time;
	float rx = 0, ry = 0;
	do {
		//simulate
		frame_time = update(prev, current);
		rotation += (float)frame_time;
		if (rotation > 360) {
			rotation -= 360.0f;
		}
		TriRotation = glm::rotate(rotation, glm::vec3(0.0f, 0.0f, -1.0f));
		//View = updateCamera(View, window, frame_time);
		prev_x = cur_x;
		prev_y = cur_y;
		glfwGetCursorPos(window, &cur_x, &cur_y);
		dx = (prev_x-cur_x)*.001;
		dy = (prev_y-cur_y)*.001;
		View = updateCamera(cam, window, frame_time, dx, dy);

		
		TriModel = TriTranslation*TriRotation*TriScale*glm::mat4(1.0f);
		triMVP = Projection*View*TriModel;
		cubeMVP = Projection*View*CubeModel;

		//render
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		//draw cube
		drawObjects(MatrixID, cubeMVP, vertexbuffer, colorbuffer, 3 * 6 * 2);
		//draw triangle
		drawObjects(MatrixID, triMVP, trivertexbuffer, colorbuffer, 3);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
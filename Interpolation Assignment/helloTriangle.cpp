//g++ -o helloTriangle helloTriangle_class.cpp libglfw3dll.a libglew32.dll.a -I include -lglew32 -lglfw3 -lgdi32 -lopengl32
//g++ -o helloTriangle.exe helloTriangle.cpp libglfw3dll.a libglew32.dll.a -I include -lglew32 -lglfw3 -lgdi32 -lopengl32
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 

  // uncomment these lines if on Apple OS X
  /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
                                  
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  glPointSize(5.0f);
  glClearColor(0.6f,0.6f,0.8f,1.0f);

  /* OTHER STUFF GOES HERE NEXT */
	float points[] = {
	   0.25f,  -0.25f,  0.0f,
	   0.25f, -0.75f,  0.0f,
	   0.75f, -0.75f,  0.0f
	};

	float points2[] = {
	   0.25f, 0.75f, 0.0f,
	   0.5f, 0.25f, 0.0f,
	   0.75f, 0.5f, 0.0f
	};
	
	float points3[] = {
		-0.5f, -0.25f, 0.0f,
		-0.75f, -0.75f, 0.0f,
		-0.25f, -0.75f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vbo1 = 1;
	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points2, GL_STATIC_DRAW);
	
	GLuint vbo2 = 2;
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points3, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLuint vao1 = 0;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	GLuint vao2 = 0;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	const char* vertex_shader =
	"#version 400\n"
	"in vec3 vp;"
	"void main() {"
	"  gl_Position = vec4(vp.x, vp.y, vp.z, 1.0);"
	"}";
	
	const char* vertex_shader1 =
	"#version 400\n"
	"in vec3 vp;"
	"void main() {"
	"  gl_Position = vec4(vp.x, vp.y, vp.z, 1.0);"
	"}";
	
	const char* vertex_shader2 =
	"#version 400\n"
	"in vec3 vp;"
	"void main() {"
	"  gl_Position = vec4(vp.x, vp.y, vp.z, 1.0);"
	"}";

	const char* fragment_shader =
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(5.0, 2.0, 0.0, 1.0);"
	"}";	

	const char* fragment_shader1 =
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(0.0, 5.0, 2.0, 1.0);"
	"}";

	const char* fragment_shader2 =
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main() {"
	"  frag_colour = vec4(2.0, 0.0, 5.0, 1.0);"
	"}";

	//Zero
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	//One
	GLuint vs1 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs1, 1, &vertex_shader1, NULL);
	glCompileShader(vs1);
	
	GLuint fs1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs1, 1, &fragment_shader1, NULL);
	glCompileShader(fs1);

	GLuint shader_programme1 = glCreateProgram();
	glAttachShader(shader_programme1, fs1);
	glAttachShader(shader_programme1, vs1);
	glLinkProgram(shader_programme1);
	
	//Two
	GLuint vs2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs2, 1, &vertex_shader2, NULL);
	glCompileShader(vs2);
	
	GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs2, 1, &fragment_shader2, NULL);
	glCompileShader(fs2);

	GLuint shader_programme2 = glCreateProgram();
	glAttachShader(shader_programme2, fs2);
	glAttachShader(shader_programme2, vs2);
	glLinkProgram(shader_programme2);
			  
	int logLen;
	GLchar* log;
	glGetProgramiv(shader_programme2, GL_INFO_LOG_LENGTH, &logLen);

	/*if(logLen > 0) {

		// Show any errors as appropriate

		glGetProgramInfoLog(shader_programme1, logLen, &logLen, log);

		fprintf(stderr, "Prog Info Log: %s\n", log);

	}*/
			
	cout << "here\n"; 			
		  
	while(!glfwWindowShouldClose(window)) {
	  // wipe the drawing surface clear
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glUseProgram(shader_programme);
	  glBindVertexArray(vao);
	  glPointSize(5.0);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays(GL_TRIANGLES, 0, 3);

	  glUseProgram(shader_programme1);
	  glBindVertexArray(vao1);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays(GL_TRIANGLES, 0, 3);

	  glUseProgram(shader_programme2);
	  glBindVertexArray(vao2);
	  // draw points 0-3 from the currently bound VAO with current in-use shader
	  glDrawArrays(GL_TRIANGLES, 0, 3);
	  
	  // update other events like input handling 
	  glfwPollEvents();
	  // put the stuff we've been drawing onto the display
	  glfwSwapBuffers(window);
	}

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}


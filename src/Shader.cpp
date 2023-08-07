#include "../headers/Shader.hpp"

GLuint	_gSamplerLocation;

Shader::Shader(void)
{
    return;
}

Shader::~Shader(void)
{
    return;
}


// this whole chunk can be simplified, divided into several funtions
// check ogldev approach in his intro to shaders
GLuint load_shaders(const char * vertex_file_path,const char * fragment_file_path)
{
	// ******************************
	// * Create and compile shaders *
	// ******************************

	////Turn those into attributes ?
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		std::cout << "Impossible to open " << vertex_file_path << "\nAre you in the right directory ?" << std::endl;
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling shader: " << vertex_file_path << std::endl;
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader compiling success
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result); // check GL_COMPILE_STATUS in shader pointed by VertexShaderID, put result in our GLint Result
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << &VertexShaderErrorMessage[0];
	}

	// Compile Fragment Shader
	std::cout << "Compiling shader: " << fragment_file_path << std::endl;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader compiling success
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << &FragmentShaderErrorMessage[0];
	}

	// **********************************
	// * Link shaders to program object *
	// **********************************

	// Create a "program object"
	std::cout << "Linking program" << std::endl;
	GLuint ProgramID = glCreateProgram();
	if (ProgramID == 0) {
		//error
		std::cout << "Error creating Shader handle (:" << std::endl;
		exit(-1);
	}

	// Attach our shaders to program, link program
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program link success
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0];
	}

	// Trying to implement textures
	_gSamplerLocation = glGetUniformLocation(ProgramID, "gSampler");
    if (_gSamplerLocation == 0) {
        std::cout << "Error getting uniform location of 'gSampler'" << std::endl;
        exit(-1);
    }

	// Addiotionnal good practice : check if linked program is actually compatible !
	glValidateProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_VALIDATE_STATUS, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	// make program and shaders active on GPU's side
	glUseProgram(ProgramID);


	// We don't need the sources of shaders anymore, we can detach them from program & delete them
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	// debug
	// int count = 0;
	// GLuint shad[2];

	// glGetAttachedShaders(ProgramID, 2, &count, shad);
	// std::cout << "COUNT IS = " << count << std::endl;
	return ProgramID;
}
#include "shader.h"

using namespace std;

// shader code reader, will parse code from files linked by #include
std::string getShaderCode(const char * path) {
	std::string temp = "";
	std::ifstream stream(path, std::ios::in);
	if (stream.is_open()) {
		std::string Line = "";
		while (getline(stream, Line))
			if (Line.substr(0, 8) == "#include") {
				std::string pathNew = Line.substr(10, Line.length() - 11);
				std::cout << pathNew << std::endl;
				Line = getShaderCode(pathNew.c_str());
				temp += "\n" + Line;
			} else {
				temp += "\n" + Line;
			}
		stream.close();
	}

	return temp;
}

GLuint LoadShaders(const char * vertex_file_path,
		const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Reading shaders code from the files
	std::string VertexShaderCode = getShaderCode(vertex_file_path);
	std::string FragmentShaderCode = getShaderCode(fragment_file_path);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//compiling shaders
	cout << "Compiling shader : " << vertex_file_path << "\n";
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	cout << "Compiling shader : " << fragment_file_path << "\n";
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// checking shader & returning errors
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL,
			&VertexShaderErrorMessage[0]);
	cout << "\n" << &VertexShaderErrorMessage[0];

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL,
			&FragmentShaderErrorMessage[0]);
	cout << "\n" << &FragmentShaderErrorMessage[0];

	// Getting shader to graphics card
	cout << "Linking program\n";
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL,
			&ProgramErrorMessage[0]);
	cout << "\n" << &ProgramErrorMessage[0];

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	// returning GLuint pointing to shader on graphics card
	return ProgramID;
}

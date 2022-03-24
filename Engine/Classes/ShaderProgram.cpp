#include"ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string VertexShaderPath, std::string FragmentShaderPath){
	std::string VertexShaderStrSource = FileIO::ReadFile((VertexShaderPath).c_str());
	std::string FragmentShaderStrSource = FileIO::ReadFile((FragmentShaderPath).c_str());

	if (VertexShaderStrSource == "") {
		Debug::Log("[ShaderProgram::ShaderProgram]: VERTEX shader not found, file specified: '" + VertexShaderPath + "'");

		Debug::ShowPrompt(
			"File loading error",
			"Something went wrong, and we couldn't find a shader file. Please ensure the .exe is in the correct directory.",
			MB_ICONWARNING | MB_OK,
			false
		);
	}

	if (FragmentShaderStrSource == "") {
		Debug::Log("[ShaderProgram::ShaderProgram]: FRAGMENT shader not found, file specified: '" + VertexShaderPath + "'");

		Debug::ShowPrompt(
			"File loading error",
			"Something went wrong, and we couldn't find a shader file. Please ensure the .exe is in the correct directory.",
			MB_ICONWARNING | MB_OK,
			false
		);
	}

	const char* VertexSource = VertexShaderStrSource.c_str();
	const char* FragmentSource = FragmentShaderStrSource.c_str();

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(VertexShader, 1, &VertexSource, NULL);
	glShaderSource(FragmentShader, 1, &FragmentSource, NULL);

	glCompileShader(VertexShader);
	glCompileShader(FragmentShader);

	ShaderProgram::PrintErrors(VertexShader, "vertex shader");
	ShaderProgram::PrintErrors(FragmentShader, "fragment shader");

	ShaderProgram::ID = glCreateProgram();

	glAttachShader(ShaderProgram::ID, VertexShader);
	glAttachShader(ShaderProgram::ID, FragmentShader);

	glLinkProgram(ShaderProgram::ID);

	ShaderProgram::PrintErrors(ShaderProgram::ID, "SHADERPROGRAM");

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

void ShaderProgram::Activate() {
	glUseProgram(ShaderProgram::ID);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(this->ID);
}

void ShaderProgram::PrintErrors(unsigned int Object, const char* Type) {
	GLint HasCompiled;

	char InfoLog[1024];

	if (Type != "SHADERPROGRAM") {
		glGetShaderiv(Object, GL_COMPILE_STATUS, &HasCompiled);

		if (HasCompiled == GL_FALSE) {
			glGetShaderInfoLog(Object, 1024, NULL, InfoLog);

			std::cout << "Error while compiling " << Type << ":\n" << InfoLog << "\n";

			Debug::Log("[ShaderProgram::PrintErrors]: Error while compiling " + (std::string)Type + ":\n" + InfoLog);
		}
	}
	else {
		glGetProgramiv(Object, GL_LINK_STATUS, &HasCompiled);

		if (HasCompiled == GL_FALSE) {
			glGetProgramInfoLog(Object, 1024, NULL, InfoLog);

			std::cout << "Error while creating shader program:\n" << InfoLog << "\n";

			Debug::Log("[ShaderProgram::PrintErrors]: Error while creating shader program:\n" + (std::string)InfoLog);

			Debug::ShowPrompt(
				"Engine error",
				"An error occurred! Details: Shader program failed to compile. Continue running application(may cause graphical glitches)?",
				MB_ICONERROR | MB_YESNO | MB_DEFBUTTON2,
				true
			);
		}
	}
}

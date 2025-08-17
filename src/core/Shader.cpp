#include "Shader.hpp"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath) : rendererId(0) {
	ShaderProgramSource source = parseShader(filepath);
	rendererId = createShader(source.VertexSource, source.FragmentSource);
}
Shader::~Shader() {
	glDeleteProgram(rendererId);
}

ShaderProgramSource Shader::parseShader(const std::string& filepath) {
	std::ifstream stream(filepath);
	if (!stream.is_open()) {
		std::cerr << "Failed to open shader file: " << filepath << std::endl;
		return { "", "" };
	}

	enum class ShaderType {
		None = -1,
		Vertex = 0,
		Fragment = 1,
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::None;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::Fragment;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return {
		ss[0].str(),
		ss[1].str()
	};
}


unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::bind() const {
	glUseProgram(rendererId);
}
void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}
void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
void Shader::setUniform1i(const std::string& name, int value) {
	glUniform1i(getUniformLocation(name), value);
}

int Shader::getUniformLocation(const std::string& name) {
	if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
		return uniformLocationCache[name];
	}
	int location = glGetUniformLocation(rendererId, name.c_str());
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	uniformLocationCache[name] = location;
	return location;
}

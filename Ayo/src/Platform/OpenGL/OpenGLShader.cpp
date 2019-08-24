#include "ayopch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace Ayo
{

	OpenGLShader::OpenGLShader(const std::string vertexSource, const std::string fragmentSource)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = (const GLchar *)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			AYO_CORE_ERROR("Vertex shader compilation fail: {0}", infoLog.data());
			AYO_CORE_ASSERT(false, "Vertex shader failed to compile.");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar *)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			AYO_CORE_ERROR("Fragment shader compilation fail: {0}", infoLog.data());
			AYO_CORE_ASSERT(false, "Fragment shader failed to compile.");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererId = glCreateProgram();
		GLuint program = m_RendererId;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			AYO_CORE_ERROR("Shader linking fail: {0}", infoLog.data());
			AYO_CORE_ASSERT(false, "Shader linking failed.");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UpdateFloatInt(const std::string& uniformName, int value)
	{
		int location = glGetUniformLocation(m_RendererId, uniformName.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UpdateFloatUniform(const std::string& uniformName, float value)
	{
		int location = glGetUniformLocation(m_RendererId, uniformName.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UpdateFloat2Uniform(const std::string& uniformName, const glm::vec2& value)
	{
		int location = glGetUniformLocation(m_RendererId, uniformName.c_str());
		glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UpdateFloat3Uniform(const std::string& uniformName, const glm::vec3& value)
	{
		int location = glGetUniformLocation(m_RendererId, uniformName.c_str());
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UpdateFloat4Uniform(const std::string& uniformName, const glm::vec4& value)
	{
		int location = glGetUniformLocation(m_RendererId, uniformName.c_str());
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UpdateMat3Uniform(const std::string& uniformName, const glm::mat3& value)
	{
		int location = glGetUniformLocation(m_RendererId, uniformName.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UpdateMat4Uniform(const std::string& uniformName, const glm::mat4& value)
	{
		int location = glGetUniformLocation(m_RendererId, uniformName.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

}
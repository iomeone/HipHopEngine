#include "ShaderProgram.h"
#include "../Utils/Logger.h"
#include <cstdio>
#include<glm/gtc/type_ptr.hpp>

	ShaderProgram::ShaderProgram() : m_IsReadyToUse(false), m_ErrorInfo("N/A")
	{
		m_ShaderIDs.reserve(4);
	}

	ShaderProgram::~ShaderProgram()
	{
		
	}

	std::string ShaderProgram::Load(const std::string& path)
	{
		FILE* file = fopen(path.c_str(), "r");
		if (file != NULL)
		{
			char ch = ' ';
			std::string buffer;
			buffer.reserve(1024);

			while (true)
			{
				ch = fgetc(file);
				if (EOF == ch)
					break;
				buffer.push_back(ch);
			}

			fclose(file);
			return buffer;
		}
		else
			return "";
	}

	bool ShaderProgram::AddAndCompile(const std::string & shaderPath, EShaderType type)
	{
		std::string shaderCode = Load(shaderPath);
		if ("" == shaderCode)
		{
			m_ErrorInfo = "Error : couldn't load file from path: " + shaderPath;
			Logger::GetInstance()->Log(m_ErrorInfo.c_str());
			return false;
		}
		

		GLenum shaderType;
		switch (type)
		{
		case EShaderType::VERTEX:
			shaderType = GL_VERTEX_SHADER;
			break;
		case EShaderType::FRAGMENT:
			shaderType = GL_FRAGMENT_SHADER;
			break;
		default:
			
			break;
		}
		
		const char* code = shaderCode.c_str();
		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID,1,&code,NULL);
		glCompileShader(shaderID);

		if (ErrorOccured(shaderID,false))
			return false;

		m_ShaderIDs.push_back(shaderID);
		return true;
	}

	bool ShaderProgram::Build()
	{
		m_ID = glCreateProgram();
		for (GLuint shaderID : m_ShaderIDs)
			glAttachShader(m_ID,shaderID);

		glLinkProgram(m_ID);

		if (ErrorOccured(m_ID, true))
			return false;

		for (GLuint shaderID : m_ShaderIDs)
			glDeleteShader(shaderID);

		m_IsReadyToUse = true;

		return true;
	}

	bool ShaderProgram::ErrorOccured(GLuint id,bool linking)
	{
			GLint success;
			glGetProgramiv(id, linking ? GL_LINK_STATUS : GL_COMPILE_STATUS, &success);
			if (!success)
			{
				GLchar errInfo[512];
				glGetProgramInfoLog(id, 512, 0, errInfo);
				std::string prefix = linking?"Linking" : "Compilation";
				m_ErrorInfo = prefix + " Error :: " + std::string(errInfo);
				Logger::GetInstance()->Log(m_ErrorInfo.c_str());
				return true;
			}
			return false;
	}

	void ShaderProgram::Use()
	{
		if (m_IsReadyToUse)
			glUseProgram(m_ID);
	}

	void ShaderProgram::SetInt(const std::string& pName,int pValue)
	{
		glUniform1i(glGetUniformLocation(m_ID, pName.c_str()), pValue);
	}


	void ShaderProgram::SetFloat(const std::string& pName,float pValue)
	{
		glUniform1f(glGetUniformLocation(m_ID, pName.c_str()), pValue);
	}


	void ShaderProgram::SetVec2(const std::string& pName,const glm::vec2& pVector)
	{
		glUniform2f(glGetUniformLocation(m_ID, pName.c_str()), pVector.x, pVector.y);
	}


	void ShaderProgram::SetVec3(const std::string& pName,const glm::vec3& pVector)
	{
		glUniform3f(glGetUniformLocation(m_ID, pName.c_str()), pVector.x, pVector.y, pVector.z);
	}


	void ShaderProgram::SetVec4(const std::string& pName,const glm::vec4& pVector)
	{
		glUniform4f(glGetUniformLocation(m_ID, pName.c_str()),
			pVector.x, pVector.y, pVector.z, pVector.w);
	}


	void ShaderProgram::SetMat4(const std::string& pName,glm::mat4& pMat)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, pName.c_str()),
			1, GL_FALSE, glm::value_ptr(pMat));
	}

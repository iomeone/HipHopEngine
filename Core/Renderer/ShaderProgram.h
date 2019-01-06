#ifndef _INC_HIP_HOP_SHADER_PROGRAM_H_
#define _INC_HIP_HOP_SHADER_PROGRAM_H_

#include<vector>
#include<cstdint>
#include<glm/glm.hpp>
#include<glad/glad.h>


	enum class EShaderType : std::uint16_t
	{
		VERTEX = 0,
		FRAGMENT,
		MAX
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		bool AddAndCompile(const std::string& shaderPath, EShaderType type);
		bool Build();
		inline const std::string& GetErrorInfo() { return m_ErrorInfo; }
		void Use();
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetVec2(const std::string& name,const glm::vec2& value);
		void SetVec3(const std::string& name, const glm::vec3& value);
		void SetVec4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, glm::mat4& value);

		inline bool IsCurrentlyActive() { return m_IsCurrentlyActive; }
		/*Sets whether this shader is currently in use or not*/
		inline void SetStatus(bool pIsCurrentlyActive) { m_IsCurrentlyActive = pIsCurrentlyActive; }
	protected:
		GLuint m_ID;
		bool m_IsReadyToUse;
		bool m_IsCurrentlyActive;
	private:
		std::string Load(const std::string& path);
		bool ErrorOccured(GLuint id, bool linking);
	private:
		std::vector<GLuint> m_ShaderIDs;
		std::string m_ErrorInfo;
	};

#endif
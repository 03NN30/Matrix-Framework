#include "matrix/src/Shader_Test.h"

namespace MX {

    Shader_Test::Shader_Test() {}

    Shader_Test::Shader_Test(std::string str) {
        vertexSource = str + ".vert";
        fragmentSource = str + ".frag";
    }

    void Shader_Test::setSource(std::string str) {
        vertexSource = str + ".vert";
        fragmentSource = str + ".frag";
    }

    std::string ParseShader(const std::string& filepath) {
    	std::ifstream stream(MX_SHADER_PATH + filepath);
    	std::string line;
    	std::stringstream ss[1];
    
    	while (getline(stream, line)) {
    		ss[0] << line << '\n';
    	}
        //std::cout << ss[0].str() << std::endl;
    	return ss[0].str();
    }

    unsigned int Shader_Test::compileShader(unsigned int type, const std::string& source) {
    	unsigned int id = glCreateShader(type);
    	const char* src = source.c_str();
    	glShaderSource(id, 1, &src, nullptr);
    	glCompileShader(id);

    	GLint success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cout << "Failed to compile shader\n" << infoLog << std::endl;
        }
    	return id;
    }

    
    void Shader_Test::createShader() {
        ID = glCreateProgram();
    	unsigned int vs = compileShader(GL_VERTEX_SHADER, ParseShader(vertexSource));
    	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, ParseShader(fragmentSource));

    	glAttachShader(ID, vs);
    	glAttachShader(ID, fs);
    	glLinkProgram(ID);
    	glValidateProgram(ID);

    	int success;
        char infoLog[512];
    	glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "Failed to link shader program\n" << infoLog << std::endl;
        }

    	glDeleteShader(vs);
    	glDeleteShader(fs);
    }

    unsigned int &Shader_Test::getID() {
        return ID;
    }

    void Shader_Test::use() { 
        glUseProgram(ID); 
    }

    void Shader_Test::setBool(const std::string &name, bool value) const {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }

    void Shader_Test::setInt(const std::string &name, int value) const { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void Shader_Test::setFloat(const std::string &name, float value) const { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void Shader_Test::setfVec2(const std::string &name, const glm::fvec2 &value) const { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void Shader_Test::setfVec2(const std::string &name, float x, float y) const { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    }

    void Shader_Test::setfVec3(const std::string &name, const glm::fvec3 &value) const { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void Shader_Test::setfVec3(const std::string &name, float x, float y, float z) const { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }

    void Shader_Test::setfVec4(const std::string &name, const glm::fvec4 &value) const { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void Shader_Test::setfVec4(const std::string &name, float x, float y, float z, float w) { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }

    void Shader_Test::setfMat2(const std::string &name, const glm::fmat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader_Test::setfMat3(const std::string &name, const glm::fmat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader_Test::setfMat4(const std::string &name, const glm::fmat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader_Test::setView(const glm::fmat4 &mat) const {
        glUseProgram(ID);
        glUniformMatrix4fv(glGetUniformLocation(ID, "view"), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader_Test::setProjection(const glm::fmat4 &mat) const {
        glUseProgram(ID);
        glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader_Test::setModel(const glm::fmat4 &mat) const {
        glUseProgram(ID);
        glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, GL_FALSE, &mat[0][0]);
    }


}
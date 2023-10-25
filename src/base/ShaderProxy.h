//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_SHADERPROXY_H
#define OPENGLSTUDY_SHADERPROXY_H

#include "common.h"
#include <unordered_map>
#include <fstream>
#include <string>

class ShaderProxy {

public:
    ShaderProxy(const ShaderProxy &rhs) = delete;
    ShaderProxy &operator=(const ShaderProxy &rhs) = delete;

    ShaderProxy(const std::string &vertFilePath, const std::string &fragFilePath) {

        std::ifstream fileVert, fileFrag;
        fileVert.open(vertFilePath, std::ios::in);
        if (!fileVert.is_open()) {
            std::cout << "read vertexShaderPath file failed, " << vertFilePath << std::endl;
            return;
        }
        fileFrag.open(fragFilePath, std::ios::in);
        if (!fileFrag.is_open()) {
            std::cout << "read fragmentShaderPath file failed, " << fragFilePath << std::endl;
            return;
        }

        std::string buf;
        std::string vertexShaderSL;
        std::string fragmentShaderSL;

        while (getline(fileVert, buf)) {
            vertexShaderSL += buf + "\n";
        }
        buf = "";
        while (getline(fileFrag, buf)) {
            fragmentShaderSL += buf + "\n";
        }

        int success;
        char infoLog[512];

        const char *vertexShaderSource = vertexShaderSL.c_str();
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        if (!success) {
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
                      infoLog << std::endl;
            return;

        }

        const char *fragmentShaderSource = fragmentShaderSL.c_str();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        if (!success) {
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
                      infoLog << std::endl;
            return;

        }

//    std::cout << "vertexShaderSource = " << vertexShaderSource << std::endl;
//    std::cout << "fragmentShaderSource = " << fragmentShaderSource << std::endl;

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::LINK_FAILED\n" <<
                      infoLog << std::endl;
            return;
        }

        std::cout << "SHADER COMPILE SUCCESS program = " << shaderProgram << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        fileFrag.close();
        fileVert.close();

        this->mProgramID = shaderProgram;

    }

    ~ShaderProxy() {
        Unbind();
        GLCall(glDeleteProgram(this->mProgramID));
        std::cout << "Shader [" << mProgramID << "] has been unbind and deleted;" << std::endl;
    }

    void Bind() {
        GLCall(glUseProgram(mProgramID));
    }

    void Unbind() {
        GLCall(glUseProgram(0));
    }

    int GetUniformLocation(const std::string &uniformName) {
        int location;
        if (mUniformLocationCache.find(uniformName) != mUniformLocationCache.end()) {
            location = mUniformLocationCache[uniformName];
        } else {
            GLCall(location = glGetUniformLocation(mProgramID, uniformName.c_str()));
            mUniformLocationCache[uniformName] = location;
        }
//        if (location == -1) {
//            std::cout << " uniform [" << uniformName << "] does not exist!" << std::endl;
//        }
//        std::cout << " uniform [" << uniformName << "] location = " << location << std::endl;
        return location;
    }

    inline uint32_t getProgramID() const { return mProgramID; }


    void setUniform4f(const std::string &uniformName, float v1, float v2, float v3, float v4) {
        GLCall(glUniform4f(GetUniformLocation(uniformName), v1, v2, v3, v4));
    }

    void setUniform3f(const std::string &uniformName, float v1, float v2, float v3) {
        GLCall(glUniform3f(GetUniformLocation(uniformName), v1, v2, v3));
    }

    void setUniform1f(const std::string &uniformName, float value) {
        GLCall(glUniform1f(GetUniformLocation(uniformName), value));
    }

    void setUniform1i(const std::string &uniformName, int value) {
        GLCall(glUniform1i(GetUniformLocation(uniformName), value));
    }

    void setUniformMat4f(const std::string &uniformName, const glm::mat4 &matrix) {
        GLCall(glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(matrix)));
    }



private:
    uint32_t mProgramID;
    std::unordered_map<std::string, int> mUniformLocationCache;

};

#endif //OPENGLSTUDY_SHADERPROXY_H

#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include "GL/glew.h"

#include <string>

namespace ndGE {

    /**
     * This class handles the compilation, linking, and usage of a GLSL shader program.
     * Reference: http://www.opengl.org/wiki/Shader_Compilation
     */
    class GLSLProgram
    {
    public:
        GLSLProgram();
        ~GLSLProgram();

        void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

        void linkShaders();

        void addAttribute(const std::string& attributeName);

        GLint getUniformLocation(const std::string& uniformName);

        void use();
        void unuse();
    private:

        int _numAttributes;

        void compileShader(const std::string& filePath, GLuint id);

        GLuint _programID;

        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;
    };

}

#endif // GLSLPROGRAM_H
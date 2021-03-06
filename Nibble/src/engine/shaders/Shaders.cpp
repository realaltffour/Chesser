#include "Shaders.h"

GEngine::Shader::Shader(const std::string vsfile, const std::string fsfile) {
    // std::string vertexCode;
    // std::string fragmentCode;
    // std::ifstream vShaderFile;
    // std::ifstream fShaderFile;
    //
    // vertexCode = GEngine::Files::FileManager::LoadFile(vsfile);
    // fragmentCode = GEngine::Files::FileManager::LoadFile(fsfile);

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.open(vsfile);
    if (vShaderFile.is_open() == false) {
        THROW_ERROR("Error occured Reading Vertex Shader File: " + vsfile,
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
    } else {
#if !defined(SUPPRESS_FILE_SUCCESS)
        Log::info("Read Vertex Shader file: " + vsfile + ". ",
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
#endif
    }

    fShaderFile.open(fsfile);
    if (fShaderFile.is_open() == false) {
        THROW_ERROR("Error Occured Reading Fragment Shader File: " + fsfile,
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
    } else {
#if !defined(SUPPRESS_FILE_SUCCESS)
        Log::info("Read Fragment Shader file: " + fsfile + ". ",
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
#endif
    }
    std::stringstream vstream, fstream;
    vstream << vShaderFile.rdbuf();
    fstream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vstream.str();
    fragmentCode = fstream.str();

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
    GLCall(glCompileShader(vertex));

    GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(vertex, 512, NULL, infoLog));
        THROW_ERROR("Compilation of Vertex Shader for Program Failed.\n" +
                std::string(infoLog),
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
    } else {
#if !defined(SUPPRESS_SHADER_SUCCESS)
        Log::info("Compilation of Vertex Shader for Program Succeeded.",
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
#endif
    }
    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
    GLCall(glCompileShader(fragment));

    GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(fragment, 512, NULL, infoLog));
        THROW_ERROR("Compilation of Fragment Shader for Program Failed.\n" +
                std::string(infoLog),
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
    } else {
#if !defined(SUPPRESS_SHADER_SUCCESS)
        Log::info("Compilation of Fragment Shader for Program Succeeded.",
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
#endif
    }

    // shader program
    this->_prog_id = glCreateProgram();
    GLCall(glAttachShader(this->_prog_id, vertex));
    GLCall(glAttachShader(this->_prog_id, fragment));
    GLCall(glLinkProgram(this->_prog_id));

    GLCall(glGetProgramiv(this->_prog_id, GL_LINK_STATUS, &success));
    if (!success) {
        GLCall(glGetProgramInfoLog(this->_prog_id, 512, NULL, infoLog));
        THROW_ERROR("Linking for Program  failed.\n" + std::string(infoLog),
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
    } else {
#if !defined(SUPPRESS_SHADER_SUCCESS)
        Log::info("Linking for Program Succeeded.",
                Log::GenLogID(__LINE__, __FILE__, "Shader", __func__));
#endif
    }
    GLCall(glDeleteShader(vertex));
    GLCall(glDeleteShader(fragment));
}

GEngine::Shader::~Shader(void) { this->destroy(); }

void GEngine::Shader::bind(void) { GLCall(glUseProgram(this->_prog_id)); }

void GEngine::Shader::unbind(void) { GLCall(glUseProgram(0)); }

void GEngine::Shader::destroy(void) { GLCall(glDeleteProgram(this->_prog_id)); }

int GEngine::Shader::getProgId(void) { return this->_prog_id; }

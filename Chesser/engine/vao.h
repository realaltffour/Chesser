#ifndef VAO_H
#define VAO_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "univ_includes.h"
#include "buffer.h"

namespace VAOs {

struct ShaderAttrib {
    int index;
    GLsizei size;
    GLsizei stride;
    void* offset;
    GLenum type;
    bool isNorm = false;
    bool isEnable = true;
};

class VAO {
public:
    VAO(BufferObject* vbo, vector<ShaderAttrib*> attribs) {
        glGenVertexArrays(1, &ID); 
        glBindVertexArray(ID);
        vbo->bind();
        for (int i = 0; i < attribs.size(); i++)
          this->enableAttrib(attribs[i]);
        glBindVertexArray(0);
    }

    void bind() {
      glBindVertexArray(ID);
    }
    
    void unbind() {
      glBindVertexArray(0);
    }

private:
    void enableAttrib(ShaderAttrib* attrib) {
        glEnableVertexAttribArray(attrib->index);
        glVertexAttribPointer(attrib->index, attrib->size, 
            attrib->type, 
            attrib->isNorm, attrib->stride, attrib->offset);
    }

private:
    GLuint ID;
    BufferObject* _vbo;
    BufferObject* _ibo;
    vector<ShaderAttrib*> _attribs;
};


static std::map<std::string, VAO*> vao;

static void createVAO(std::string name,BufferObject* vbo , vector<ShaderAttrib*> attribs) {
    VAO* new_vao = new VAO(vbo, attribs);
    vao.insert(std::pair<std::string, VAO*>(name, new_vao));
}

}  // namespace VAOs

#endif
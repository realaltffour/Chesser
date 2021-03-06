#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

GEngine::Texture::Texture(std::string file) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imgData = stbi_load(file.c_str(), &this->_imgWidth,
            &this->_imgHeight, &this->_imgComp, 0);
    if (imgData == nullptr) {
        THROW_ERROR("Failed to load texture: " + file,
                Log::GenLogID(__LINE__, __FILE__, "Texture", __func__));
    } else {
#if !defined(SUPPRESS_TEXTURE_SUCCESS)
        Log::info("Loaded Texture: " + file,
                Log::GenLogID(__LINE__, __FILE__, "Texture", __func__));
#endif
    }

    GLCall(glGenTextures(1, &this->_tex_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, this->_tex_id));

    // Optional texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Match texture data format to the image we load
    GLuint texDataFormat = 0;
    if (this->_imgComp == 3)
        texDataFormat = GL_RGB;
    else if (this->_imgComp == 4)
        texDataFormat = GL_RGBA;

    // Send image data to OpenGL
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texDataFormat, this->_imgWidth,
                this->_imgHeight, 0, texDataFormat, GL_UNSIGNED_BYTE,
                imgData));

    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    // Free stbi image data
    stbi_image_free((void*)imgData);
}

GEngine::Texture::Texture(TextureProps prop) {
    if (prop._data == nullptr) {
#if !defined(SUPPRESS_TEXTURE_NULL_WARNING)
        Log::warn("Texture data is null.",
                Log::GenLogID(__LINE__, __FILE__, "Texture", __func__));
#endif
    }

    GLCall(glGenTextures(1, &this->_tex_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, this->_tex_id));

    // Texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, prop._wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, prop._wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, prop._min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, prop._mag_filter);

    GLCall(glTexImage2D(GL_TEXTURE_2D, prop._level, prop._internalFormat,
                prop._width, prop._height, prop._border,
                prop._bufferFormat, prop._type, prop._data));
    if (prop._gen_mipmap) {
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
GEngine::Texture::~Texture(void) { this->destroy(); }

void GEngine::Texture::bind(int index) {
    if (index == -1) {
        GLCall(glActiveTexture(GL_TEXTURE0));
        AddTexSlot(0);
        this->_slot_bound = 0;
    } else {
        GLCall(glActiveTexture(GL_TEXTURE0 + index));
        AddTexSlot(index);
        this->_slot_bound = index;
    }
    GLCall(glBindTexture(GL_TEXTURE_2D, this->_tex_id));
}

void GEngine::Texture::unbind(void) {
    GLCall(glBindTexture(GL_TEXTURE_2D, this->_tex_id));
    RemoveTexSlot(this->_slot_bound);
}

int GEngine::Texture::getImgWidth(void) { return this->_imgWidth; }

int GEngine::Texture::getImgHeight(void) { return this->_imgHeight; }

int GEngine::Texture::getImgCompNum(void) { return this->_imgComp; }

void GEngine::Texture::destroy(void) {
    GLCall(glDeleteTextures(1, &this->_tex_id));
}

#include <glad/gl.h>
#include <stb_image/stb_image.h>

class Texture{
private:
    unsigned int rendererID;
    int width;
    int height;
    int nChannels;

public:
    unsigned int slot;

    Texture(const char* filepath){
        stbi_set_flip_vertically_on_load(1);
        unsigned char* textureData = stbi_load(filepath, &width, &height, &nChannels, 0);
        glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
        this->Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(textureData);
    }

    void Bind(unsigned int slot = 0){
        this->slot = slot;
        glActiveTexture(GL_TEXTURE0 + this->slot);
        glBindTexture(GL_TEXTURE_2D, rendererID);
    }

    void Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    ~Texture(){
        glDeleteTextures(1, &rendererID);
    }
};
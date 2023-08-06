
#include "../headers/texture.hpp"
#include "../headers/img_loader.hpp"


Texture::Texture(const std::string &file_name)
{
    // _texture_target = texture_target;
    _file_name = file_name;
}

bool Texture::load_tex()
{
    if (load_bmp(_file_name, this->_texture_target) != 0)
        exit(-1);
    return (0);
}
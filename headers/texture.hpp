#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#pragma once
#include "render.hpp"

class Texture
{
    private:
        std::string _file_name;
        GLenum      _texture_target;
        GLuint      _texture_obj;

    public:
        Texture(const std::string &file_name);

        bool load_tex();

        void bind_tex(GLenum texture_unit);

};

#endif
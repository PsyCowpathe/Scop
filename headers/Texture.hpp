#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#pragma once
#include "render.hpp"

class Texture
{
    private:
        std::string _file_name;
        // GLenum      _texture_target;
        GLuint      _texture_obj;

        GLuint      _w;
        GLuint      _h;

        uint8_t     *_pixels;


        // render      *_render; // to use the clear() function

    public:
        Texture(const std::string &file_name);

        int check_file();
        void gen_tex();
        bool load_tex();

        // void bind_tex(GLenum texture_unit);

};

#endif
#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#pragma once
#include "render.hpp"

class render;

class Texture
{
    private:
        std::string         _file_name;
        GLenum              _texture_target;
        GLuint              _texture_obj;

        GLuint              _w;
        GLuint              _h;

        unsigned char       *_pixels;

        render              *_render; // to use the clear() function

        void bind_tex(GLenum texture_unit);
    public:
        Texture(GLenum texture_target, const std::string &file_name, render *render);

        void check_file();
        void gen_tex();
        void load_tex();


};

#endif
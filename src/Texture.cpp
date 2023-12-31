
#include "Texture.hpp"
#include "bmp.hpp"


//====================  CONSTRUCTORS  ====================

Texture::Texture(GLenum texture_target, const std::string &file_name, render *render)
{
	_texture_target = texture_target; // GL_TEXTURE
    _file_name = file_name;
	_render = render;

}


//====================  PARSING  ====================

void    Texture::check_file()
{
    uint8_t * datBuff[2] = {nullptr, nullptr}; // Header buffers
	uint8_t* pixels = nullptr; // Pixels
	uint8_t* verif = nullptr; // Pixels

	BITMAPFILEHEADER* bmpHeader = nullptr; // Header
	BITMAPINFOHEADER* bmpInfo   = nullptr; // Info 

    // The file... We open it with it's constructor
	std::ifstream file(this->_file_name, std::ios::binary);
	if(!file)
	{
		std::cout << "Failure to open bitmap file.\n";
		_render->clear();
	}

    // Allocate byte memory that will hold the two headers
	datBuff[0] = new uint8_t[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

    // Construct the values from the buffers
	bmpHeader = (BITMAPFILEHEADER*) datBuff[0];
	bmpInfo   = (BITMAPINFOHEADER*) datBuff[1];

    // Check if the file is an actual BMP file
	if(bmpHeader->bfType != 0x4D42)
	{
		std::cout << "File \"" << this->_file_name << "\" isn't a bitmap file\n";
		_render->clear();
	}

    // First allocate pixel memory
	pixels = new uint8_t[bmpInfo->biSizeImage];
	verif = new uint8_t[bmpInfo->biSizeImage];

	// Go to where image data starts, then read in image data
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)pixels, bmpInfo->biSizeImage);
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)verif, bmpInfo->biSizeImage);

    // Verify that the BMP file is formated correctly for our program
	if (*verif != *pixels)
	{
		std::cout << "BMP format error" << std::endl;
		_render->clear();
	}
	delete[] verif;
    // We're almost done. We have our image loaded, however it's not in the right format.
	// .bmp files store image data in the BGR format, and we have to convert it to RGB.
	// Since we have the value in bytes, this shouldn't be to hard to accomplish
	uint8_t tmpRGB = 0; // Swap buffer
	for (unsigned long i = 0; i < bmpInfo->biSizeImage; i += 3)
	{
		tmpRGB        = pixels[i];
		pixels[i]     = pixels[i + 2];
		pixels[i + 2] = tmpRGB;
	}

	// Set width and height to the values loaded from the file
	this->_w = bmpInfo->biWidth;
	this->_h = bmpInfo->biHeight;

	// Fill member attribute with image data
    this->_pixels = pixels;

	std::cout << "Texture \"" << this->_file_name << "\" successfully loaded.\n";

	delete[] datBuff[0];
	delete[] datBuff[1];

    return;
}

void Texture::gen_tex()
{
    glGenTextures(1, &_texture_obj);             // Generate a texture
	glBindTexture(_texture_target, _texture_obj); // Bind that texture temporarily

	if (_texture_target != GL_TEXTURE_2D)
	{
		std::cout << "Not the right texture format." << std::endl;
		_render->clear();
	}

	glTexParameteri(_texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(_texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(_texture_target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(_texture_target, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(_texture_target, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	GLint mode = GL_RGB;                   // Set the mode
	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	if (_pixels)
	{
		glTexImage2D(_texture_target, 0, mode, _w, _h, 0, mode, GL_UNSIGNED_BYTE, _pixels); // pushes data to GL_TEXTURE_2D
		glGenerateMipmap(_texture_target);
	}
	else
	{
		std::cout << "Something went wrong while generating texture." << std::endl;
		_render->clear();
	}

	// Unbind the GL_TEXTURE_2D texture
	// glBindTexture(_texture_target, 0);

	// Output a successful message
	std::cout << "Texture based on \"" << this->_file_name << "\" successfully generated.\n";

	// Delete remaining buffer.
	delete[] _pixels;
}


//====================  UTILITY  ====================

void Texture::bind_tex(GLenum texture_unit)
{
	glActiveTexture(texture_unit); // 
	glBindBuffer(texture_unit, _texture_obj);
}

void Texture::load_tex()
{
    check_file();
    gen_tex();
	bind_tex(GL_TEXTURE_2D);
}


#include "../headers/Texture.hpp"
#include "../headers/bmp.hpp"


Texture::Texture(GLenum texture_target, const std::string &file_name, render *render)
{
	_texture_target = texture_target; // GL_TEXTURE
    _file_name = file_name;
	_render = render;

}

int    Texture::check_file()
{
    uint8_t * datBuff[2] = {nullptr, nullptr}; // Header buffers
    
	uint8_t* pixels = nullptr; // Pixels

	BITMAPFILEHEADER* bmpHeader = nullptr; // Header
	BITMAPINFOHEADER* bmpInfo   = nullptr; // Info 

    // The file... We open it with it's constructor
	std::ifstream file(this->_file_name, std::ios::binary);
	if(!file)
	{
		std::cout << "Failure to open bitmap file.\n";

		return 1;
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
		return 2;
	}

    // First allocate pixel memory
	pixels = new uint8_t[bmpInfo->biSizeImage];

	// Go to where image data starts, then read in image data
	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)pixels, bmpInfo->biSizeImage);

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

    this->_pixels = pixels;
	_render->_pixels = *pixels;

	// uint8_t i;
	// for (i = 0; i < bmpInfo->biSizeImage; i++)
	// {
	// 	printf("%u/n", _pixels[i]);
	// }
	std::cout << "Texture \"" << this->_file_name << "\" successfully loaded.\n";

	delete[] datBuff[0];
	delete[] datBuff[1];
    
    return (0);
}

void Texture::gen_tex()
{
    glGenTextures(1, &_texture_obj);             // Generate a texture
	glBindTexture(_texture_target, _texture_obj); // Bind that texture temporarily

	if (_texture_target != GL_TEXTURE_2D)
	{
		std::cout << "not the right texture format" << std::endl;
		_render->clear();
		exit(1);
	}

	GLint mode = GL_RGB;                   // Set the mode


	glTexParameteri(_texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(_texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(_texture_target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(_texture_target, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(_texture_target, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	if (_pixels)
	{
		glTexImage2D(_texture_target, 0, mode, _w, _h, 0, mode, GL_UNSIGNED_BYTE, _pixels);
		glGenerateMipmap(_texture_target);
	}

	// Unbind the GL_TEXTURE_2D texture
	// glBindTexture(_texture_target, 0);

	// Output a successful message
	std::cout << "Texture based on \"" << this->_file_name << "\" successfully generated.\n";

	// Delete the two buffers.
	// delete[] datBuff[0];
	// delete[] datBuff[1];
	delete[] _pixels;
}

void Texture::bind_tex(GLenum texture_unit)
{
	glActiveTexture(texture_unit); // 
	glBindBuffer(texture_unit, _texture_obj);
}

bool Texture::load_tex()
{
    if (check_file() != 0)
        exit(-1);
    gen_tex();
	bind_tex(GL_TEXTURE_2D);
    
    return (0);
}
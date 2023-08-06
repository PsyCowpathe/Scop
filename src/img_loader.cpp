#include "../headers/img_loader.hpp"

int load_bmp(const std::string &location, GLuint &texture)
{
    uint8_t * datBuff[2] = {nullptr, nullptr}; // Header buffers

	uint8_t* pixels = nullptr; // Pixels

	BITMAPFILEHEADER* bmpHeader = nullptr; // Header
	BITMAPINFOHEADER* bmpInfo   = nullptr; // Info 

    // The file... We open it with it's constructor
	std::ifstream file(location, std::ios::binary);
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
		std::cout << "File \"" << location << "\" isn't a bitmap file\n";
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
	GLuint w = bmpInfo->biWidth;
	GLuint h = bmpInfo->biHeight;








    /*******************GENERATING TEXTURES*******************/

	glGenTextures(1, &texture);             // Generate a texture
	glBindTexture(GL_TEXTURE_2D, texture); // Bind that texture temporarily

	GLint mode = GL_RGB;                   // Set the mode

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 
	// Create the texture. We get the offsets from the image, then we use it with the image's
	// pixel data to create it.
	glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, pixels);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Output a successful message
	std::cout << "Texture \"" << location << "\" successfully loaded.\n";

	// Delete the two buffers.
	delete[] datBuff[0];
	delete[] datBuff[1];
	delete[] pixels;

	return 0; // Return success code 
}
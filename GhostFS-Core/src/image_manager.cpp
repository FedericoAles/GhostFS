#include "image_manager.h"
#include <iostream>

// CONFIGURACIÓN DE STB (NO TOCAR)
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"

std::vector<Pixel> ImageManager::load(const std::string& filepath, int& width, int& height) {
  int channels;
  unsigned char* raw_data = stbi_load(filepath.c_str(), &width, &height, &channels, 3); // Guarda la imagen como una cadena de chars a modo [R, G, B, R, G, ...].
                                                                                        // Y asigna valores a width y height.
  if (!raw_data) {
    std::cerr << "[ERROR] No se pudo abrir la imagen: " << filepath << std::endl;
    return {};
  }

  // Preparamos el vector
  std::vector<Pixel> pixels;
  int image_size = width * height;
  pixels.reserve(image_size);
  
  for (int i = 0; i < image_size; i++) {
    int index = i * 3;
    Pixel p = {                 // Llenamos los canales RGB
        raw_data[index],        // R
        raw_data[index + 1],    // G
        raw_data[index + 2]};   // B
    pixels.push_back(p);        // Agregamos el pixel al vector dinamico de pixeles
  }

  stbi_image_free(raw_data);    // Liberamos la memoria de C (muy importante)
  return pixels;                // Devolvemos la imagen en un formato el cual si podemos editar con nuestras funciones.
}

bool ImageManager::save(const std::string& filepath, const std::vector<Pixel>& pixels, int width, int height) {
  std::vector<unsigned char> raw_data;
  raw_data.reserve(width * height * 3);  // El 3 es porque necesitamos 3 espacios por cada pixel (RGB)
  
  for (const Pixel& p : pixels) {
     raw_data.push_back(p.r);
     raw_data.push_back(p.g);
     raw_data.push_back(p.b);
  }

  int result = stbi_write_png(filepath.c_str(), width, height, 3, raw_data.data(), width * 3);

  return result != 0;
}
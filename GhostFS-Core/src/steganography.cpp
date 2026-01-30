#include "steganography.h"
#include <iostream>

bool Steganography::hide_data(std::vector<Pixel>& image, const std::vector<uint8_t>& data) {
  uint32_t file_size = data.size();

  if (image.size() < (file_size + HEADER) * 8) { // Cada byte consume 8 pixeles. En el header se indica el tamaño del archivo.
    std::cout << "[ERROR] - El tamaño del archivo es superior al de la imagen." << std::endl;
    return false;
  } 
  
  int pixel_index = 0;
  for (int i = 0; i < 4; i++) {
    uint8_t byte_to_hide = (file_size >> i * 8) & 0xFF;  // Voy tomando y aislando byte x byte.
    hide_byte(image, pixel_index , byte_to_hide);
    pixel_index += 8;
  }
  for (uint32_t i = 0; i < file_size; i++) {
    hide_byte(image, pixel_index , data[i]);
    pixel_index += 8;
  }
  return true;
}

std::vector<uint8_t> Steganography::read_data(const std::vector<Pixel>& image) {
  uint32_t extracted_size = 0;
  int pixel_index = 0;

  for (int i = 0; i < 4; i++) {
    uint8_t byte_read = read_byte(image, pixel_index);
    extracted_size = extracted_size | (byte_read << i * 8);
    pixel_index += 8;
  }
  if (pixel_index + (extracted_size * 8) > image.size()) {
    std::cerr << "[ERROR] Header corrupto o tamaño invalido detectado." << std::endl;
    return {}; // Retornar vector vacío
  }

  std::vector<uint8_t> result;
  result.reserve(extracted_size); // Optimización

  for (uint32_t i = 0; i < extracted_size; i++) {
    uint8_t byte_read = read_byte(image, pixel_index);
    result.push_back(byte_read);
    pixel_index += 8;
  }

  return result;
}

void Steganography::hide_byte(std::vector<Pixel>& pixels, int start_index, uint8_t byte) {
  // El byte (uint8_t) tiene 8 bits.
  // Necesitamos meter cada uno de esos bits en el LSB del componente .r (rojo) de los siguientes 8 píxeles. 

  for (int i = 0; i < 8; ++i) {
    int bit_to_hide = (byte >> i) & 1;  // El operador >> mueve el bit 'i' a la posicion del LSB, luego & 1 aplica solo a ese bit.

    Pixel& current_pixel = pixels[start_index + i]; // Me guardo una referencia a la ubicacion real del pixel actual, no una copia.

    current_pixel.r = current_pixel.r & 0xFE; // Limpiar el LSB del canal rojo del píxel.
    current_pixel.r = current_pixel.r | bit_to_hide; // Insertar el 'bit_to_hide' en esa posición.
  }
}

uint8_t Steganography::read_byte(const std::vector<Pixel>& pixels, int start_index){
  uint8_t byte_read = 0;
  for (int i = 0; i < 8; ++i) {
    int bit_read = pixels[start_index + i].r & 0x01; // Aislamos el LSB del canal rojo del pixel
    byte_read = byte_read | (bit_read << i); // Ubicamos el bit en la posicion correcta
  }
  return byte_read;
}
#include "steganography.h"
#include <bitset> // Útil para ver bits

void Steganography::hide_message(std::vector<Pixel>& image, const std::string& message) {
  std::cout << "[INFO] Iniciando ocultamiento del mensaje: " << message << std::endl;

  // Chequeo básico de capacidad
  if (image.size() < message.length() * 8) {
    std::cerr << "[ERROR] La imagen es muy chica para este mensaje." << std::endl;
    return;
  }

  int pixel_index = 0;
  for (char c : message) {
    hide_char(image, pixel_index, c);
    pixel_index += 8; // Avanzamos 8 píxeles (1 bit por píxel, por ahora)
  }
    
  std::cout << "[INFO] Mensaje oculto exitosamente." << std::endl;
}


void Steganography::hide_char(std::vector<Pixel>& pixels, int start_index, char character) {
  // El caracter (char) tiene 8 bits.
  // Necesitamos meter cada uno de esos bits en el LSB del componente .r (rojo) de los siguientes 8 píxeles. 

  for (int i = 0; i < 8; ++i) {
    int bit_index = 7 - i; // El indice de bits va al reves, de MSB a LSB. Es decir, bit[7] seria el de la derecha de todo
    int bit_to_hide = (character >> bit_index) & 1;  // El operador >> mueve el bit 'i' a la posicion del LSB, luego & 1 aplica solo a ese bit.

    Pixel& current_pixel = pixels[start_index + i]; // Me guardo una referencia a la ubicacion real del pixel actual, no una copia.

    current_pixel.r = current_pixel.r & 0b11111110; // Limpiar el LSB del canal rojo del píxel (podria usar 0xFE, pero lo considero mas expresivo asi).
    current_pixel.r = current_pixel.r | bit_to_hide; // Insertar el 'bit_to_hide' en esa posición.
  }
}

void Steganography::print_binary(unsigned char value) {
  std::cout << std::bitset<8>(value) << " ";
}
#include <vector>
#include <cstdint>
#include <string>
#include "pixel.h"

#define HEADER 4

class Steganography {
public:
  // DESAFÍO 1: Ocultar cualquier archivo (vector de bytes)
  static void hide_data(std::vector<Pixel>& image, const std::vector<uint8_t>& data);

  // DESAFÍO 2: Recuperar esos bytes
  static std::vector<uint8_t> read_data(const std::vector<Pixel>& image);

private:
  // Auxiliares (Ya las tienes, solo cambia char por uint8_t si quieres ser estricto)
  static void hide_byte(std::vector<Pixel>& pixels, int start_index, uint8_t byte);
  static uint8_t read_byte(const std::vector<Pixel>& pixels, int start_index);
};
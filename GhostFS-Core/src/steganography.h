#include <vector>
#include <cstdint>
#include <string>
#include "pixel.h"

#define HEADER 4

class Steganography {
public:
  static bool hide_data(std::vector<Pixel>& image, const std::vector<uint8_t>& data);

  static std::vector<uint8_t> read_data(const std::vector<Pixel>& image);

private:
  static void hide_byte(std::vector<Pixel>& pixels, int start_index, uint8_t byte);
  static uint8_t read_byte(const std::vector<Pixel>& pixels, int start_index);
};
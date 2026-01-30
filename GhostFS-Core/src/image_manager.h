#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <vector>
#include <string>
#include "pixel.h"

class ImageManager {
public:
  static std::vector<Pixel> load(const std::string& filepath, int& width, int& height);

  static bool save(const std::string& filepath, const std::vector<Pixel>& pixels, int width, int height);
};

#endif
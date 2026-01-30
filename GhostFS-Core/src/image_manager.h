#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <vector>
#include <string>
#include "pixel.h"

class ImageManager {
public:
  // Carga una imagen desde 'filepath'.
  // Rellena width y height con las dimensiones reales.
  // Retorna el vector de pixeles listo para usar.
  static std::vector<Pixel> load(const std::string& filepath, int& width, int& height);

  // Guarda el vector de pixeles en un archivo PNG (sin pérdida).
  // Retorna true si salió bien.
  static bool save(const std::string& filepath, const std::vector<Pixel>& pixels, int width, int height);
};

#endif
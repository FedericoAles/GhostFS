#include <iostream>
#include <vector>
#include <string>
#include "image_manager.h"
#include "file_manager.h"
#include "steganography.h"

// GhostFS CLI
// Uso: ./ghostfs [hide/read] [imagen_portadora] [archivo_secreto/output] [imagen_salida]

void print_usage() {
  std::cout << "Uso incorrecto.\n";
  std::cout << "OCULTAR: ./bin/GhostLab.exe hide <imagen.png> <secreto.pdf> <salida.png>\n";
  std::cout << "LEER:    ./bin/GhostLab.exe read <imagen_con_secreto.png> <recuperado.pdf>\n";
}

int main(int argc, char* argv[]) {
  if (argc < 4) {
    print_usage();
    return 1;
  }

  std::string mode = argv[1];        // "hide" o "read"
  std::string image_path = argv[2];  // La imagen base
  std::string file_path = argv[3];   // El archivo a esconder o a recuperar


  // ------- MODO OCULTAR -------
  if (mode == "hide") {
    if (argc != 5) { // Necesitamos un argumento extra para el nombre de salida
      print_usage();
      return 1;
    }
    std::string output_image_path = argv[4];

    std::cout << "[INFO] Cargando imagen portadora...\n";
    int width, height;
    std::vector<Pixel> image = ImageManager::load(image_path, width, height);
    if (image.empty()) return 1;

    std::cout << "[INFO] Leyendo archivo secreto...\n";
    std::vector<uint8_t> secret_data = FileManager::read_file(file_path);
    if (secret_data.empty()) {
      std::cerr << "[ERROR] Archivo secreto vacio o no encontrado.\n";
      return 1;
    }

    std::cout << "[INFO] Ocultando " << secret_data.size() << " bytes...\n";

    if (Steganography::hide_data(image, secret_data)) {
      if (ImageManager::save(output_image_path, image, width, height)) {
        std::cout << "[EXITO] Secreto guardado en: " << output_image_path << "\n";
      } else {
        std::cerr << "[ERROR] Fallo al guardar imagen.\n";
      }
    } else {
      std::cerr << "[ERROR] La imagen es muy chica para este archivo.\n";
    }


  // ------- MODO LEER -------
  } else if (mode == "read") {
    std::cout << "[INFO] Cargando imagen...\n";
    int width, height;
    std::vector<Pixel> image = ImageManager::load(image_path, width, height);
    if (image.empty()) return 1;

    std::cout << "[INFO] Extrayendo datos...\n";

    std::vector<uint8_t> recovered_data = Steganography::read_data(image);

    if (!recovered_data.empty()) {
      if (FileManager::write_file(file_path, recovered_data)) {
        std::cout << "[EXITO] Archivo recuperado: " << file_path << "\n";
      } else {
        std::cerr << "[ERROR] Fallo al escribir archivo en disco.\n";
      }
    } else {
      std::cerr << "[ERROR] No se encontraron datos validos o magic number incorrecto.\n";
    }

  } else {
    print_usage();
    return 1;
  }

  return 0;
}
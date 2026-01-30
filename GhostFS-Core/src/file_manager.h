#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>
#include <cstdint>

class FileManager {
public:
  // Lee un archivo binario del disco y devuelve sus bytes crudos
  static std::vector<uint8_t> read_file(const std::string& filepath);

  // Escribe bytes crudos en un archivo en el disco
  static bool write_file(const std::string& filepath, const std::vector<uint8_t>& data);
};

#endif
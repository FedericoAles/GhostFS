#include "file_manager.h"
#include <fstream>
#include <iostream>

std::vector<uint8_t> FileManager::read_file(const std::string& filepath) {
  // Abrir archivo en modo binario (std::ios::binary) y al final (std::ios::ate)
  // 'ate' nos permite ver el tamaño inmediatamente.
  std::ifstream file(filepath, std::ios::binary | std::ios::ate); // ifstream: input file stream, permite leer datos.
                                                                  // std::ios::binary: no se modifican los bytes del archivo (conversiones de \n\r a \n por ej.).
  if (!file) {return {};}                                         // std::ios::ate: at the end, abrir el archivo y saltar al final.

  std::streamsize size = file.tellg(); // tellg: tell get pointer, al estar parados al final nos dice el tamaño del archivo.
  file.seekg(0, std::ios::beg);        // seekg: seek get pointer, mueve el puntero. Volvemos el cursor al principio para leer.

  std::vector<uint8_t> buffer(size);

  if (file.read(reinterpret_cast<char*>(buffer.data()), size)) { // Leemos y guardamos en la data del buffer.
    return buffer;
  }

  return {}; // Si falló la lectura
}

bool FileManager::write_file(const std::string& filepath, const std::vector<uint8_t>& data) {
  std::ofstream file(filepath, std::ios::binary); // ofstream: output file stream, permite escribir datos

  if (!file) {return false;}

  file.write(reinterpret_cast<const char*>(data.data()), data.size()); // Volcamos la data en el disco, en el archivo.
    
  return true;
}
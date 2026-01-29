#include <iostream>
#include <vector>
#include <iomanip> // Para imprimir en HEX
#include "steganography.h"

// Función auxiliar para ver los bytes en consola
void print_hex(const std::string& label, const std::vector<uint8_t>& data) {
  std::cout << label << ": { ";
  for (uint8_t byte : data) {
    // Imprime en formato Hexadecimal
    std::cout << "0x" << std::hex << std::uppercase << (int)byte << " ";
  }
  std::cout << "}" << std::dec << std::endl; // Volver a decimal
}

int main() {
  std::cout << "=== GHOST-FS: PRUEBA DE DATOS BINARIOS ===" << std::endl;

  // 1. SIMULAMOS UN ARCHIVO
  std::vector<uint8_t> secret_file = { 0xA1, 0xB2, 0xC3, 0xD4, 0xFF };
  
  print_hex("Archivo Original", secret_file);

  // 2. PREPARAR LA IMAGEN
  std::vector<Pixel> image(100, {0, 0, 0}); 
  
  std::cout << "\n[INFO] Ocultando datos..." << std::endl;
  Steganography::hide_data(image, secret_file);

  
  std::cout << "[INFO] Intentando recuperar datos..." << std::endl;
  std::vector<uint8_t> recovered_file = Steganography::read_data(image); // = ... (completar)

  print_hex("Archivo Recuperado", recovered_file);

  if (secret_file == recovered_file) { 
    std::cout << "\n[EXITO] Integridad verificada. Los archivos son identicos." << std::endl;
  } else {
    std::cout << "\n[ERROR] Los datos no coinciden o el tamaño esta mal." << std::endl;
  }

  return 0;
}
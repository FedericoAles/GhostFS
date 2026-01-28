#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

// Simulación de un píxel (3 bytes: R, G, B)
struct Pixel {
    uint8_t r, g, b;
};

// Clase estática para manejar la lógica de ocultamiento
class Steganography {
public:
    // Función principal: Esconde un mensaje en un vector de Píxeles
    static void hide_message(std::vector<Pixel>& image, const std::string& message);

    // Función auxiliar (Tu reto): Esconde 1 solo caracter en 8 Píxeles
    static void hide_char(std::vector<Pixel>& pixels, int start_index, char character);
    
    // Función de utilidad para ver binario (para debuggear)
    static void print_binary(unsigned char value);
};

#endif
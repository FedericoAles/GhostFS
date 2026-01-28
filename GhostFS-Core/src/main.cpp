#include <iostream>
#include <vector>
#include "steganography.h"

int main() {
    // 1. SIMULACIÓN: Creamos una "Imagen Falsa" de 16 píxeles negros (R=0, G=0, B=0)
    // Usamos un vector para simular la memoria de la imagen.
    std::vector<Pixel> dummy_image(16, {0, 0, 0});

    std::cout << "=== PRUEBA DE LABORATORIO GHOST-FS ===" << std::endl;
    std::cout << "Mensaje a esconder: 'A' (ASCII 65)" << std::endl;
    std::cout << "Binario esperado:   0 1 0 0 0 0 0 1" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    // 2. EJECUCIÓN: Llamamos a tu lógica (la que vas a escribir en steganography.cpp)
    Steganography::hide_message(dummy_image, "A");

    std::cout << "\n=== RESULTADO DE LOS PIXELES (CANAL ROJO) ===" << std::endl;
    
    // 3. VALIDACIÓN: Verificamos los primeros 8 píxeles.
    // Si hiciste bien la tarea, el LSB del rojo debería coincidir con los bits de 'A'.
    for(int i = 0; i < 8; i++) {
        int valor_rojo = (int)dummy_image[i].r;
        
        std::cout << "Pixel " << i << " | Rojo: " << valor_rojo;
        
        // Imprimimos en binario para ver qué pasó
        std::cout << " | Binario: ";
        Steganography::print_binary(dummy_image[i].r);
        
        // Chequeo visual simple
        if (i == 7 && valor_rojo == 1) std::cout << " <--- FINAL (Bit 1)";
        else if (i == 1 && valor_rojo == 1) std::cout << " <--- INICIO (Bit 1)";
        
        std::cout << std::endl;
    }

    return 0;
}
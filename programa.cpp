#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

#define ANCHO 800
#define ALTO 600
#define ESCALA_X 40 // Nueva escala horizontal
#define ESCALA_Y 30 // Nueva escala vertical
#define ORIGEN_X (ANCHO / 2)
#define ORIGEN_Y (ALTO / 2)

using namespace std;

// Clase para manejar la imagen BMP
class Grafico {
    vector<unsigned char> pixeles;

public:
    Grafico() : pixeles(ANCHO * ALTO * 3, 255) {} // Fondo blanco

    void pintarPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
        if (x >= 0 && x < ANCHO && y >= 0 && y < ALTO) {
            int indice = (y * ANCHO + x) * 3;
            pixeles[indice] = b;
            pixeles[indice + 1] = g;
            pixeles[indice + 2] = r;
        }
    }

    void guardar(const string &nombreArchivo) {
        ofstream archivo(nombreArchivo, ios::binary);
        if (!archivo) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }

        // Encabezado BMP
        unsigned char encabezado[54] = {
            0x42, 0x4D, 54 + ANCHO * ALTO * 3, 0, 0, 0, 54, 0, 0, 0, 40, 0, 0, 0,
            (unsigned char)(ANCHO & 0xFF), (unsigned char)((ANCHO >> 8) & 0xFF), 0, 0,
            (unsigned char)(ALTO & 0xFF), (unsigned char)((ALTO >> 8) & 0xFF), 0, 0, 1, 0, 24, 0};

        archivo.write(reinterpret_cast<char *>(encabezado), 54);
        archivo.write(reinterpret_cast<char *>(pixeles.data()), pixeles.size());
        archivo.close();
    }
};

// Función para evaluar funciones simples como sin(x), cos(x), etc.
double calcularFuncion(const string &nombre, double x) {
    if (nombre == "sin") return sin(x);
    if (nombre == "cos") return cos(x);
    if (nombre == "tan") return tan(x);
    return 0.0;
}

// Procesar la entrada y calcular el valor
double procesarEntrada(const string &funcion, double x) {
    if (funcion == "sin(x)") return sin(x);
    if (funcion == "cos(x)") return cos(x);
    if (funcion == "tan(x)") return tan(x);
    return 0.0; // Si no coincide, devolver 0
}

int main() {
    string funcion;
    cout << "Ingresa la funcion a graficar (ejemplo: sin(x), cos(x), tan(x)): ";
    getline(cin, funcion);

    Grafico grafico;

    // Dibujar ejes
    for (int x = 0; x < ANCHO; x++) grafico.pintarPixel(x, ORIGEN_Y, 0, 0, 0);
    for (int y = 0; y < ALTO; y++) grafico.pintarPixel(ORIGEN_X, y, 0, 0, 0);

    // Dibujar la función
    for (int px = 0; px < ANCHO; px++) {
        double x = (px - ORIGEN_X) / (double)ESCALA_X; // Usar nueva escala horizontal
        double y = procesarEntrada(funcion, x);
        int py = ORIGEN_Y - (int)(y * ESCALA_Y); // Usar nueva escala vertical
        grafico.pintarPixel(px, py, 255, 0, 0); // Píxel rojo
    }

    grafico.guardar("grafica_imagen.bmp");
    cout << "\nLa grafica se ha guardado como 'grafica_imagen.bmp'." << endl;

    return 0;
}

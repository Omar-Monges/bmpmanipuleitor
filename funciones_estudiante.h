#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED

#include "constantes.h"

int solucion(int argc, char* argv[]);

typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} t_pixel;
typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;
    unsigned int comienzoImagen;
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundida;
} t_metadata;

void dumpHex(FILE *archivo);
void extraerMetadata(FILE *archivo, t_metadata *dataP);

int escalaDeGrises(char *nombreImagenIn);
int tonalidadAzul(char *nombreImagenIn);
int tonalidadVerde(char *nombreImagenIn);
int tonalidadRoja(char *nombreImagenIn);
int aumentarContraste(char *nombreImagenIn);
int reducirContraste(char *nombreImagenIn);

int recortar(char *nombreImagenIn);

#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED

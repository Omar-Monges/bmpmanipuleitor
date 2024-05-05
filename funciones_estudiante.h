#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include <stdbool.h>
#include "constantes.h"

#define PREPARAR_ARCHIVO_SALIDA(pathOut) FILE *imagenOut = fopen((pathOut), "wb")
#define ESCALA_DE_GRISES_OK 30
#define TONALIDAD_OK 40
#define RECORTAR_OK 50
#define ROTAR_OK 60
#define CONTRASTE_OK 70

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

/*
typedef struct
{
    bool seCompletoEscalaDeGrises;
    bool seCompletoTonalidadRoja;
    bool seCompletoTonalidadVerde;
    bool seCompletoTonalidadAzul;
    bool seCompletoAumentarContraste;   //Implementacion para no repetir operaciones
    bool seCompletoReducirContraste;
    bool seCompletoRecortar;
    bool seCompletoRotarDerecha;
    bool seCompletoRotarIzquierda;
} t_statusOperation;
*/

void dumpHex(FILE *archivo);
void extraerMetadata(FILE *archivo, t_metadata *dataP);

int escalaDeGrises(FILE *imagenIn);
int tonalidadAzul(FILE *imagenIn);
int tonalidadVerde(FILE *imagenIn);
int tonalidadRoja(FILE *imagenIn);
int aumentarContraste(FILE *imagenIn);
int reducirContraste(FILE *imagenIn);

int recortar(FILE *imagenIn);

#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED

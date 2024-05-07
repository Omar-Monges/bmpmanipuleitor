#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "constantes.h"

#define PREPARAR_ARCHIVO_SALIDA(pathOut) FILE *imagenOut = fopen((pathOut), "wb")
#define true 1
#define false 0

//operaciones
#define NEGATIVO "--negativo"
#define ESCALA_DE_GRISES "--escala-de-grises"
#define AUMENTAR_CONTRASTE "--aumentar-contraste"
#define REDUCIR_CONTRASTE "--reducir-contraste"
#define TONALIDAD_AZUL "--tonalidad-azul"
#define TONALIDAD_VERDE "--tonalidad-verde"
#define TONALIDAD_ROJA "--tonalidad-roja"
#define RECORTAR "--recortar"
#define ROTAR_DERECHA "--rotar-derecha"
#define ROTAR_IZQUIERDA "--rotar-izquierda"
#define COMODIN "--comodin"
#define DUMP "--dump"
#define METADATA "--metadata"

//Codigos de resultados
/*
#define TODO_OK 0
#define ARCHIVO_NO_ENCONTRADO 10
#define NO_SE_PUEDE_CREAR_ARCHIVO 20
*/
#define ESCALA_DE_GRISES_OK 30
#define TONALIDAD_OK 40
#define RECORTAR_OK 50
#define ROTAR_OK 60
#define CONTRASTE_OK 70
#define NEGATIVO_OK 80
#define COMODIN_OK 90

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

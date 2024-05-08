#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED
#include "constantes.h"

#define PREPARAR_ARCHIVO_SALIDA(pathOut) FILE *imagenOut = fopen((pathOut), "wb")
#define true 1
#define false 0
#define CANT_COMANDOS 13

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
#define TODO_BIEN 100
#define NO_ENCONTRE_ARCHIVO 110
#define NO_PUDE_CREAR_ARCHIVO 120
#define NO_ES_ARCHIVO_BMP 130
#define REPETIDO 140

#define NEGATIVO_OK 0
#define ESCALA_DE_GRISES_OK 1
#define AUMENTAR_CONTRASTE_OK 2
#define REDUCIR_CONTRASTE_OK 3
#define TONALIDAD_AZUL_OK 4
#define TONALIDAD_VERDE_OK 5
#define TONALIDAD_ROJA_OK 6
#define RECORTAR_OK 7
#define ROTAR_DERECHA_OK 8
#define ROTAR_IZQUIERDA_OK 9
#define COMODIN_OK 10
#define DUMP_OK 11
#define METADATA_OK 12

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
typedef struct
{
    unsigned int status[CANT_COMANDOS];
    char *operaciones[50];
    unsigned int numOperaciones;
    char *nombreImagen;
} t_parametros;

int esOperacion(const char *operacionValida, const char *operacion);
int seRepite(const t_parametros *param, const int operacion);
void initComandos(t_parametros *comandos, const int cantOperacionesValidas);
int comoUsar();
int esArchivoBmp(FILE *img);
int minmax(int valor, int minimo, int maximo);
void extraerMetadata(FILE *archivo, t_metadata *dataP);

int dumpHex(FILE *archivo);
int negativo(FILE *imagenIn);
int escalaDeGrises(FILE *imagenIn);
int tonalidadAzul(FILE *imagenIn);
int tonalidadVerde(FILE *imagenIn);
int tonalidadRoja(FILE *imagenIn);
int aumentarContraste(FILE *imagenIn);
int reducirContraste(FILE *imagenIn);
int recortar(FILE *imagenIn);
int rotarIzquierda(FILE *imagenIn);
int rotarDerecha(FILE *imagenIn);
int comodin(FILE *imagenIn);
int mostrarMetadata(FILE *archivo);
int resultado(const int res, const char comando[]);

#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED

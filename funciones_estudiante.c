/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    (Sólo para grupos de tres integrantes)
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "constantes.h"
#include "funciones_estudiante.h"


void dumpHex(FILE *archivo)
{
    unsigned int i = 0, leido;
    while(!feof(archivo))
    {
        leido = fgetc(archivo);
        printf("byte:%d hexa: %x\n", i, leido);
        i++;
    }
}

void copiandoCabecera(FILE *in, FILE *out, unsigned int comienzoImagen)
{
    int i;
    unsigned char byte;
    //copiando data hasta comienzo de la imagen
    for(i = 0; i < comienzoImagen; i++)
    {
        fread(&byte, sizeof(unsigned char), 1, in);
        fwrite(&byte, sizeof(unsigned char), 1, out);
    }
}

void extraerMetadata(FILE *archivo, t_metadata *dataP)
{
    fseek(archivo, 2, SEEK_SET);
    fread(&dataP->tamArchivo, 4, 1, archivo);

    fseek(archivo, 10, SEEK_SET);
    fread(&dataP->comienzoImagen, 4, 1, archivo);
    fread(&dataP->tamEncabezado, 4, 1, archivo);

    fseek(archivo, 18, SEEK_SET);
    fread(&dataP->ancho, 4, 1, archivo);
    fread(&dataP->alto, 4, 1, archivo);

    fseek(archivo, 28, SEEK_SET);
    fread(&dataP->profundida, 2, 1, archivo);
    rewind(archivo);
}
int escalaDeGrises(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    unsigned char promedio;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_escala-de-grises.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;

    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < metaP.alto; y++)
    {
        for(x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calculo el promedio para la escala de grises
            promedio = (pixel.red + pixel.green + pixel.blue) / 3;
            //modifico los valores para la imagen de salida
            pixel.red = promedio;
            pixel.green = promedio;
            pixel.blue = promedio;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return ESCALA_DE_GRISES_OK;
}
int tonalidadAzul(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    unsigned char aumetaBlue;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_tonalidad-azul.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < metaP.alto; y++)
    {
        for(x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta al 50% el azul
            aumetaBlue = pixel.blue > 170 ? 255 : pixel.blue * 1.5;
            //modifico los valores para la imagen de salida
            pixel.blue = aumetaBlue;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return TONALIDAD_OK;
}

int tonalidadVerde(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    unsigned char aumeta;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_tonalidad-verde.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < metaP.alto; y++)
    {
        for(x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta al 50% el azul
            aumeta = pixel.green > 170 ? 255 : pixel.green * 1.5;
            //modifico los valores para la imagen de salida
            pixel.green = aumeta;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return TONALIDAD_OK;
}


int tonalidadRoja(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    unsigned char aumeta;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_tonalidad-roja.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < metaP.alto; y++)
    {
        for(x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta
            aumeta = pixel.red > 170 ? 255 : pixel.red * 1.5;
            //modifico los valores para la imagen de salida
            pixel.red = aumeta;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return TONALIDAD_OK;
}


int aumentarContraste(FILE *imagenIn)
{
    //Declaracion de variables
    float factorAumento;
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul, promedio, x, y;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_aumentar-contraste.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen
    for (y = 0; y < metaP.alto; y++)
    {
        for(x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calcular promedio
            promedio = (pixel.red + pixel.green + pixel.blue) / 3;
            //Si el promedio es mayor a 127 aumentamos sino reducimos
            if(promedio > 127)
            {
                factorAumento = 1.25;
                nuevoRojo = pixel.red * factorAumento;
                nuevoVerde = pixel.green * factorAumento;
                nuevoAzul = pixel.blue * factorAumento;
            }
            else
            {
                factorAumento = 0.85;
                nuevoRojo = pixel.red * factorAumento;
                nuevoVerde = pixel.green * factorAumento;
                nuevoAzul = pixel.blue * factorAumento;
            }
            pixel.red = (nuevoRojo > 255) ? 255 : nuevoRojo;
            pixel.green = (nuevoVerde > 255) ? 255 : nuevoVerde;
            pixel.blue = (nuevoAzul > 255) ? 255 : nuevoAzul;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return CONTRASTE_OK;
}


int reducirContraste(FILE *imagenIn)
{
    //Declaracion de variables
    float factorAumento;
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul, promedio, x, y;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_reducir-contraste.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < metaP.alto; y++)
    {
        for(x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calcular promedio
            promedio = (pixel.red + pixel.green + pixel.blue) / 3;

            //Si el promedio es mayor a 127 reducimos sino aumentamos
            if(promedio > 127)
            {
                factorAumento = 0.85;
                nuevoRojo = pixel.red * factorAumento;
                nuevoVerde = pixel.green * factorAumento;
                nuevoAzul = pixel.blue * factorAumento;
            }
            else
            {
                factorAumento = 1.25;
                nuevoRojo = pixel.red * factorAumento;
                nuevoVerde = pixel.green * factorAumento;
                nuevoAzul = pixel.blue * factorAumento;
            }
            pixel.red = (nuevoRojo > 255) ? 255 : nuevoRojo;
            pixel.green = (nuevoVerde > 255) ? 255 : nuevoVerde;
            pixel.blue = (nuevoAzul > 255) ? 255 : nuevoAzul;
            //escribir en imagenOut
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return CONTRASTE_OK;
}

int recortar(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int mitadAlto, mitadAncho, x, y, i, fila, col;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_recortar.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);

    //copiando data hasta comienzo de la imagen
    for(i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        if(i == 2)
        {
            unsigned int tam;
            fread(&tam, 4, 1, imagenIn);
            tam = tam >> 2;
            fwrite(&tam, 4, 1, imagenOut);
            i += 4;
        }
        if(i == 18)
        {
            int unsigned ancho;
            fread(&ancho, 4, 1, imagenIn);
            ancho = ancho >> 1;
            fwrite(&ancho, 4, 1, imagenOut);
            i += 4;
        }
        if(i == 22)
        {
            int unsigned alto;
            fread(&alto, 4, 1, imagenIn);
            alto = alto >> 1;
            fwrite(&alto, 4, 1, imagenOut);
            i += 4;
        }

        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    mitadAlto = metaP.alto >> 1;
    mitadAncho = metaP.ancho >> 1;
    t_pixel imagenOriginal[metaP.alto][metaP.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(fila = 0; fila < metaP.alto; fila++)
    {
        for(col = 0; col < metaP.ancho; col++)
        {
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            imagenOriginal[fila][col] = pixel;
        }
    }
    //Recortando
    for (y = 0; y < mitadAlto ; y++)
    {
        for(x = 0; x < mitadAncho; x++)
        {
            fwrite(&imagenOriginal[y][x], sizeof(t_pixel), 1, imagenOut);
        }
    }
    return RECORTAR_OK;
}

int rotarIzquierda(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int fila, col;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_rotar-izquierda.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando cagecera para rotar: ancho y alto
    fseek(imagenOut, 18, SEEK_SET);
    fwrite(&metaP.alto, sizeof(metaP.alto), 1, imagenOut);
    fwrite(&metaP.ancho, sizeof(metaP.ancho), 1, imagenOut);
    fseek(imagenOut, metaP.comienzoImagen, SEEK_SET);

    t_pixel imagenOriginal[metaP.alto][metaP.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(fila = 0; fila < metaP.alto; fila++)
    {
        for(col = 0; col < metaP.ancho; col++)
        {
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            imagenOriginal[fila][col] = pixel;
        }
    }
    for(fila = 0; fila < metaP.ancho; fila++)
    {
        for(col = 0; col < metaP.alto; col++)
            fwrite(&imagenOriginal[metaP.alto - 1 - col][fila], sizeof(t_pixel), 1, imagenOut);
    }

    fclose(imagenOut);
    return ROTAR_OK;
}
int rotarDerecha(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int fila, col;
    t_metadata metaP;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_rotar-derecha.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_SE_PUEDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando cagecera para rotar: ancho y alto
    fseek(imagenOut, 18, SEEK_SET);
    fwrite(&metaP.alto, sizeof(metaP.alto), 1, imagenOut);
    fwrite(&metaP.ancho, sizeof(metaP.ancho), 1, imagenOut);
    fseek(imagenOut, metaP.comienzoImagen, SEEK_SET);

    t_pixel imagenOriginal[metaP.alto][metaP.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(fila = 0; fila < metaP.alto; fila++)
    {
        for(col = 0; col < metaP.ancho; col++)
        {
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            imagenOriginal[fila][col] = pixel;
        }
    }
    // rotando imagen
    for(fila = 0; fila < metaP.ancho; fila++)
    {
        for(col = 0; col < metaP.alto; col++)
            fwrite(&imagenOriginal[col][metaP.ancho - 1 - fila], sizeof(t_pixel), 1, imagenOut);
    }

    fclose(imagenOut);
    return ROTAR_OK;
}
void mostrarMetadata(FILE *archivo)
{
    t_metadata meta;
    fseek(archivo, 2, SEEK_SET);
    fread(&meta.tamArchivo, 4, 1, archivo);

    fseek(archivo, 10, SEEK_SET);
    fread(&meta.comienzoImagen, 4, 1, archivo);
    fread(&meta.tamEncabezado, 4, 1, archivo);

    fseek(archivo, 18, SEEK_SET);
    fread(&meta.ancho, 4, 1, archivo);
    fread(&meta.alto, 4, 1, archivo);

    fseek(archivo, 28, SEEK_SET);
    fread(&meta.profundida, 2, 1, archivo);

    printf("tamanio de archivo: %d bytes\n", meta.tamArchivo);
    printf("comienzo de la imagen: %d bytes\n", meta.comienzoImagen);
    printf("tamanio del encabezado: %d bytes\n", meta.tamEncabezado);
    printf("ancho x alto: %d x %d pixeles\n", meta.ancho, meta.alto);
    printf("profundidad: %d\n", meta.profundida);
}

bool resultado(const int res)
{
    switch (res)
    {
    case TODO_OK:
        printf("todo okey\n");
        break;
    case ARCHIVO_NO_ENCONTRADO:
        printf("Archivo no encontrado\n");
        break;
    case NO_SE_PUEDE_CREAR_ARCHIVO:
        printf("No se puede crear archivo\n");
        break;
    case ESCALA_DE_GRISES_OK:
        printf("Escala de grises completado.\n");
        break;
    case TONALIDAD_OK:
        printf("Tonalidad completado.\n");
        break;
    case RECORTAR_OK:
        printf("Recortar completado.\n");
        break;
    case ROTAR_OK:
        printf("Rotar completado.\n");
        break;
    case CONTRASTE_OK:
        printf("Contraste completado.\n");
        break;
    default:
        printf("no se que codigo de error es XD\n");
    }
    return true;
}

int solucion(int argc, char* argv[])
{
    int i, numOperaciones = 0;
    char *operaciones[50], *nombreImagen;
    if(argc < 3)
    {
        printf("Uso: %s <argumentos> entre las cuales esta la imagen\n", argv[0]);
        return 0;
    }
    for(i = 1; i < argc; i++)
    {
        if(strncmp(argv[i], "--", 2) == 0)
        {
            operaciones[numOperaciones] = argv[i];
            numOperaciones++;
        }
        else
            nombreImagen = argv[i];
    }
    FILE *imagenOriginal = fopen(nombreImagen, "rb");
    if (imagenOriginal == NULL) return ARCHIVO_NO_ENCONTRADO;
    for(i = 0; i < numOperaciones; i++)
    {
        if(strcmp(operaciones[i], "--escala-de-grises") == 0)
            resultado(escalaDeGrises(imagenOriginal));
        else if(strcmp(operaciones[i], "--tonalidad-roja") == 0)
            resultado(tonalidadRoja(imagenOriginal));
        else if(strcmp(operaciones[i], "--tonalidad-verde") == 0)
            resultado(tonalidadVerde(imagenOriginal));
        else if(strcmp(operaciones[i], "--tonalidad-azul") == 0)
            resultado(tonalidadAzul(imagenOriginal));
        else if(strcmp(operaciones[i], "--aumentar-contraste") == 0)
            resultado(aumentarContraste(imagenOriginal));
        else if(strcmp(operaciones[i], "--reducir-contraste") == 0)
            resultado(reducirContraste(imagenOriginal));
        else if(strcmp(operaciones[i], "--recortar") == 0)
            resultado(recortar(imagenOriginal));
        else if(strcmp(operaciones[i], "--rotar-izquierda") == 0)
            resultado(rotarIzquierda(imagenOriginal));
        else if(strcmp(operaciones[i], "--rotar-derecha") == 0)
            resultado(rotarDerecha(imagenOriginal));
        else if(strcmp(operaciones[i], "--metadata") == 0)
            mostrarMetadata(imagenOriginal);
        else if(strcmp(operaciones[i], "--dump") == 0)
            dumpHex(imagenOriginal);
        else
            printf("operacion %s desconoscido\n", operaciones[i]);
    }
    fclose(imagenOriginal);
    return TODO_OK;
}

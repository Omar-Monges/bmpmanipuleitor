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
#include "constantes.h"
#include "funciones_estudiante.h"

int solucion(int argc, char* argv[])
{
    int i, numOperaciones = 0;
    char *operaciones[5], *nombreImagen;
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
    for(i = 0; i < numOperaciones; i++)
    {
        if(strcmp(operaciones[i], "--escala-de-grises") == 0)
            escalaDeGrises(nombreImagen);
        if(strcmp(operaciones[i], "--tonalidad-roja") == 0)
            tonalidadRoja(nombreImagen);
        if(strcmp(operaciones[i], "--tonalidad-verde") == 0)
            tonalidadVerde(nombreImagen);
        if(strcmp(operaciones[i], "--tonalidad-azul") == 0)
            tonalidadAzul(nombreImagen);
        if(strcmp(operaciones[i], "--aumentar-contraste") == 0)
            aumentarContraste(nombreImagen);
        if(strcmp(operaciones[i], "--reducir-contraste") == 0)
            reducirContraste(nombreImagen);
        if(strcmp(operaciones[i], "--recortar") == 0)
            recortar(nombreImagen);
        if(strcmp(operaciones[i], "--dump") == 0)
        {
            FILE *archivo = fopen(nombreImagen, "rb");
            dumpHex(archivo);
        }
        if(strcmp(operaciones[i], "--prueba") == 0)
        {
            operaciones[0] = argv[0];
            printf("%s", operaciones[0]);
        }
    }
    return TODO_OK;
}

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

    printf("tamanio de archivo: %d bytes\n", dataP->tamArchivo);
    printf("comienzo de la imagen: %d bytes\n", dataP->comienzoImagen);
    printf("tamanio del encabezado: %d bytes\n", dataP->tamEncabezado);
    printf("ancho x alto: %d x %d pixeles\n", dataP->ancho, dataP->alto);
    printf("profundidad: %d\n", dataP->profundida);
    rewind(archivo);
}
int escalaDeGrises(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_escala-de-grises.bmp", "wb");
    // Verifica si se abrio
    if (imagenIn == NULL)
    {
        printf("No se pudo abrir imagenIn\n");
        return 1;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return 1;
    }

    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    for(int i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    // Modificando imagen

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calculo el promedio para la escala de grises
            unsigned char promedio = (pixel.red + pixel.green + pixel.blue) / 3;
            //modifico los valores para la imagen de salida
            pixel.red = promedio;
            pixel.green = promedio;
            pixel.blue = promedio;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;
}
int tonalidadAzul(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_tonalidad-azul.bmp", "wb");
    // Verifica si se abrio
    if (imagenIn == NULL)
    {
        printf("No se pudo abrir imagenIn\n");
        return 1;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return 1;
    }
    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    for(int i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    // Modificando imagen

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta al 50% el azul
            unsigned char aumetaBlue = pixel.blue > 170 ? 255 : pixel.blue * 1.5;
            //printf("aumentaBlue: %d | pixel.blue: %d\n", aumetaBlue, pixel.blue);
            //modifico los valores para la imagen de salida
            pixel.blue = aumetaBlue;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;

}

int tonalidadVerde(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_tonalidad-verde.bmp", "wb");
    // Verifica si se abrio
    if (imagenIn == NULL)
    {
        printf("No se pudo abrir imagenIn\n");
        return 1;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return 1;
    }
    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    for(int i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    // Modificando imagen

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta al 50% el azul
            unsigned char aumeta = pixel.green > 170 ? 255 : pixel.green * 1.5;
            //printf("aumentaBlue: %d | pixel.blue: %d\n", aumetaBlue, pixel.blue);
            //modifico los valores para la imagen de salida
            pixel.green = aumeta;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;

}


int tonalidadRoja(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_tonalidad-roja.bmp", "wb");
    // Verifica si se abrio
    if (imagenIn == NULL)
    {
        printf("No se pudo abrir imagenIn\n");
        return 1;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return 1;
    }
    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);
    //copiando data hasta comienzo de la imagen
    for(int i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    // Modificando imagen

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta
            unsigned char aumeta = pixel.red > 170 ? 255 : pixel.red * 1.5;
            //printf("aumentaBlue: %d | pixel.blue: %d\n", aumetaBlue, pixel.blue);
            //modifico los valores para la imagen de salida
            pixel.red = aumeta;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;
}


int aumentarContraste(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_aumentar-contraste.bmp", "wb");
    // Verifica si se abrio
    if (imagenIn == NULL)
    {
        printf("No se pudo abrir imagenIn\n");
        return 1;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return 1;
    }

    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);
    float factorAumento = 1.24;
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul;
    //copiando data hasta comienzo de la imagen
    for(int i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    // Modificando imagen

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calculo
            nuevoRojo = pixel.red * factorAumento;
            nuevoVerde = pixel.green * factorAumento;
            nuevoAzul = pixel.blue * factorAumento;
            //modifico los valores para la imagen de salida
            pixel.red = (nuevoRojo > 255) ? 255 : nuevoRojo;
            pixel.green = (nuevoVerde > 255) ? 255 : nuevoVerde;
            pixel.blue = (nuevoAzul > 255) ? 255 : nuevoAzul;
            //printf("red: %d | green: %d | blue: %d | nuevoR: %d | nuevoG: %d | nuevoB: %d\n",
            //       pixel.red, pixel.green, pixel.blue, nuevoRojo, nuevoVerde, nuevoAzul);
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;
}


int reducirContraste(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_reducir-contraste.bmp", "wb");
    // Verifica si se abrio
    if (imagenIn == NULL)
    {
        printf("No se pudo abrir imagenIn\n");
        return 1;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return 1;
    }

    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);
    float factorReductor = 0.85;
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul;
    //copiando data hasta comienzo de la imagen
    for(int i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    // Modificando imagen

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calculo

            nuevoRojo = pixel.red * factorReductor;
            nuevoVerde = pixel.green * factorReductor;
            nuevoAzul = pixel.blue * factorReductor;

            //modifico los valores para la imagen de salida

            pixel.red = nuevoRojo;
            pixel.green = nuevoVerde;
            pixel.blue = nuevoAzul;

            //printf("red: %d | green: %d | blue: %d | nuevoR: %d | nuevoG: %d | nuevoB: %d\n",
            //       pixel.red, pixel.green, pixel.blue, nuevoRojo, nuevoVerde, nuevoAzul);
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;
}

int recortar(char *nombreImagenIn)
{
    int mitadAlto, mitadAncho, x, y;
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_recortar.bmp", "wb");
    // Verifica si se abrio
    if (imagenIn == NULL)
    {
        printf("No se pudo abrir imagenIn\n");
        return 1;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return 1;
    }
    //lee y guardar datos
    t_metadata metaP;
    extraerMetadata(imagenIn, &metaP);

    //copiando data hasta comienzo de la imagen
    for(int i = 0; i < metaP.comienzoImagen; i++)
    {
        unsigned char byte;
        if(i == 2)
        {
            unsigned int tam;
            fread(&tam, 4, 1, imagenIn);
            printf("tamOriginal: %d\n", tam);
            tam = tam >> 2;
            printf("tamMod: %d\n", tam);
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
    for (y = 0; y < mitadAlto ; y++)
    {
        for(x = 0; x < mitadAncho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }
    return 1;
}


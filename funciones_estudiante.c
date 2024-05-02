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
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
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
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
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
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
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
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
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
    float factorAumento;
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul, promedio;
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
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
    float factorAumento;
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul, promedio;
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando imagen
    //printf("pointer: %d\n", ftell(imagenOut));

    for (int y = 0; y < metaP.alto; y++)
    {
        for(int x = 0; x < metaP.ancho; x++)
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
        return ARCHIVO_NO_ENCONTRADO;
    }
    if (imagenOut == NULL)
    {
        printf("No se pudo abrir imagenOut\n");
        return NO_SE_PUEDE_CREAR_ARCHIVO;
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
    for(int fila = 0; fila < metaP.alto; fila++)
    {
        for(int col = 0; col < metaP.ancho; col++)
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
    return 1;
}

int rotarIzquierda(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_rotar-izquierda.bmp", "wb");
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
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando cagecera para rotar: ancho y alto
    fseek(imagenOut, 18, SEEK_SET);
    //fwrite(que voy a escribir, tamanio de byte,
    fwrite(&metaP.alto, sizeof(metaP.alto), 1, imagenOut);
    fwrite(&metaP.ancho, sizeof(metaP.ancho), 1, imagenOut);
    fseek(imagenOut, metaP.comienzoImagen, SEEK_SET);
    //printf("posDespues: %ld\n", ftell(imagenOut));

    t_pixel imagenOriginal[metaP.alto][metaP.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(int fila = 0; fila < metaP.alto; fila++)
    {
        for(int col = 0; col < metaP.ancho; col++)
        {
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            imagenOriginal[fila][col] = pixel;
        }
    }
    for(int fila = 0; fila < metaP.ancho; fila++)
    {
        for(int col = 0; col < metaP.alto; col++)
            fwrite(&imagenOriginal[metaP.alto - 1 - col][fila], sizeof(t_pixel), 1, imagenOut);
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;
}
int rotarDerecha(char *nombreImagenIn)
{
    t_pixel pixel;
    FILE *imagenIn;
    FILE *imagenOut;
    // Abre el archivo
    imagenIn = fopen(nombreImagenIn, "rb");
    imagenOut = fopen("estudiante_rotar-derecha.bmp", "wb");
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
    copiandoCabecera(imagenIn, imagenOut, metaP.comienzoImagen);
    // Modificando cagecera para rotar: ancho y alto
    fseek(imagenOut, 18, SEEK_SET);
    fwrite(&metaP.alto, sizeof(metaP.alto), 1, imagenOut);
    fwrite(&metaP.ancho, sizeof(metaP.ancho), 1, imagenOut);
    fseek(imagenOut, metaP.comienzoImagen, SEEK_SET);

    t_pixel imagenOriginal[metaP.alto][metaP.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(int fila = 0; fila < metaP.alto; fila++)
    {
        for(int col = 0; col < metaP.ancho; col++)
        {
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            imagenOriginal[fila][col] = pixel;
        }
    }
    // rotando imagen
    for(int fila = 0; fila < metaP.ancho; fila++)
    {
        for(int col = 0; col < metaP.alto; col++)
            fwrite(&imagenOriginal[col][metaP.ancho - 1 - fila], sizeof(t_pixel), 1, imagenOut);
    }
    fclose(imagenIn);
    fclose(imagenOut);
    return 1;
}
void mostrarMetadata(char *nombreImagen)
{
    FILE *archivo = fopen(nombreImagen, "rb");
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

    fclose(archivo);
}

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
        else if(strcmp(operaciones[i], "--tonalidad-roja") == 0)
            tonalidadRoja(nombreImagen);
        else if(strcmp(operaciones[i], "--tonalidad-verde") == 0)
            tonalidadVerde(nombreImagen);
        else if(strcmp(operaciones[i], "--tonalidad-azul") == 0)
            tonalidadAzul(nombreImagen);
        else if(strcmp(operaciones[i], "--aumentar-contraste") == 0)
            aumentarContraste(nombreImagen);
        else if(strcmp(operaciones[i], "--reducir-contraste") == 0)
            reducirContraste(nombreImagen);
        else if(strcmp(operaciones[i], "--recortar") == 0)
            recortar(nombreImagen);
        else if(strcmp(operaciones[i], "--rotar-izquierda") == 0)
            rotarIzquierda(nombreImagen);
        else if(strcmp(operaciones[i], "--rotar-derecha") == 0)
            rotarDerecha(nombreImagen);
        else if(strcmp(operaciones[i], "--metadata") == 0)
            mostrarMetadata(nombreImagen);
        else if(strcmp(operaciones[i], "--dump") == 0)
        {
            FILE *archivo = fopen(nombreImagen, "rb");
            dumpHex(archivo);
        }
        else if(strcmp(operaciones[i], "--prueba") == 0)
        {
            t_metadata data;
            FILE *imagen = fopen(nombreImagen, "rb");
            extraerMetadata(imagen, &data);
        }
        else
            printf("operacion %s desconoscido\n", operaciones[i]);
    }
    return TODO_OK;
}

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

const char *operacionesValidas[CANT_COMANDOS] =
{
    NEGATIVO,
    ESCALA_DE_GRISES,
    TONALIDAD_AZUL,
    TONALIDAD_VERDE,
    TONALIDAD_ROJA,
    AUMENTAR_CONTRASTE,
    REDUCIR_CONTRASTE,
    RECORTAR,
    ROTAR_DERECHA,
    ROTAR_IZQUIERDA,
    COMODIN,
    DUMP,
    METADATA
};

int solucion(int argc, char* argv[])
{
    int i;
    t_parametros comando;
    FILE *imagenOriginal;
    initComandos(&comando, CANT_COMANDOS);
    if(argc < 3)
    {
        return comoUsar();
    }
    for(i = 1; i < argc; i++)
    {
        if(strncmp(argv[i], "--", 2) == 0)
        {
            comando.operaciones[comando.numOperaciones] = argv[i];
            comando.numOperaciones++;
        }
        else
            comando.nombreImagen = argv[i];
    }
    imagenOriginal = fopen(comando.nombreImagen, "rb");
    if (imagenOriginal == NULL) return resultado(NO_ENCONTRE_ARCHIVO, comando.nombreImagen);
    if (!esArchivoBmp(imagenOriginal)) return resultado(NO_ES_ARCHIVO_BMP, comando.nombreImagen);
    for(i = 0; i < comando.numOperaciones; i++)
    {
        if(esOperacion(ESCALA_DE_GRISES, comando.operaciones[i]))
            !seRepite(&comando, ESCALA_DE_GRISES_OK)
                ? comando.status[ESCALA_DE_GRISES_OK] = resultado(escalaDeGrises(imagenOriginal), ESCALA_DE_GRISES)
                : resultado(REPETIDO, ESCALA_DE_GRISES);
        else if(esOperacion(TONALIDAD_ROJA, comando.operaciones[i]))
            !seRepite(&comando, TONALIDAD_ROJA_OK)
                ? comando.status[TONALIDAD_ROJA_OK] = resultado(tonalidadRoja(imagenOriginal), TONALIDAD_ROJA)
                : resultado(REPETIDO, TONALIDAD_ROJA);
        else if(esOperacion(TONALIDAD_VERDE, comando.operaciones[i]))
            !seRepite(&comando, TONALIDAD_VERDE_OK)
                ? comando.status[TONALIDAD_VERDE_OK] = resultado(tonalidadVerde(imagenOriginal), TONALIDAD_VERDE)
                : resultado(REPETIDO, TONALIDAD_VERDE);
        else if(esOperacion(TONALIDAD_AZUL, comando.operaciones[i]))
            !seRepite(&comando, TONALIDAD_AZUL_OK)
                ? comando.status[TONALIDAD_AZUL_OK] = resultado(tonalidadAzul(imagenOriginal), TONALIDAD_AZUL)
                : resultado(REPETIDO, TONALIDAD_AZUL);
        else if(esOperacion(AUMENTAR_CONTRASTE, comando.operaciones[i]))
            !seRepite(&comando, AUMENTAR_CONTRASTE_OK)
                ? comando.status[AUMENTAR_CONTRASTE_OK] = resultado(aumentarContraste(imagenOriginal), AUMENTAR_CONTRASTE)
                : resultado(REPETIDO, AUMENTAR_CONTRASTE);
        else if(esOperacion(REDUCIR_CONTRASTE, comando.operaciones[i]))
            !seRepite(&comando, REDUCIR_CONTRASTE_OK)
                ? comando.status[REDUCIR_CONTRASTE_OK] = resultado(reducirContraste(imagenOriginal), REDUCIR_CONTRASTE)
                : resultado(REPETIDO, REDUCIR_CONTRASTE);
        else if(esOperacion(RECORTAR, comando.operaciones[i]))
            !seRepite(&comando, RECORTAR_OK)
                ? comando.status[RECORTAR_OK] = resultado(recortar(imagenOriginal), RECORTAR)
                : resultado(REPETIDO, RECORTAR);
        else if(esOperacion(ROTAR_IZQUIERDA, comando.operaciones[i]))
            !seRepite(&comando, ROTAR_IZQUIERDA_OK)
                ? comando.status[ROTAR_IZQUIERDA_OK] = resultado(rotarIzquierda(imagenOriginal), ROTAR_IZQUIERDA)
                : resultado(REPETIDO, ROTAR_IZQUIERDA);
        else if(esOperacion(ROTAR_DERECHA, comando.operaciones[i]))
            !seRepite(&comando, ROTAR_DERECHA_OK)
                ? comando.status[ROTAR_DERECHA_OK] = resultado(rotarDerecha(imagenOriginal), ROTAR_DERECHA)
                : resultado(REPETIDO, ROTAR_DERECHA);
        else if(esOperacion(NEGATIVO, comando.operaciones[i]))
            !seRepite(&comando, NEGATIVO_OK)
                ? comando.status[NEGATIVO_OK] = resultado(negativo(imagenOriginal), NEGATIVO)
                : resultado(REPETIDO, NEGATIVO);
        else if(esOperacion(METADATA, comando.operaciones[i]))
            !seRepite(&comando, METADATA_OK)
                ? comando.status[METADATA_OK] = resultado(mostrarMetadata(imagenOriginal), METADATA)
                : resultado(REPETIDO, METADATA);
        else if(esOperacion(DUMP, comando.operaciones[i]))
            !seRepite(&comando, DUMP_OK)
                ? comando.status[DUMP_OK] = resultado(dumpHex(imagenOriginal), DUMP)
                : resultado(REPETIDO, DUMP);
        else if(esOperacion(COMODIN, comando.operaciones[i]))
            !seRepite(&comando, COMODIN_OK)
                ? comando.status[COMODIN_OK] = resultado(comodin(imagenOriginal), COMODIN)
                : resultado(REPETIDO, COMODIN);
        else
            printf("operacion %s desconocido\n", comando.operaciones[i]);
    }
    fclose(imagenOriginal);
    return TODO_BIEN;
}

int esOperacion(const char *operacionValida, const char *operacion)
{
    if(strcmp(operacionValida, operacion) == 0)
        return true;
    return false;
}
int seRepite(const t_parametros *param, const int operacion)
{
    if(param->status[operacion] != false)
        return true;
    return false;
}
void initComandos(t_parametros *comandos, const int cantOperacionesValidas)
{
    int i;
    comandos->numOperaciones = 0;
    for(i = 0; i < cantOperacionesValidas; i++)
        comandos->status[i] = false;
}
int comoUsar()
{
    int i;
    printf("Modo de empleo: bmpmanipuleitor [OPERACION] [IMAGEN]\n");
    printf("Operaciones validas:\n");
    for(i = 0; i < CANT_COMANDOS; i++)
        printf(" %s\n", operacionesValidas[i]);
    return TODO_BIEN;
}
int esArchivoBmp(FILE *img)
{
    char tipo[2];
    fseek(img, 0, SEEK_SET);
    fread(tipo, 2, 1, img);
    return tipo[0] == 'B' && tipo[1] == 'M';
}
int minmax(int valor, int minimo, int maximo)
{
    if(valor < minimo)
        return minimo;
    else if(valor > maximo)
        return maximo;
    else
        return valor;
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

//----------------Manipulaciones-----------

int dumpHex(FILE *archivo)
{
    unsigned int i = 0, leido;
    while(!feof(archivo))
    {
        leido = fgetc(archivo);
        printf("byte:%d hexa: %x\n", i, leido);
        i++;
    }
    return DUMP_OK;
}

void copiandoCabecera(FILE *in, FILE *out, unsigned int comienzoImagen)
{
    unsigned char buffer[comienzoImagen];
    //copiando data hasta comienzo de la imagen
    fread(&buffer, comienzoImagen, 1, in);
    fwrite(&buffer, comienzoImagen, 1, out);
}

int negativo(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    t_metadata cabecera;
    t_pixel pixel, negativoPixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_negativo.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;

    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < cabecera.alto; y++)
    {
        for(x = 0; x < cabecera.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //modifico los valores para la imagen
            negativoPixel.red = ~pixel.red;
            negativoPixel.green = ~pixel.green;
            negativoPixel.blue = ~pixel.blue;
            //escribo los bytes en la imagen de salida
            fwrite(&negativoPixel, sizeof(negativoPixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return NEGATIVO_OK;
}
int escalaDeGrises(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    unsigned char promedio;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_escala-de-grises.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;

    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < cabecera.alto; y++)
    {
        for(x = 0; x < cabecera.ancho; x++)
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
    unsigned char aumeta;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_tonalidad-azul.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < cabecera.alto; y++)
    {
        for(x = 0; x < cabecera.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta al 50% el azul
            aumeta = minmax(pixel.blue * 1.5, 0, 255);
            //modifico los valores para la imagen de salida
            pixel.blue = aumeta;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return TONALIDAD_AZUL_OK;
}

int tonalidadVerde(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    unsigned char aumeta;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_tonalidad-verde.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < cabecera.alto; y++)
    {
        for(x = 0; x < cabecera.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta al 50% el azul
            aumeta = minmax(pixel.green * 1.5, 0, 255);
            //modifico los valores para la imagen de salida
            pixel.green = aumeta;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return TONALIDAD_VERDE_OK;
}


int tonalidadRoja(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int x, y;
    unsigned char aumeta;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_tonalidad-roja.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < cabecera.alto; y++)
    {
        for(x = 0; x < cabecera.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //Aumenta
            aumeta = minmax(pixel.red * 1.5, 0, 255);
            //modifico los valores para la imagen de salida
            pixel.red = aumeta;
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return TONALIDAD_ROJA_OK;
}

int aumentarContraste(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul, condicion, x, y;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_aumentar-contraste.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando imagen
    for (y = 0; y < cabecera.alto; y++)
    {
        for(x = 0; x < cabecera.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calcular promedio
            condicion = (pixel.red + pixel.green + pixel.blue) / 3 > 127;
            //Si el promedio es mayor a 127 reducimos sino aumentamos
            if(condicion)
            {
                nuevoRojo = pixel.red + (pixel.red >> 2);
                nuevoVerde = pixel.green + (pixel.green >> 2);
                nuevoAzul = pixel.blue + (pixel.blue >> 2);

                pixel.red = minmax(nuevoRojo, 127, 255);
                pixel.green = minmax(nuevoVerde, 127, 255);
                pixel.blue = minmax(nuevoAzul, 127, 255);
            }
            else
            {
                nuevoRojo = pixel.red - (pixel.red >> 2);
                nuevoVerde = pixel.green - (pixel.green >> 2);
                nuevoAzul = pixel.blue - (pixel.blue >> 2);

                pixel.red = minmax(nuevoRojo, 0, 127);
                pixel.green = minmax(nuevoVerde, 0, 127);
                pixel.blue = minmax(nuevoAzul, 0, 127);
            }
            //escribo los bytes en la imagen de salida
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return AUMENTAR_CONTRASTE_OK;
}

int reducirContraste(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int nuevoRojo, nuevoVerde, nuevoAzul, condicion, x, y;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_reducir-contraste.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando imagen

    for (y = 0; y < cabecera.alto; y++)
    {
        for(x = 0; x < cabecera.ancho; x++)
        {
            //leer el pixel de la imagen de entrada
            fread(&pixel, sizeof(pixel), 1, imagenIn);
            //calcular promedio
            condicion = (pixel.red + pixel.green + pixel.blue) / 3 > 127;
            //Si el promedio es mayor a 127 reducimos sino aumentamos
            if(!condicion)
            {
                nuevoRojo = pixel.red + (pixel.red >> 2);
                nuevoVerde = pixel.green + (pixel.green >> 2);
                nuevoAzul = pixel.blue + (pixel.blue >> 2);

                pixel.red = minmax(nuevoRojo, 0, 127);
                pixel.green = minmax(nuevoVerde, 0, 127);
                pixel.blue = minmax(nuevoAzul, 0, 127);
            }
            else
            {
                nuevoRojo = pixel.red - (pixel.red >> 2);
                nuevoVerde = pixel.green - (pixel.green >> 2);
                nuevoAzul = pixel.blue - (pixel.blue >> 2);

                pixel.red = minmax(nuevoRojo, 127, 255);
                pixel.green = minmax(nuevoVerde, 127, 255);
                pixel.blue = minmax(nuevoAzul, 127, 255);
            }
            //escribir en imagenOut
            fwrite(&pixel, sizeof(pixel), 1, imagenOut);
        }
    }

    fclose(imagenOut);
    return REDUCIR_CONTRASTE_OK;
}

int recortar(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int mitadAlto, mitadAncho, x, y, i, fila, col, mod;
    unsigned char byte;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_recortar.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    t_metadata cabecera;
    extraerMetadata(imagenIn, &cabecera);

    //copiando data hasta comienzo de la imagen modificando el tamanio, ancho y alto.
    for(i = 0; i < cabecera.comienzoImagen; i++)
    {
        if(i == 2)
        {
            fread(&mod, 4, 1, imagenIn);
            mod = mod >> 2;
            fwrite(&mod, 4, 1, imagenOut);
            i += 4;
        }
        if(i == 18)
        {
            fread(&mod, 4, 1, imagenIn);
            mod = mod >> 1;
            fwrite(&mod, 4, 1, imagenOut);
            i += 4;
        }
        if(i == 22)
        {
            fread(&mod, 4, 1, imagenIn);
            mod = mod >> 1;
            fwrite(&mod, 4, 1, imagenOut);
            i += 4;
        }

        fread(&byte, sizeof(unsigned char), 1, imagenIn);
        fwrite(&byte, sizeof(unsigned char), 1, imagenOut);
    }
    mitadAlto = cabecera.alto >> 1;
    mitadAncho = cabecera.ancho >> 1;
    t_pixel imagenOriginal[cabecera.alto][cabecera.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(fila = 0; fila < cabecera.alto; fila++)
    {
        for(col = 0; col < cabecera.ancho; col++)
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
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_rotar-izquierda.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando cabecera para rotar: ancho y alto ej: 240x360 -> 360x240
    fseek(imagenOut, 18, SEEK_SET);
    fwrite(&cabecera.alto, sizeof(cabecera.alto), 1, imagenOut);
    fwrite(&cabecera.ancho, sizeof(cabecera.ancho), 1, imagenOut);
    fseek(imagenOut, cabecera.comienzoImagen, SEEK_SET);

    t_pixel imagenOriginal[cabecera.alto][cabecera.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(fila = 0; fila < cabecera.alto; fila++)
    {
        for(col = 0; col < cabecera.ancho; col++)
        {
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            imagenOriginal[fila][col] = pixel;
        }
    }
    for(fila = 0; fila < cabecera.ancho; fila++)
    {
        for(col = 0; col < cabecera.alto; col++)
            fwrite(&imagenOriginal[cabecera.alto - 1 - col][fila], sizeof(t_pixel), 1, imagenOut);
    }

    fclose(imagenOut);
    return ROTAR_IZQUIERDA_OK;
}
int rotarDerecha(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int fila, col;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_rotar-derecha.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    // Modificando cagecera para rotar: ancho y alto
    fseek(imagenOut, 18, SEEK_SET);
    fwrite(&cabecera.alto, sizeof(cabecera.alto), 1, imagenOut);
    fwrite(&cabecera.ancho, sizeof(cabecera.ancho), 1, imagenOut);
    fseek(imagenOut, cabecera.comienzoImagen, SEEK_SET);

    t_pixel imagenOriginal[cabecera.alto][cabecera.ancho];
    //Copiamos la imagen en la matrizOriginal
    for(fila = 0; fila < cabecera.alto; fila++)
    {
        for(col = 0; col < cabecera.ancho; col++)
        {
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            imagenOriginal[fila][col] = pixel;
        }
    }
    // rotando imagen
    for(fila = 0; fila < cabecera.ancho; fila++)
    {
        for(col = 0; col < cabecera.alto; col++)
            fwrite(&imagenOriginal[col][cabecera.ancho - 1 - fila], sizeof(t_pixel), 1, imagenOut);
    }

    fclose(imagenOut);
    return ROTAR_DERECHA_OK;
}
int comodin(FILE *imagenIn)
{
    //Declaracion de variables
    unsigned int fila, col;
    t_metadata cabecera;
    t_pixel pixel;
    PREPARAR_ARCHIVO_SALIDA("estudiante_comodin.bmp");
    // Verifica si se abrio
    if (imagenOut == NULL) return NO_PUDE_CREAR_ARCHIVO;
    //lee y guardar datos
    extraerMetadata(imagenIn, &cabecera);
    //copiando data hasta comienzo de la imagen
    copiandoCabecera(imagenIn, imagenOut, cabecera.comienzoImagen);
    for(fila = 0; fila < cabecera.alto; fila++)
    {
        fseek(imagenIn, sizeof(t_pixel) * (cabecera.ancho), SEEK_CUR);
        for(col = 0; col < cabecera.ancho; col++)
        {
            fseek(imagenIn, -3, SEEK_CUR);
            fread(&pixel, sizeof(t_pixel), 1, imagenIn);
            fwrite(&pixel, sizeof(t_pixel), 1, imagenOut);
            fseek(imagenIn, -3, SEEK_CUR);
        }
        fseek(imagenIn, sizeof(t_pixel) * (cabecera.ancho), SEEK_CUR);
    }
    return COMODIN_OK;
}
int mostrarMetadata(FILE *archivo)
{
    t_metadata meta;
    extraerMetadata(archivo, &meta);

    printf("tamanio de archivo: %d bytes\n", meta.tamArchivo);
    printf("comienzo de la imagen: %d bytes\n", meta.comienzoImagen);
    printf("tamanio del encabezado: %d bytes\n", meta.tamEncabezado);
    printf("ancho x alto: %d x %d pixeles\n", meta.ancho, meta.alto);
    printf("profundidad: %d\n", meta.profundida);
    return METADATA_OK;
}

int resultado(const int res, const char comando[])
{
    switch (res)
    {
    case TODO_BIEN:
        printf("todo okey\n");
        break;
    case NO_ENCONTRE_ARCHIVO:
        printf("Archivo no encontrado\n");
        break;
    case NO_PUDE_CREAR_ARCHIVO:
        printf("No se puede crear archivo\n");
        break;
    case REPETIDO:
        printf("Operacion %s ya se ejecuto.\n", comando);
        break;
    case NEGATIVO_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case ESCALA_DE_GRISES_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case TONALIDAD_AZUL_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case TONALIDAD_ROJA_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case TONALIDAD_VERDE_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case ROTAR_DERECHA_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case ROTAR_IZQUIERDA_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case AUMENTAR_CONTRASTE_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case REDUCIR_CONTRASTE_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case RECORTAR_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case COMODIN_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case DUMP_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case METADATA_OK:
        printf("Operacion %s completado.\n", comando);
        break;
    case NO_ES_ARCHIVO_BMP:
        printf("El archivo %s no es valido.\n", comando);
        break;
    default:
        printf("No se que codigo de error es XD\n");
    }
    return true;
}

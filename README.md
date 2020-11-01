# Proyecto Implementación de Grafos en C #

## Compilación ##
    gcc -Wall -Werror -Wextra -std=c99 -O2 -Iprimeraparte -c main.c primeraparte/*.c
    gcc -Wall -Werror -Wextra -std=c99 -O2 -Iprimeraparte -o grafo *.o

## Los grafos a utilizar deben ser en un archivo de texto .txt con el formato
## p edge A B
## donde A es el número de vértices y B el número de aristas, luego
## e a b
## donde a y b son vértices

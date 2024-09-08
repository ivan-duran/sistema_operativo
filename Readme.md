## 1. Descripción del Sistema

Este programa es una aplicación de consola escrita en C++ que permite a los usuarios ejecutar una serie de operaciones basadas en un menú interactivo. Las opciones disponibles son:

1. **Detección de Palíndromos:** Verifica si un texto ingresado es un palíndromo.
2. **Contar Vocales:** Cuenta el número de vocales en un texto dado.
3. **Cantidad de Letras:** Calcula la cantidad de letras en un texto.
4. **Promedio y Sumatoria de un Vector:** Calcula la sumatoria y el promedio de un conjunto de números enteros.
5. **Calcular f(x) = 5x*x + 1/x:** Realiza una operación matemática sobre un número ingresado.

## 2. Compilación

Este programa se compila con `makefile`, ejecutando el siguiente comando en la consola:

```bash
make
```


## 3. Ejecución
Una vez que el programa esté compilado, se ejecuta con el siguiente comando en la terminal:
```
./main -u <usuario> -p <contraseña> -t <texto> -v <vector> -n <número>
```
Ejemplo:
```
./main -u usuario -p contrasena -t palabra -v 10\;12\;20\;300 -n 5
```

## 4. Parametros

- -u: Permite ingresar el nombre de usuario. El nombre debe contener solo letras y tener al menos 3 caracteres.
- -p: Permite ingresar la contraseña. Debe tener al menos 6 caracteres y contener solo letras y números.
- -t: Permite ingresar un texto que será utilizado en las opciones 1, 2 y 3 del menú.
- -v: Permite ingresar un vector de números enteros separados por ; para la opción 4 del menú (por ejemplo, 10;12;20;300).
- -n: Permite ingresar un número para calcular la función en la opción 5 del menú.
## 1. Descripción del Sistema

Este programa es una aplicación de consola escrita en C++ que permite a los usuarios ejecutar una serie de operaciones basadas en un menú interactivo. Las opciones disponibles son:

0. **Salir:** Permite salir del programa.  
1. **Detección de Palíndromos:** Verifica si un texto ingresado es un palíndromo.  
2. **Contar Vocales:** Cuenta el número de vocales en un texto dado.  
3. **Cantidad de Letras:** Calcula la cantidad de letras en un texto.  
4. **Promedio y Sumatoria de un Vector:** Calcula la sumatoria y el promedio de un conjunto de números enteros.  
5. **Calcular f(x) = 5x*x + 1/x:** Realiza una operación matemática sobre un número ingresado.  
6. **Contar Palabras:** Cuenta las palabras que hay en los archivos de un directorio con la misma extensión.

Si el usuario tiene el rol de administrador, podrá acceder a las siguientes opciones adicionales:

7. **Ingresar Usuario:** Permite ingresar un nuevo usuario.  
8. **Listar Usuarios:** Muestra la lista de usuarios registrados.  
9. **Eliminar Usuario:** Elimina un usuario de la lista.

## 2. Compilación

Este programa se compila con `makefile`. En la carpeta raíz del proyecto, se debe ejecutar el siguiente comando en la terminal:

```bash
make
```

## 3. Ejecución

Una vez que el programa esté compilado, desde la carpeta raiz, se ejecuta con el siguiente comando:

```
./main -u <usuario> -p <contraseña> -t <texto> -v <vector> -n <número>
```

Ejemplo:

```
./main -u usuario -p contrasena -t palabra -v 10\;12\;20\;300 -n 5
```

## 4. Parámetros

- **-u:** Permite ingresar el nombre de usuario. El nombre debe contener solo letras y tener al menos 3 caracteres.
- **-p:** Permite ingresar la contraseña. Debe tener al menos 6 caracteres y contener solo letras y números.
- **-t:** Permite ingresar un texto que será utilizado en las opciones 1, 2 y 3 del menú.
- **-v:** Permite ingresar un vector de números enteros separados por `;` para la opción 4 del menú (por ejemplo, `10;12;20;300`).
- **-n:** Permite ingresar un número para calcular la función en la opción 5 del menú.

## 5. Gestión de Usuarios

Este sistema permite gestionar usuarios con dos roles distintos: **Admin** y **Usuario Genérico**. Los usuarios se autentican utilizando un archivo de texto que actúa como base de datos, donde están almacenados el nombre de usuario, la contraseña y el rol. Solo los usuarios con rol **Admin** pueden ver y acceder a las opciones de gestión de usuarios.

El formato del archivo de base de datos es el siguiente:

```
NombreUsuario1;Contraseña1;Rol1
NombreUsuario2;Contraseña2;Rol2
```

### Opciones de gestión de usuarios:

1. **Ingresar Usuario:** Permite añadir nuevos usuarios al archivo de base de datos.
2. **Listar Usuarios:** Muestra una lista de todos los usuarios registrados junto con su rol.
3. **Eliminar Usuario:** Permite eliminar usuarios genéricos del sistema. Solo los usuarios con rol **Admin** pueden realizar esta operación.

## 6. Conteo de Palabras en Archivos

El sistema incluye una funcionalidad para contar palabras en archivos dentro de un directorio especificado por el usuario. Esta opción ejecuta un proceso externo que:

1. Solicita al usuario tres datos:
   - **Extensión de los archivos** a procesar (por ejemplo, `.txt`).
   - **Ruta del directorio** donde se encuentran los archivos.
   - **Ruta del directorio** donde se guardarán los resultados.
   
2. Valida si las carpetas y los archivos existen antes de proceder.

3. Procesa los archivos del directorio de entrada, contando las veces que aparece cada palabra en cada archivo. Luego, genera un archivo de salida con el mismo nombre que el archivo de entrada, pero con los resultados del conteo en el formato:

```
palabra1; cantidad
palabra2; cantidad
```

4. Muestra un resumen al finalizar con la cantidad de palabras distintas en cada archivo procesado.

Ejemplo de salida:

```
archivo /home/lvc/out/cuento1.txt, 100 palabras distintas
archivo /home/lvc/out/cuento10.txt, 1020 palabras distintas
archivo /home/lvc/out/cuento11.txt, 2300 palabras distintas
```

## 7. Variables de Entorno

El sistema utiliza variables de entorno para definir el **path** del archivo de la base de datos de usuarios:

```bash
DB_PATH="/ruta/a/archivo/usuarios.txt"
```

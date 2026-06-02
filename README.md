# Laboratorio 2 Estructura de Datos

## Complilación
Para compilar el programa, ejecuta el siguiente comando en tu terminal:
```bash
g++ -std=c++17 main.cpp tinyxml2.cpp nodes.cpp tree.cpp -o test
```

## Ejecución
El programa se ejecuta con el siguiente formato:
```bash
./test
```

## Salida
La salida del programa deberá ser de la siguiente forma:
- Se imprime el listado de id's de libros pertenecientes a el árbol completo 
- Se imprime el listado de id's de libros precursores
- Se borran los libros que tengan rating promedio menor o igual a 4.5 de el árbol
- Se imprime nuevamente el listado de id's de libros pertenecientes a el árbol luego de la eliminación

## Repositorios Externos
Este proyecto hizo uso del siguiente repositorio

**TinyXML-2** — C++ XML parser  
  Autor: Lee Thomason  
  Repositorio: https://github.com/leethomason/tinyxml2  
  Licencia: zlib
# arbolB
Template para un diccionario implementado con un árbol B con capacidad para eliminar lógicamente.

El template se debe instanciar declarando el tipo de dato de tanto la llave como la información que esta almacena dentro del nodo. En caso de alocar memoria dentro de uno de los nodos, el destructor del árbol NO limpiara la memoria asociada a la información almacenada en el nodo, sino de la que se ocupó para instanciar al árbol.

El método recorrer imprime el árbol en un formato cómodo para interpretar el orden de inserción de este. Algunos recursos interesantes para interpretar la inserción del árbol son por ejemplo la página "B Tree visualization".

Los métodos de eliminación y consulta solo piden como parámetro la llave a buscar en el diccionario, mientras que la carga tiene como parámetros tanto al dato como a la llave.

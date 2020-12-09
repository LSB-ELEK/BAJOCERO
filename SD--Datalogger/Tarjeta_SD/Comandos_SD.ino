/*
      Comandos libreria SD
 */




/*
     →→ Iniciar la SD
    SD.begin(cspin);
 
    →→ Comprobar si existe un fichero (devuelve 1 si existe, 0 en caso contrario)
    SD.exists(filename);
 
    →→ Borrar un fichero
    SD.remove(filename);
 
    →→ Abrir un fichero
    →→ Mode: FILE_READ para sólo lectura
    →→        FILE_WRITE para lectura y escritura
    SD.open(filepath, mode);
 
    →→ Crear un directorio/carpeta
    SD.mkdir(directory);
 
    →→ Eliminar un directorio/carpeta
    SD.rmdir(dirname);

 */

 /*
    →→ Obtener el tamaño de un fichero
    file.size()
 
    →→ Comprobar si quedan bytes por leer
    file.available()
 
    →→ Leer un byte del fichero
    file.read()
 
    →→ Escribir un byte en el fichero
    file.write(data)
 
    →→ Escribir una variable en un fichero (en forma similar a Serial.Print)
    file.print(data)
 
    →→ Obtener el punto de lectura/escritura actual
    file.position()
 
    →→ Mover el punto de lectura/escritura actual
    →→ Pos: Debe estar entre 0 y file.size()
    file.seek(pos)
 
    →→ Cerrar el fichero
    file.close()
  */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include "mytar.h"

extern char *use;

/** Copy nBytes bytes from the origin file to the destination file.
 *
 * origin: pointer to the FILE descriptor associated with the origin file
 * destination:  pointer to the FILE descriptor associated with the destination file
 * nBytes: number of bytes to copy
 *
 * Returns the number of bytes actually copied or -1 if an error occured.
 */
int copynFile(FILE * origin, FILE * destination, int nBytes)
{
	// Complete the function
	
	int c=0, ret=0, i=0;


	while ((c = getc(origin)) != EOF) {
		ret=putc((unsigned char) c, destination);
		i++;
		if (ret==EOF){
			fclose(origin);
			err(3,"putc() failed!!");
		}
	}

	if(i==0){
		return 0;
	} else {
		return i;
	}
}

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor 
 * 
 * The loadstr() function must allocate memory from the heap to store 
 * the contents of the string read from the FILE. 
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc()) 
 * 
 * Returns: !=NULL if success, NULL if error
 */
char*
loadstr(FILE * file)
{
	int n = 0;
	char c;
	if (file != NULL) {
		do {
			fread(&c, sizeof(char), 1, file);
			n++; //Contador para la cadena de caracteres
		} while (!feof(file) && c != '\0');

		//Retrocedemos el puntero desde la posicion actual (SEEK_CUR) tantas veces como hemos avanzado
		fseek(file, n * -1, SEEK_CUR);
		char* p;
		p = (char*) malloc(n * sizeof(unsigned char)); //Reserva memoria para n caracteres de tamanyo char

		//Lee la cadena de caracteres otra vez y la guarda en memoria
		int i = 0;

		do {
			fread(&c, sizeof(char), 1, file);
			p[i] = c;
			i++;
		} while (c != 0 && c != '\0');
		return p;
	}

	return NULL;
}

/** Read tarball header and store it in memory.
 *
 * tarFile: pointer to the tarball's FILE descriptor 
 * nFiles: output parameter. Used to return the number 
 * of files stored in the tarball archive (first 4 bytes of the header).
 *
 * On success it returns the starting memory address of an array that stores 
 * the (name,size) pairs read from the tar file. Upon failure, the function returns NULL.
 */
stHeaderEntry*
readHeader(FILE * tarFile, int *nFiles)
{
	stHeaderEntry * array = NULL ;
	int nr_files =0;
	/* ... Read the number of files (N) from tarfile and
	store it in nr_files ... */
	fread(&nr_files, sizeof(unsigned int), 1, tarFile);


	/* Allocate memory for the array */
	if((array = (stHeaderEntry *) malloc(sizeof(stHeaderEntry) * (nr_files))) == NULL){
					err(2, "Error al reservar memoria");

				}


	/* ... Read the ( pathname , size ) pairs from tarFile and
	store them in the array ... */

	int i;
		for (i = 0; i < (nr_files); i++) {
			array[i].name = loadstr(tarFile);
			fread(&array[i].size, sizeof(unsigned int), 1, tarFile);
		}
	/* Store the number of files in the output parameter */

	*nFiles  = nr_files ;
		return array ;


}

/** Creates a tarball archive 
 *
 * nfiles: number of files to be stored in the tarball
 * filenames: array with the path names of the files to be included in the tarball
 * tarname: name of the tarball archive
 * 
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First reserve room in the file to store the tarball header.
 * Move the file's position indicator to the data section (skip the header)
 * and dump the contents of the source files (one by one) in the tarball archive. 
 * At the same time, build the representation of the tarball header in memory.
 * Finally, rewind the file's position indicator, write the number of files as well as 
 * the (file name,file size) pairs in the tar archive.
 *
 * Important reminder: to calculate the room needed for the header, a simple sizeof 
 * of stHeaderEntry will not work. Bear in mind that, on disk, file names found in (name,size) 
 * pairs occupy strlen(name)+1 bytes.
 *
 */
int
createTar(int nFiles, char *fileNames[], char tarName[])
{
	int suma=0;
	char *destFile= tarName;
	FILE *inputFile;
	FILE *outFile;
	stHeaderEntry *arrayArchivos;


	//calculamos cuantos bytes necesitamos para guardar los nombres de los archivos
	int i=0;
	while(i<nFiles){
	  suma= suma + strlen(fileNames[i])+1;
	  i++;	  
	}

	//abrimos el archivo mtar para escritura
	if ((outFile = fopen(destFile, "w+")) == NULL){
		err(2,"The output file could not be opened");
	}

	suma= suma +4; //sumamos el int del numero de archivos
	suma = suma +(nFiles*sizeof(unsigned int));//sumamos el int del tamaño de cada archivo



	//reservamos memoria
	if((arrayArchivos = malloc(suma)) == NULL){
		err(2, "Error al reservar memoria");
		fclose(outFile);
		return(EXIT_FAILURE);
	}


	fseek(outFile, suma, SEEK_SET); //situamos el cursor del FILE en la posicion donde comienzan los datos


	int k=0;
	while(k<nFiles){
		if((inputFile = fopen(fileNames[k], "r")) == NULL){
				err(2, "No se ha podido abrir el fichero %s: \n", fileNames[i]);
				free(arrayArchivos);
				return(EXIT_FAILURE);
			}

		arrayArchivos[k].size = copynFile(inputFile, outFile, sizeof(fileNames[k]));//nos devuelve a copiado el numero de bytes que se ha copiado, por lo que sabemos cuando ocupa el archivo
		// guardamos el nombre del archivo en la estructura
		arrayArchivos[k].name = fileNames[k];


		fclose(inputFile);
		k++;

	}
	
	rewind(outFile); //situamos el cursor de FILE al comienzo del archivo destino
	fwrite(&nFiles, sizeof(int), 1, outFile);
	//escribimos a continuacion los datos de cada uno de los ficheros
	fseek(outFile, sizeof(int), SEEK_SET);

	int j=0;
	while(j<nFiles){
		fwrite(arrayArchivos[j].name, strlen(fileNames[j]) + 1, 1, outFile);

		fwrite(&arrayArchivos[j].size, sizeof(unsigned int), 1, outFile);

		j++;

	}



	free(arrayArchivos);
	fclose(outFile);
	return EXIT_SUCCESS;
}

/** Extract files stored in a tarball archive
 *
 * tarName: tarball's pathname
 *
 * On success, it returns EXIT_SUCCESS; upon error it returns EXIT_FAILURE. 
 * (macros defined in stdlib.h).
 *
 * HINTS: First load the tarball's header into memory.
 * After reading the header, the file position indicator will be located at the 
 * tarball's data section. By using information from the 
 * header --number of files and (file name, file size) pairs--, extract files 
 * stored in the data section of the tarball.
 *
 */
int
extractTar(char tarName[])
{
	FILE *input;

		unsigned char* c;
		int nFiles=0;
		stHeaderEntry *arrayArchivos;
		arrayArchivos = (stHeaderEntry *) malloc(sizeof(stHeaderEntry) * (nFiles));


		//abrimos archivo mtar para lectura
		if((input = fopen(tarName, "r")) == NULL){
							fprintf(stderr, "No se ha podido abrir el fichero %s: \n", tarName);
							return(EXIT_FAILURE);
		}

		//Leemos los datos de cabecera y lo almacenamos en p
		arrayArchivos = readHeader(input, &nFiles);

		/*int dataoffset=0;
		dataoffset = (sizeof(arrayArchivos) * nFiles) + (sizeof(unsigned char)* (sizeof(int) * 4)+2);

		fseek(input, dataoffset, SEEK_SET);
*/

		int i=0;
		for (i = 0; i < nFiles; i++) {
			//Creamos nuevo fichero con mismo nombre en modo escritura, leemos el contenido y lo copiamos en el nuevo fichero
			FILE *output = fopen(arrayArchivos[i].name, "w");
			if (output != NULL) {
				c = (unsigned char*) malloc(arrayArchivos[i].size);
				fread(c, sizeof(unsigned char) * arrayArchivos[i].size, 1, input); //leemos de tarFile
				fwrite(c, sizeof(unsigned char) * arrayArchivos[i].size, 1, output);	//escribimos en el nuevo archivo
				fclose(output);
			} else
				return EXIT_FAILURE;
		}
		fclose(input);

		printf("\nFile successfully extracted!\n\n");

		return EXIT_SUCCESS;
}

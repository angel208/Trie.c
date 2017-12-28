#include <stdio.h>
#include "trie.h"
#include <stdlib.h>

void menu_ayuda(void){
          printf ("----------------------comandos--------------------\n");
          printf ("cargar: carga un archivo .dic (cargar nombre_archivo)\n");
          printf ("s: muestra los sinonimos de una palabra (s palabra)\n");
          printf ("a: muestra los antonimos de una palabra (a palabra)\n");
          printf ("e: mustra los sinonimos y antonimos de las palabras que comiencen con la expresion (e expresion)\n");
          printf ("salir .: sale del programa\n");
}

int main(int argc, char **argv){

   	trieNode_t *root = TrieCreateNode('\0'), *Busq=NULL;
	char seleccion[10], palabra[25];

	if ( argc > 1 ){//modo comando

			   cargar_datos("file.dic", root);
	                   root=root->children;
	                   LowerCase(argv[2]);

			   if ( !strcmp (argv[1], "a")  || !strcmp (argv[1], "A")  ){
					Busq = TrieSearch ( root , argv[2] );
					if (!Busq) { printf ("Palabra no encontrada\n\n"); exit(1);}
					mostrar(Busq->children->ant);
				}

				else if ( !strcmp (argv[1], "s")  || !strcmp (argv[1], "S")  ){
					Busq = TrieSearch ( root , argv[2] ); 
					if (!Busq) { printf ("Palabra no encontrada\n\n"); exit(1);}
					mostrar(Busq->children->sin);
				}
				else {
					printf ("Comando Erroneo\n\n");
					exit(1);
				}

	}
	else{ //modo iterativo
           
	    cargar_datos("file.dic", root);
	    root=root->children;

			do{
				printf ( "> "); 
				scanf ("%s %s", seleccion, palabra );
				
				if ( strcmp (seleccion, "cargar") ) 
				        LowerCase(palabra);

				if ( !strcmp (seleccion, "e") || !strcmp (seleccion, "E") ){
					BuscarExpresion( root , palabra );
				} 
				else if ( !strcmp (seleccion, "cargar") ){
					LiberarTrie( root );
					root=TrieCreateNode('\0');
					cargar_datos( palabra , root ); root=root->children;
					printf ("archivo cargado\n\n");
				}   
				else if ( !strcmp (seleccion, "a")  || !strcmp (seleccion, "A")  ){
					Busq = TrieSearch ( root , palabra );
					if (!Busq) printf ("Palabra no encontrada\n\n");
					else       mostrar(Busq->children->ant);
				}
				else if ( !strcmp (seleccion, "s")  || !strcmp (seleccion, "S")  ){
					Busq = TrieSearch ( root , palabra );
					if (!Busq) printf ("Palabra no encontrada\n\n");
					else  mostrar (Busq->children->sin);
				}
				else if ( !strcmp (seleccion, "ayuda") ){
					menu_ayuda();
				} 
				else {
                                   if ( strcmp (seleccion, "salir") )
                                   printf( "Comando erroneo, escriba 'ayuda .' para mas informacion\n\n"); 
				} 

			  }while ( strcmp(seleccion, "salir") );

	} //fin del modo interactivo
	
	LiberarTrie( root );

}



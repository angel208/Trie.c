#include "ListasDobles.h"

//estructura de datos 
typedef struct trieNode{
    	char key; 
    	list *sin;
		list *ant;
    	struct trieNode *next; 		// el vecino de la derecha
    	struct trieNode *prev;		// vecino de la izquierda
    	struct trieNode *children;	// nodo Hijo
    	struct trieNode *parent;	// Nodo Padre
} trieNode_t;

void LowerCase ( char str[] ){

  for ( ; *str ; str++ )
       *str = tolower(*str);
}

//===================================crea e inicializa un nodo==================================//

trieNode_t *TrieCreateNode(char key){
	trieNode_t *node = NULL;
    	node = (trieNode_t *)malloc(sizeof(trieNode_t)); 
 
    	if(NULL == node){
		printf("Error en Malloc\n");
        	return node;
    	}
 
    	node->key = key;
    	node->next = NULL;
    	node->children = NULL;
    	    node->sin = nueva_lista();
	    node->ant = nueva_lista();
    	node->parent= NULL;
    	node->prev= NULL;
    	return node;
}
//=================================Busca en la estructura==============================//

trieNode_t* TrieSearch(trieNode_t *root, const char *key){
    	trieNode_t *level = root;
    	trieNode_t *pPtr = NULL; 
    
	while(1){
        	trieNode_t *found = NULL;
        	trieNode_t *curr;
		for (curr = level; curr != NULL; curr = curr->next){
            		if (curr->key == *key){
                		found = curr;
                		break;
            		}
        	}
 
        	if (found == NULL)
            	return NULL;  
            	
        	if (*key == '\0'){ 
            		pPtr = curr->parent;
            		return pPtr;
        	}
        	
         	level = found->children;
        	key++;
    	}
}
//==========================Manejo de la Expresion===================================================//

trieNode_t* TrieExpSearch(trieNode_t *root, const char *key){ //--funcion TrieSearch, q no busca una palabra completa, sino una expresion
    	trieNode_t *level = root;
    	trieNode_t *pPtr = NULL;
    
	while(1){
        	trieNode_t *found = NULL;
        	trieNode_t *curr;
		for (curr = level; curr != NULL ; curr = curr->next){
            		if (curr->key == *key){
                		found = curr;
                		break;
            		}
        	}
 
        	if (found == NULL)
            	return NULL; 
            	
        	if ( *(key+1) == '\0' ){ 
            		pPtr = curr->children; //retorna el nodo con el subarbol de la ultima letra de la expresion
            		return pPtr;
        	}

         	level = found->children;
        	key++;
    	}
}
 
void MostrarExpresion ( trieNode_t *root ){ //--imprime el subarbol con las palabras que empiezan con la expresion

   if (root == NULL )
	   return;

   MostrarExpresion ( root->children );
   MostrarExpresion ( root->next );

   if ( root->key == '\0' ){
   	   printf("\n");
           printf("%s: \n", root->sin->ini->dato );
	   printf("S:");mostrarExp ( root->sin );
	   printf("A:");mostrarExp ( root->ant );

   }
   return;
}

void BuscarExpresion( trieNode_t *root , char exp[] ){ //Busca y muestra el resultado de la expresion
	trieNode_t *Busqueda;
        
	Busqueda = TrieExpSearch( root , exp );

        if (Busqueda){
        	MostrarExpresion( Busqueda );
        	printf( "\n" ); 
        }
        else
            printf ("No se encontraron Coincidencias\n");
        	
}
/*=====================================Agrega a la estructura================================*/

void TrieAdd(trieNode_t **root, char *palabra, char original[], char *palabra2, char estado ){
	trieNode_t *np = NULL, *Busqueda = NULL;
	
 
    	if(*root == NULL ){
        	printf("TRIE vacio\n");
        	return;
    	}
    	np = (*root)->children;
 
    	if( ( Busqueda=TrieSearch(np, palabra) ) ){ //de ya estar la palabra en el arbol    	
	
               
	       if (estado == 's' || estado == 'S' ){
	           if ( BuscarEnLista(Busqueda->children->sin ,palabra2) ) return;
	           insertar_fin ( Busqueda->children->sin , palabra2 );
	       }
               else if (estado == 'a' || estado == 'A' ){ 
                   if ( BuscarEnLista(Busqueda->children->ant ,palabra2) ) return;
                   insertar_fin ( Busqueda->children->ant , palabra2 );
               }
               return;
    	}
 
    	if(np == NULL){
        /*Primer nodo a ser creado*/
        	for(np = *root; *palabra; np = np->children){
            		np ->children = TrieCreateNode( *palabra );
            		np ->children->parent = np ;
            		palabra++;
        	}
 
        	np ->children = TrieCreateNode('\0');
			     insertar_fin (np->children->sin, original); insertar_fin (np->children->ant ,original );
				 if (estado == 's' || estado == 'S' ) insertar_fin  ( np->children->sin , palabra2 );
				 else if (estado == 'a' || estado == 'A' ) insertar_fin  ( np->children->ant , palabra2 );
				
        	np ->children->parent = np ;
        	return;
    	}

    	while(*palabra != '\0'){
        	if(*palabra == np ->key){
            		palabra++;
            		np  = np ->children;
        	}
        	else
            		break;
    	}
 
    	while(np ->next){
        	if(*palabra == np ->next->key){
            		palabra++;
            		TrieAdd(&(np ->next), palabra, original, palabra2, estado);
            		return;
        	}
        	np  = np ->next;
    	}
 
    	np ->next = TrieCreateNode(*palabra); // crea un vecino con la letra de no haberla encontrado en su nivel
    	np ->next->parent = np ->parent;
    	np ->next->prev = np ; 
    	palabra++;
 
    	for(np  = np ->next; *palabra ; np  = np ->children){ //anade lo que queda de la palabra al vecino recien creado
        	np ->children = TrieCreateNode(*palabra);
        	np ->children->parent = np ;
		palabra++;
    	}
 
	np ->children = TrieCreateNode('\0' ); //asigna 
        np ->children->parent = np ;

	    insertar_fin (np->children->sin, original); insertar_fin (np->children->ant , original );

		if (estado == 's' || estado == 'S' ) insertar_fin ( np->children->sin , palabra2 );
		else if (estado == 'a' || estado == 'A' ) insertar_fin  ( np->children->ant , palabra2 );
		
    return;
}

//=============================Carga del archivo a la Estructura de Datos (el trie)=====================//

int validarPalabra ( char s[] ){
	int i=0;
	
	if (s[i] == '\0' ) return 0;

	for (i=0 ; s[i] != '\0' ; i++){
		if ( s[i]<'A' || (s[i]>'Z' && s[i]<'a' ) || s[i]>'z'  )
			return 0;		
	}
	return 1;
}


void cargar_datos(char archivo[], trieNode_t *root){
    FILE *fp;
    int i;
    char palabra[25], palabra2[25], estado[5], buffer[100];
	
	if((fp=fopen(archivo,"r"))==NULL){
		printf("error de archivo\n");
		exit(1);
	}
	
	
	while (fgets( buffer, 99, fp)!=NULL){
	
	estado[0]='\0'; palabra[0]='\0'; palabra2[0]='\0'; //inicializa las palabras
	
	sscanf( buffer ,"%s %s %s",estado, palabra, palabra2); // cargar las palabras
	
	//validaciones de estado y palabras	
	        if ( !estado[0] && !palabra[0] && !palabra2[0] ) continue;
		if ( ( estado[0] != 'S' && estado[0] != 's' && estado[0] != 'a' && estado[0] != 'A' ) || ( estado[1] != '\0' ) )
		    { printf("ocurrio un error al cargar la palabra %s\n", palabra);  continue;  }
		if ( !validarPalabra(palabra) || !validarPalabra(palabra2) )        
	            { printf("ocurrio un error al cargar la palabra %s\n", palabra);  continue;  } 
	//---------------------------------
                
                LowerCase(palabra); LowerCase(palabra2);
		TrieAdd( &root, palabra, palabra, palabra2, estado[0] );
		TrieAdd( &root, palabra2, palabra2 , palabra, estado[0] );
	}
	fclose(fp);
}
/*=======================Liberar el Trie=========================*/

trieNode_t *LiberarTrie( trieNode_t *root ){

   if (root == NULL )
	   return;

   root->next = LiberarTrie( root->children );
   root->children = LiberarTrie( root->next );

   	  free_all(root->sin);
   	  root->sin = NULL;
	  free_all(root->ant);
	  root->sin = NULL;
	  free(root);

   return NULL;
}

/* ======================Escribir el Trie======================= */

int maxLevel;

void padding( char *s, int n ){
   	int i;

   	for ( i = 0; i < n; i++ )
      		printf( "%s", s );
}

void printNode(trieNode_t *p){
   	if ( p->key != '\0' )
      		printf("( %c )\n", p->key );
   	else{
      		printf("(`*')->" );
	         mostrarf(p->sin);
			printf("\n" );
		 mostrarf(p->ant);
			printf("\n" );
	}
}

void printSubTrie(trieNode_t *p, int level ){  // Print on level level
	if ( p == NULL )
      		return;
   	while ( p != NULL ){  
      		padding("         ", level );
      		printNode( p );
      		printSubTrie( p->children, level+1);
      		p = p->next;
   	}
}

void TriePrint(trieNode_t *root){
// printf("TriePrint\n");
   	printSubTrie( root, 0 );  // Print on level 0
   	printf("\n========================================================\n");
}

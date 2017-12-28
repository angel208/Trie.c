#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char dato[25];
    struct nodo *sig, *ant;
} node;

typedef struct {
     node *ini, *fin;
} list;

//----------------------------------funciones------------------------------------//

list *nueva_lista ( void ){
   list *p;
   
   if ( ! (p = (list *)malloc ( sizeof(list) )) ){
    printf ("error: malloc");
    exit(1);
   }
   p->ini = p->fin = NULL;
   return p;
}

void insertar_fin ( list *lp, char palabra[] ){
   node *np;
   

      if ( !( np = (node *)malloc ( sizeof(node) ) ) ){
        printf ("error: malloc");
        exit(1);
      }
   
   strcpy(np->dato, palabra);
   
   if ( lp->ini == NULL ){ //LA LISTA ESTA VACIA
      np->sig = np->ant = NULL;
      lp->ini = lp->fin = np;
   }
   else{
      np->ant = lp->fin;
      lp->fin->sig= np;
      lp->fin = np;
	  np->sig=NULL;
   }
}

void free_all ( list *lp ){
  node *np, *actp;

  np = lp->ini;

  while(np){
    actp = np->sig;
    free(np);
    np=actp;
  }
 
  free(lp);
}

int BuscarEnLista( list *lp , char str[] ){
  node *np = lp->ini;
  
  for ( ; np ; np=np->sig )
     if ( !strcmp ( np->dato , str ) )
        return 1;
        
  return 0;
}

//===============================mostrar listas=====================================//

void mostrarf( list *lp ){
  node *np;

    for ( np = lp->ini->sig ; np != NULL ; np = np->sig )
        printf ( "%s ",  np->dato );
}

void mostrarExp( list *lp ){
  node *np=lp->ini->sig ;
    if ( !np ){
            printf("\b\b  ");
	    return;
   }
   
    for (; np != NULL ; np = np->sig )
        printf ( "%s, ",  np->dato );
    printf ( "\b\b \n" );
    
}
void mostrar( list *lp ){
  node *np=lp->ini->sig ;
    if ( !np ){
		printf ("Ningun elemento ha sido encontrado \n");
	    return;
   }
   
    for (; np != NULL ; np = np->sig )
        printf ( "%s  ",  np->dato );
    printf ( "\n\n" );
    
}

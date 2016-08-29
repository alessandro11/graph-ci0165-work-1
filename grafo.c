/*
 * =====================================================================================
 *
 *       Filename:  grafo.c

 *
 *    Description:  Trabalho1 de grafos Professor Renato.
 *
 *        Version:  1.0
 *        Created:  08/27/2016 07:15:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alessandro Elias, GRR20110589, ae11@inf.ufpr.br
 *
 * =====================================================================================
 */

#include <malloc.h>
#include "grafo.h"

//-----------------------------------------------------------------------------
// (apontador para) lista encadeada
typedef struct lista *lista;

//-----------------------------------------------------------------------------
// (apontador para) nó da lista encadeada cujo conteúdo é um void *
typedef struct no *no;

//------------------------------------------------------------------------------
// devolve o número de nós da lista l
unsigned int tamanho_lista(lista l);

//------------------------------------------------------------------------------
// devolve o primeiro nó da lista l,
//      ou NULL, se l é vazia
no primeiro_no(lista l);

//------------------------------------------------------------------------------
// devolve o sucessor do nó n,
//      ou NULL, se n for o último nó da lista
no proximo_no(no n);

//------------------------------------------------------------------------------
// devolve o conteúdo do nó n
//      ou NULL se n = NULL
void *conteudo(no n);

//------------------------------------------------------------------------------
// insere um novo nó na lista l cujo conteúdo é p
//
// devolve o no recém-criado
//      ou NULL em caso de falha
no insere_lista(void *conteudo, lista l);

//------------------------------------------------------------------------------
// cria uma lista vazia e a devolve
//
// devolve NULL em caso de falha
lista constroi_lista(void);
//------------------------------------------------------------------------------
// desaloca a lista l e todos os seus nós
//
// se destroi != NULL invoca
//
//     destroi(conteudo(n))
//
// para cada nó n da lista.
//
// devolve 1 em caso de sucesso,
//      ou 0 em caso de falha
int destroi_lista(lista l, int destroi(void *));

//------------------------------------------------------------------------------
// remove o no de endereço rno de l
// se destroi != NULL, executa destroi(conteudo(rno))
// devolve 1, em caso de sucesso
//         0, se rno não for um no de l
int remove_no(struct lista *l, struct no *rno, int destroi(void *));
//______________________________________________________________________________


//------------------------------------------------------------------------------
// devolve o nome do grafo g
char *nome_grafo(grafo g) {
	return NULL;
}

//------------------------------------------------------------------------------
// devolve 1, se g é direcionado,
//      ou 0, caso contrário
int direcionado(grafo g) {
	return 0;
}

//------------------------------------------------------------------------------
// devolve 1, se g tem pesos nas arestas/arcos,
//      ou 0, caso contrário
int ponderado(grafo g) {
	return 0;
}

//------------------------------------------------------------------------------
// devolve o número de vértices do grafo g
unsigned int numero_vertices(grafo g) {
	return 0;
}

//------------------------------------------------------------------------------
// devolve o número de arestas/arcos do grafo g
unsigned int numero_arestas(grafo g) {
	return 0;
}

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// o peso das arestas/arcos (quando houver) é escrito como o atributo
// de nome "peso"
//
// devolve o grafo escrito
//      ou NULL em caso de erro
grafo escreve_grafo(FILE *output, grafo g) {
	return NULL;
}

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
//
// devolve 1 em caso de sucesso,
//      ou 0 caso contrário
int destroi_grafo(grafo g) {
	return 0;
}

//______________________________________________________________________________
//
// Definição das funções que trata a lista.
//
// nó de lista encadeada cujo conteúdo é um void *
struct no {

  void*	conteudo;
  no	anterior;
  no 	proximo;
};

//---------------------------------------------------------------------------
// lista encadeada
struct lista {

  unsigned int tamanho;
  int padding; // só pra evitar warning
  no primeiro;
};

//---------------------------------------------------------------------------
// devolve o número de nós da lista l
unsigned int tamanho_lista(lista l) { return l->tamanho; }

//---------------------------------------------------------------------------
// devolve o primeiro nó da lista l,
//      ou NULL, se l é vazia
no primeiro_no(lista l) { return l->primeiro; }

//---------------------------------------------------------------------------
// devolve o conteúdo do nó n
//      ou NULL se n = NULL
void *conteudo(no n) { return n->conteudo; }

//---------------------------------------------------------------------------
// devolve o sucessor do nó n,
//      ou NULL, se n for o último nó da lista
no proximo_no(no n) { return n->proximo; }

//---------------------------------------------------------------------------
// cria uma lista vazia e a devolve
//
// devolve NULL em caso de falha
lista constroi_lista(void) {

  lista l = malloc(sizeof(struct lista));

  if ( ! l )
    return NULL;

  l->primeiro = NULL;
  l->tamanho = 0;

  return l;
}

//---------------------------------------------------------------------------
// desaloca a lista l e todos os seus nós
//
// se destroi != NULL invoca
//
//     destroi(conteudo(n))
//
// para cada nó n da lista.
//
// devolve 1 em caso de sucesso,
//      ou 0 em caso de falha
int destroi_lista(lista l, int destroi(void *)) {

  no p;
  int ok=1;

  while ( (p = primeiro_no(l)) ) {

    l->primeiro = proximo_no(p);

    if ( destroi )
      ok &= destroi(conteudo(p));

    free(p);
  }

  free(l);

  return ok;
}

//---------------------------------------------------------------------------
// insere um novo nó na lista l cujo conteúdo é p
//
// devolve o no recém-criado
//      ou NULL em caso de falha
no insere_lista(void *conteudo, lista l) {

  no novo = malloc(sizeof(struct no));

  if ( ! novo )
    return NULL;

  novo->conteudo = conteudo;
  novo->proximo = primeiro_no(l);
  ++l->tamanho;

  return l->primeiro = novo;
}

//------------------------------------------------------------------------------
// remove o no de endereço rno de l
// se destroi != NULL, executa destroi(conteudo(rno))
// devolve 1, em caso de sucesso
//         0, se rno não for um no de l
int remove_no(struct lista *l, struct no *rno, int destroi(void *)) {
	int r = 1;
	if (l->primeiro == rno) {
		l->primeiro = rno->proximo;
		if (destroi != NULL) {
			r = destroi(conteudo(rno));
		}
		free(rno);
		l->tamanho--;
		return r;
	}
	for (no n = primeiro_no(l); n->proximo; n = proximo_no(n)) {
		if (n->proximo == rno) {
			n->proximo = rno->proximo;
			if (destroi != NULL) {
				r = destroi(conteudo(rno));
			}
			free(rno);
			l->tamanho--;
			return r;
		}
	}
	return 0;
}

/*
 *******************************************************************************
 * Meu código começa aqui.
 *******************************************************************************
 */

#include <graphviz/cgraph.h>
#define _XOPEN_SOURCE
#include <string.h>

typedef unsigned int uint;
typedef long int lint;
typedef unsigned short ushort;
typedef int bool;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#ifndef NULL
#define NULL			0
#endif

#define ERRO(fmt, ...)       (fprintf(stderr, (fmt), ## __VA_ARGS__))

struct grafo {
	uint 	nvertices;
	uint 	narestas;
	bool	ponderado;
	int		padding;
	char*	nome;
	lista	vertices;
};

struct vertice {
	char*	nome;
	lista	vizinhos_esq;
	lista	vizinhos_dir;
};
typedef struct vertice* vertice;

struct aresta {
	char*	nome;
	vertice	origem;
	vertice	destino;
};
typedef struct aresta* aresta;

grafo* alloc_grafo(void);
char* str_dup(const char* str);



grafo* alloc_grafo(void) {
	grafo* g = (grafo*)calloc(1, sizeof(struct grafo));
	return g;
}

char* str_dup(const char* str) {
	char* p = (char*)calloc(1, strlen(str)+1);
	if( p )
		strcpy(p, str);

	return p;
}
//------------------------------------------------------------------------------
// lê um grafo no formato dot de input, usando as rotinas de libcgraph
//
// desconsidera todos os atributos do grafo lido exceto o atributo
// "peso" quando ocorrer; neste caso o valor do atributo é o peso da
// aresta/arco que é um long int
//
// num grafo com pesos todas as arestas/arcos tem peso
//
// o peso default é 0
//
// todas as estruturas de dados alocadas pela libcgraph são
// desalocadas ao final da execução
//
// devolve o grafo lido
//      ou NULL em caso de erro
grafo le_grafo(FILE *input) {
    Agraph_t*	Ag_g;
    grafo       g;

    g = (grafo)alloc_grafo();
    Ag_g = agread(input, NULL);
    if ( !Ag_g ) {
        free(g);
        ERRO("Não foi possível ler o grado!\n");
        return NULL;
    }

    g->nome = str_dup(agnameof(Ag_g));
    g->ponderado = agisdirected(Ag_g);
    g->nvertices= (uint)agnnodes(Ag_g);
    g->narestas = (uint)agnedges(Ag_g);
    g->vertices = constroi_lista();
    constroi_grafo(Ag_g, g);
    /*
    for( Ag_v=agfstnode(Ag_g); Ag_v; Ag_v=agnxtnode(Ag_g, Ag_v) ) {
        v = (vertice)mymalloc(sizeof(struct vertice));
        memset(v, 0, sizeof(struct vertice));
        v->v_nome = strdup(agnameof(Ag_v));
        v->v_lbl  = (int*)mymalloc(sizeof(int) * g->g_nvertices);
                memset(v->v_lbl, 0, sizeof(int) * g->g_nvertices);
        v->v_neighborhood_in = constroi_lista();
        v->v_neighborhood_out = constroi_lista();
        // Insert vertex to the list of vertexes in the graph list.
        if( !insere_lista(v, g->g_vertices) ) exit(EXIT_FAILURE);
    }

    BuildList build_list[2];
    build_list[0] = BuildListOfEdges;
    build_list[1] = BuildListOfArrows;
    for( Ag_v=agfstnode(Ag_g); Ag_v; Ag_v=agnxtnode(Ag_g, Ag_v) )
        build_list[g->g_tipo](g, Ag_g, Ag_v, agnameof(Ag_v));
    */
    agclose(Ag_g);
    return g;
}

void constroi_grafo(Agraph_t* ag, grafo g) {
	for( Agnode_t* v=agfstnode(ag); v; v=agnxtnode(ag, v) ) {
		ver = alloc_vertice(agnameof(v));

	}
}

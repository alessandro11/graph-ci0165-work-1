void print_v(grafo g) {
        no n;
        struct vertice* v;
        lista l = g->vertices;

        printf("Grafo %s=%p\n", g->nome, g);
        for( n=primeiro_no(l); n; n=proximo_no(n) ) {
                v = conteudo(n);
                printf("%s=%p\n", v->nome, v);
                printf("\tV. Ent.:\n");
                print_a(v->vizinhos_esq);
//                printf("\tV. Sai.:\n");
//                print_a(v->vizinhos_esq);
        }
        fflush(stdout);
}

void print_a(lista l) {
    no n;
    struct aresta* a;

    n=primeiro_no(l);
    if( n ) {
        a = conteudo(n);
        printf("\taresta=%p\n", a);
        printf( "\t(%s=%p, %s=%p)\n",\
				a->origem->nome, a->origem,
				(a->destino != 0) ? a->destino->nome : "NULL", a->destino );
        for( n=proximo_no(n); n; n=proximo_no(n) ) {
            a = conteudo(n);
            printf("\taresta=%p\n", a);
            printf( "\t(%s=%p, %s=%p)\n",\
					a->origem->nome, a->origem,
					(a->destino != 0) ? a->destino->nome : "NULL", a->destino );
        }
    }
    fflush(stdout);
}

vertice busca_vertice(const char* nome_calda,
		const char* nome_cabeca, lista l, vertice* cabeca) {
	no n;
	vertice v, calda;

	calda = *cabeca = 0;
	for( n=primeiro_no(l); n && (! calda || ! *cabeca); n=proximo_no(n) ) {
		v = (vertice)conteudo(n);
		if( strcmp(nome_calda, v->nome) == 0 )
			calda = v;
		else if( strcmp(nome_cabeca, v->nome) == 0 )
			*cabeca = v;
	}

	return calda;
}

int busca_aresta(vertice v, vertice calda, vertice cabeca) {
	no n;
	aresta a;

	for( n=primeiro_no(v->vizinhos_esq); n; n=proximo_no(n) ) {
		a = (aresta)conteudo(n);
		if( (a->origem == calda && a->destino == cabeca) ||
			(a->origem == cabeca && a->destino == calda ) )
			return 1;
	}

	return 0;
}

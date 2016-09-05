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


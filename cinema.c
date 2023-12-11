#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cat{
    char Nome[20];
    int sala; 
    int hora;
    int min;
    int lotacao;
    int LOTMAX;
    struct cat *proxno;
} NO;

typedef struct cliente{
    char nome[20];
    struct cat *ingresso;
} USU;


/*void cadastra_cliente(USU **c, char nome[20]){
    USU *aux, *c1 = malloc(sizeof(USU));

    if (c1) {
        //p1->Nome = nome; Em C, você não pode atribuir diretamente um array a outro. Você precisa copiar cada elemento individualmente.
        strcpy(c1->nome, nome);
        
        printf("| Cliente cadastrado! | \n");
        if (*c == NULL) {
            *c = c1;
        } 
        else {
            aux = *c;
            while(aux->prox){
                aux = aux->prox;
            }
            aux->prox = c1;
        }   
    } else {
        printf("| Erro ao alocar memoria! |");
    }
}*/
/*void cadastra_cliente(USU **c, char nome[20]){
    USU *c1 = malloc(sizeof(USU));

    if (c1) {
        //p1->Nome = nome; Em C, você não pode atribuir diretamente um array a outro. Você precisa copiar cada elemento individualmente.
        strcpy(c1->nome, nome);
        *c = c1;
        printf("| Cliente cadastrado! | \n");
    }
}*/


void compra_ingresso(NO *p, USU *c, char nome[20], int sala){
    if ( p == NULL){
        return(0);
    } else {
        do {
        if (p->Nome == nome && p->sala == sala){
            c->ingresso = p;
            p->lotacao += 1;
            return(1);
        } else{
            p = p->proxno;
        }
            
        } while ( p != NULL );
    return(0);
} } 

void cadastra_cliente(USU *c, char *nome) {
    strcpy(c->nome, nome);
}



void adiciona_filme(NO **p, char nome[20], int sala, int hora, int min){
    NO *aux, *p1 = malloc(sizeof(NO));

    if (p1) {
        //p1->Nome = nome; Em C, você não pode atribuir diretamente um array a outro. Você precisa copiar cada elemento individualmente.
        strcpy(p1->Nome, nome);
        p1->sala = sala;
        p1->hora = hora;
        p1->min = min;
        p1->LOTMAX = 50;
        p1->lotacao = 0;
        p1->proxno = NULL;
        printf("| Inclusao bem sucedida! | \n");
        if (*p == NULL) {
            *p = p1; 
        } 
        else {
            aux = *p;
            while(aux->proxno){
                aux = aux->proxno;
            }
            aux->proxno = p1;
        }   
    } else {
        printf("| Erro ao alocar memoria! |");
    }
}

void remove_filme(NO **p, char nome[20], int sala){
    NO *aux = *p;
    NO *prev = NULL;

    // Procura o filme na lista
    while (aux != NULL) {
        if (strcmp(aux->Nome, nome) == 0 && aux->sala == sala) {
            break;
        }
        prev = aux;
        aux = aux->proxno;
    }

    // Se o filme não foi encontrado
    if (aux == NULL) {
        printf("Filme não encontrado!\n");
        return;
    }

    // Se o filme é o primeiro da lista
    if (prev == NULL) {
        *p = aux->proxno;
    } else {
        prev->proxno = aux->proxno;
    }

    free(aux);
    printf("Filme removido com sucesso!\n");
}

void lista_salas(NO *p) {
    while (p != NULL) {
        if (p->sala != NULL) {
        printf("_____________________________\n");
        printf("  %s\n Sala: %d | Sessao: %d:%d\n Lotacao (%d/%d)\n",p->Nome,p->sala,p->hora,p->min, p->lotacao, p->LOTMAX);
        printf("_____________________________\n");
        }
        p = p->proxno;
    }
}

void lista_filmes ( NO *p ) {
        printf(" CATALOGO DE FILMES \n\t");
        printf("____________________\n");
    while (p != NULL) {
        
        if (p->sala != NULL) {
        
        printf("|-%s          \n\t", p->Nome);
        printf("____________________\n");
        }

        p = p->proxno;
    } 
}
void imprimir_ingresso(USU *c) {
    struct cat *ingresso = c->ingresso;
    printf("Nome: %s\n", ingresso->Nome);
    printf("Sala: %d\n", ingresso->sala);
    printf("Hora: %d:%d\n", ingresso->hora, ingresso->min);
    printf("Lotação: %d/%d\n", ingresso->lotacao, ingresso->LOTMAX);
}
void menu_Funcionario(NO **p){
        int in;
        char nome[20];
        int sala, hora, min;
        

        NO *p1 = NULL; 
        do{
            printf(" Cine SyStem - Funcionario\n");
            printf("___________________________\n");
            printf("1 - Adicionar Filme\n");
            printf("2 - Remover Filme\n");
            printf("3 - Listar Salas\n");
            printf("4 - Listar Filmes\n");
            printf("5 - Sair \n");  
            printf("___________________________\n");
            scanf("%d", &in);
            getchar();
            switch(in){
                case 1:                         
                        printf("Filme: ");
                        fgets(nome, sizeof(nome), stdin);
                        //nome[strcspn(nome, "\n")] = 0;  
                        getchar();
                        printf("Sala: ");
                        scanf("%d", &sala);
                        getchar();
                        printf("Hora:");
                        scanf("%d", &hora);
                        getchar();
                        printf("Minuto:");
                        scanf("%d", &min);
                        getchar();                        
                        adiciona_filme(&p1,nome,sala,hora,min);
                        printf("Ta certo isso?");
                        break;
                
                case 2: 
                        printf("Nome do filme: ");
                        scanf("%s", &nome);
                        getchar();
                        printf("Sala: ");
                        scanf("%d", &sala);
                        getchar();
                        remove_filme(&p1, nome, sala);
                        break;
               
                case 3: 
                        lista_salas(p1);
                        break;
                
                case 4: 
                        lista_filmes(p1);
                        break;
            }

        } while(in != 5);
        
        
}

void menu_Cliente(NO **p ,USU **c){
        int in, sala;
        char nome[20];
        char filme[20];
        NO *p1 = NULL;
        USU *c1 = NULL;
        p = malloc(sizeof(NO));
        //c = malloc(sizeof(USU));
        do{

        
        printf("Cine SyStem - Cliente\n");
        printf("----------------\n");
        printf("1 - Comprar Ingressos\n");
        printf("2 - Comprovante Ingresso\n");
        printf("3 - Listar Salas\n");
        printf("4 - Listar Filmes\n");
        printf("5 - Sair \n");
        scanf("%d", &in);

        switch(in){
                case 1:
                        printf("  Cine SyStem - Cliente\n");
                        printf("__________________________\n");
                        printf("Nome Cliente: ");
                    //    fgets(nome, sizeof(nome), stdin);                       
                    //    getchar();
                    //    cadastra_cliente(c1,nome);
                        printf("Filme: ");
                        fgets(filme, sizeof(filme), stdin);
                        getchar();
                        printf("Sala:");
                        scanf("%d", &sala);
                        getchar();
                        printf("Antes cadastra cliente\n");
                        
                        printf("Antes compra ingresso\n");
                        compra_ingresso(p1,c1,filme,sala);
                        printf("Antes do break\n");
                        break;
                case 2:
                        printf("_____________________________\n");
                        imprimir_ingresso(c1);
                        printf("_____________________________\n");
                case 3: 
                        lista_salas(p1);
                        break;
                case 4: 
                        lista_filmes(p1);
                        break;
        }

        } while(in != 5);
}

main(){

    NO *p = NULL;
    USU *c = NULL;
    char nome[20];

    p = malloc(sizeof(NO));
    c = malloc(sizeof(USU));
    int in;
    do{
    printf(" ____________________\n");
    printf("|    Cine SyStem     |\n");
    printf("|--------------------|\n");
    printf("| 1 - Cliente        |\n");
    printf("| 2 - Funcionario    |\n");
    printf("| 3 - Sair           |\n");
    printf("|____________________|\n");
    scanf("%i", &in);
    getchar();
        switch(in){
            case 1:
                printf("Nome Cliente: ");
                fgets(nome, sizeof(nome), stdin);
                getchar();
                cadastra_cliente(c, nome);
                menu_Cliente(p,c);
                break;
            case 2:
                menu_Funcionario(p);
                break;
        }   
    } while(in != 3);
}

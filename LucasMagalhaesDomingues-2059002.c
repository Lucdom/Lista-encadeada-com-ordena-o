# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

struct No{
	char nome[30];
	struct No *prox;
};
typedef struct No No;

void inicializar(No *p);

int verificar(No *p);

void inserir(No *p,char *nome);

void imprimir(No *p);

void buscar1(No *p,char *nome);

No *retirar(No *p);

void liberar(No *p);

void bubblesort(No *p,int tam);

void selectionsort(No *p,int tam);

void buscabin(No *p,char *nome,int tam);

clock_t tempo[2];

int clock1,clock2,clock3,clock4;

double tempoGasto;

int main(){
	FILE *f;
	int escolha,i,tipo,tam;
	char nomeaux[30];
	No *p;
	p=(No *)malloc(sizeof(No));
	inicializar(p);
	for (i=0;i<1;i--){
		printf("Digite 1 para carregar arquivo.\n");
		printf("Digite 2 para inserir novo nome.\n");
		printf("Digite 3 para remover nome.\n");
		printf("Digite 4 para buscar nome.\n");
		printf("Digite 5 para ordenar os nomes.\n");
		printf("Digite 6 para imprimir os nome.\n");
		printf("Digite 7 para gerar relatório.\n");
		printf("Digite 8 para sair do programa.\n");
		scanf("%d",&escolha);
		switch (escolha){
			case 1:
				printf("\n");
				f=fopen("ed-1000.txt","r");
				tempo[0]=clock();
				while (!feof(f)){
					fgets(nomeaux,30,f);
					nomeaux[strlen(nomeaux)-1]=0;
					inserir(p,nomeaux);
				}
				tempo[1]=clock();
				clock1=(tempo[1]-tempo[0])*1000.0 / CLOCKS_PER_SEC;
				fclose(f);
			break;
			case 2:
				printf("\n");
				printf("Digite o nome que deseja inserir:\n");
				setbuf(stdin,NULL);
				gets(nomeaux);
				inserir(p,nomeaux);
				printf("\n");
				printf("Inserido!\n");
				printf("\n");
			break;
			case 3:
				printf("\n");
				retirar(p);
			break;
			case 4:
				printf("\n");
				printf("Digite 0 para busca sequêncial.\n");
				printf("Digite qualquer outra tecla para busca binária.\n");
				scanf("%d",&tipo);
				if (tipo==0){
					printf("\n");
					printf("Digite o nome que deseja buscar:\n");
					setbuf(stdin,NULL);
					gets(nomeaux);
					buscar1(p,nomeaux);
					printf("\n");	
				}
				else{
					printf("\n");
					printf("Digite o nome que deseja buscar:\n");
					setbuf(stdin,NULL);
					gets(nomeaux);
					tam=pegartamanho(p);
					buscabin(p,nomeaux,tam);
					printf("\n");
				}
			break;
			case 5:
				printf("\n");
				printf("Digite 0 para ordenação bubble sort.\n");
				printf("Digite qualquer outra tecla para ordenação e impressao do selection sort.\n");
				scanf("%d",&tipo);
				if (tipo==0){
					printf("\n");
					tam=pegartamanho(p);
					bubblesort(p,tam);
				}
				else{
					printf("\n");
					tam=pegartamanho(p);
					selectionsort(p,tam);
					imprimir(p);
					tempo[1]=clock();
					clock4=(tempo[1]-tempo[0])*1000.0 / CLOCKS_PER_SEC;
				}
			break;
			case 6:
				printf("\n");
				imprimir(p);
			break;
			case 7:
				printf("\n");
				f=fopen("relatorio.txt","w");
				fprintf(f,"Leitura do arquivo e inserção na estrutura: %g ms.\n",clock1);
				fprintf(f,"Busca binaria para nome existente: %g ms.\n",clock2);
				fprintf(f,"Busca binaria para nome nao existente: %g ms.\n",clock3);
				fprintf(f,"Ordenacao e impressao no console: %g ms.\n",clock4);
				fprintf(f,"Total: %g ms.\n",clock1+clock2+clock3+clock4);
				fclose(f);
			break;
			case 8:
				printf("\n");
				i=2;
				printf("Sistema encerrado.\n");
				liberar(p);
				printf("Memoria liberada.\n");
			break;
		}		
	}
	return 0;
}

void inicializar(No *p){
	p->prox=NULL;
}

int verificar(No *p){
	if(p->prox==NULL)
  		return 1;
 	else
 		return 0;
}

void inserir(No *p,char *nome){
	No *novo=(No *)malloc(sizeof(No));
	strcpy(novo->nome,nome);
	novo->prox=NULL;
	if(verificar(p)){
		p->prox=novo;
	}
	else{
  		No *tmp=p->prox;
  	while(tmp->prox!=NULL){
   		tmp=tmp->prox;
   	}
  	tmp->prox=novo;
	}
}

void imprimir(No *p){
	if (verificar(p)){
		printf("A estrutura está vazia.\n");
		printf("\n");
	}
	else{
		No *tmp=p->prox;
		while(tmp!=NULL){
			printf("%s\n",tmp->nome);
			tmp=tmp->prox;
   		}
	}
	printf("\n");
}

void buscar1(No *p,char *nome){
	if (verificar(p)){
		printf("A estrutura está vazia.\n");
		printf("\n");
	}
	else{
		No *tmp=p->prox;
		while(tmp!=NULL){
			if (strcmp(tmp->nome,nome)==0){
				printf("\n");
				printf("Nome encontrado.\n");
				return;
			}
			tmp=tmp->prox;
   		}
   		printf("\n");
   		printf("Nome não foi encontrado.\n");
	}
}

No *retirar(No *p){
	if(verificar(p)){
  		printf("A estrutura está vazia.\n");
  		printf("\n");
  		return p;
 	}
 	No *aux1=p;
 	No *aux2=p->prox;
	char busca[30];
	printf("Digite o nome que deseja buscar:\n");
	setbuf(stdin,NULL);
	gets(busca);
	while(aux2!=NULL && strcmp(aux2->nome,busca)!=0){
		aux1=aux2;
		aux2=aux2->prox;
	}
	if (aux2!=NULL){
    	aux1->prox=aux2->prox;
    	free(aux2);
    	printf("\n");
		printf("Nome removido!\n");
		printf("\n");
		return;
   	}
   	printf("\n");
	printf("Nome não encontrado!\n");
	printf("\n");
}

void liberar(No *p){
    No *aux=p;
    while (aux!=NULL){
    	No *t=aux->prox;
    	free(aux);
    	aux=t;
	}
}

int pegartamanho(No *p){
	int i=0;
	if (verificar(p)){
		return 0;
	}
	else{
		No *tmp=p->prox;
		while(tmp!=NULL){
			i++;
			tmp=tmp->prox;
   		}
	}
	return i;
}

void bubblesort(No *p,int tam){
	No *tmp=p;
	int j;
	char aux[30];
	for (j=0;j<tam-1;j++){
		tmp=p->prox;
		while (tmp->prox!=NULL){
			if (strcmp(tmp->nome,tmp->prox->nome)>0){
				strcpy(aux,tmp->nome);
				strcpy(tmp->nome,tmp->prox->nome);
				strcpy(tmp->prox->nome,aux);
			}
		tmp=tmp->prox;
		}
	}
}

void selectionsort(No *p,int tam){
	char teste[30];
	No *tmp=p;
	No *aux=p;
	int i;
	tempo[0]=clock();
	for (i=0;i<tam;i++){
		while (aux!=NULL){
			while (tmp!=NULL){
				if (strcmp(tmp->nome,aux->nome)>0){
					strcpy(teste,tmp->nome);
					strcpy(tmp->nome,aux->nome);
					strcpy(aux->nome,teste);
				}
			tmp=tmp->prox;
		}
		aux=aux->prox;
		tmp=p->prox;
		}
	}
}

void buscabin(No *p,char *nome,int tam){
	No *tmp=p;
	int i;
	int inicio=0,meio,fim=tam-1;
	tempo[0]=clock();
	while (inicio<=fim){
		meio=(inicio+fim)/2;
		for (i=0;i<meio;i++){
			tmp=tmp->prox;
		}
		if (strcmp(nome,tmp->nome)<0){
			fim=meio-1;
		}
		else{
			if (strcmp(nome,tmp->nome)>0){
				inicio=meio+1;
			}
			else{
				printf("Encontrado.\n");
				tempo[1]=clock();
				clock2=(tempo[1]-tempo[0])*1000.0 / CLOCKS_PER_SEC;
				return;
			}
		}
		tmp=p;
	}
	printf("Nao foi encontrado.\n");
	tempo[1]=clock();
	clock3=(tempo[1]-tempo[0])*1000.0 / CLOCKS_PER_SEC;
}

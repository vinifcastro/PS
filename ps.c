// Vinicius de Freitas Castro 202103783
// Lucas Bernardes Feitosa 202103751

#include "ps.h"

int verifica_vazia(Fila * fila){
    if(fila == NULL) return 1;
    else return 0; 
}

void enfileira_pessoa_ps(Fila ** fila, char * nome, int idade, char * sintomas, int gravidade){
    Fila *prox, *aux, *novo = NULL;
    novo = (Fila *) malloc(sizeof(Fila));
    if(novo){
        novo->idade = idade;
        novo->proximo = NULL;
        novo->gravidade = gravidade;
        strcpy(novo->nome, nome);
        strcpy(novo->sintomas, sintomas);
        if(*fila == NULL)
            *fila = novo;
        else{
            if(novo->gravidade > (*fila)->gravidade){
                novo->proximo = *fila;
                *fila = novo;
            }
            else{
                aux = *fila;
                prox = aux->proximo;
                while(aux->proximo && (prox->gravidade >= novo->gravidade) ) {
                    aux = aux->proximo;
                    prox = aux->proximo;
                }
                aux->proximo = novo;
                novo->proximo = prox;
            }
        }
    }
    else printf("Erro ao criar posicao na fila!\n");
}

void enfileira_pessoa_triagem(Fila **fila, char * nome, int idade){
    Fila *aux, *novo = (Fila *) malloc(sizeof(Fila));
    if(novo){
        strcpy(novo->nome, nome);
        novo->idade = idade;
        novo->gravidade = 0;
        novo->sintomas[0] = '\0';
        novo->proximo = NULL;
        if(*fila == NULL)
            *fila = novo;
        else{
            if(idade > 59){
                if((*fila)->idade < 60){
                    novo->proximo = *fila;
                    *fila = novo;
                }
                else{
                    aux = *fila;
                    while(aux->proximo && aux->proximo->idade > 59)
                        aux = aux->proximo;
                    novo->proximo = aux->proximo; 
                    aux->proximo = novo;
                }
            }
            else{
                aux = *fila;
                while(aux->proximo)
                    aux = aux->proximo;
                aux->proximo = novo;
            }
        }
    }
    else
        printf("\nErro ao alocar memoria.\n");
}

void desenfileirar(Fila ** fila, int triagem, Fila ** filaps, Fila * maca){
    Fila * aux = NULL;
    int gravidade = 0;
    char sintomas[300];
    char vazia[10] = { "(Vazia) \0" };
    if(*fila){
        aux = *fila;
        *fila = (*fila)->proximo;
        if(triagem){
          while(gravidade<1 || gravidade > 3){
            system("clear");
            printf("Paciente ' %s | Idade: %d '\n", aux->nome, aux->idade);
            printf("Digite uma gravidade para o paciente (De 1 a 3): ");
            scanf("%d%*c", &gravidade);
            if(gravidade<1 || gravidade>3) {
              printf("Gravidade digitada invalida! Pressione enter para tentar novamente...\n");
              getchar();
            }
          }
          printf("Digite os sintomas do paciente: ");
          scanf("%[^\n]%*c", sintomas);
          enfileira_pessoa_ps(filaps, aux->nome, aux->idade, sintomas, gravidade);
          printf("Paciente ' %s ' enviado para fila de atendimento.\n", aux->nome);
        }
        if (triagem == 0) {
          while(gravidade<1 || gravidade > 40) {
            system("clear");
            printf("Em qual maca deseja inserir o paciente (1-40): ");
            scanf("%d%*c", &gravidade);
            if(gravidade<1 || gravidade>40) {
              printf("Maca digitada invalida! Pressione enter para tentar novamente...\n");
              getchar();
            }
          }
          if(strcmp(maca[gravidade-1].nome, vazia) != 0){
            printf("A maca ja esta ocupada, tente novamente.\n");
            *fila = aux;
          }
          else{
            printf("Paciente ' %s ' enviado para a maca %d.\n", aux->nome, gravidade);
            maca[gravidade-1] = *aux;
            free(aux);
            maca[gravidade-1].proximo = NULL;
            }
          }
    }
    else printf("Erro ao tentar remover paciente da fila, pois esta vazia!\n");
}

void libera_fila(Fila ** fila){
    Fila * aux;
    if (*fila == NULL){
        free(*fila);
        return;
    }
    aux = *fila;
    while((*fila)->proximo){
        *fila = (*fila)->proximo;
        free(aux);
        aux = *fila;
    }
    aux = *fila;
    free(aux);
}

void mostra_fila(Fila *fila){
    if (verifica_vazia(fila)){
        printf("Fila Vazia!\n");
        return;
    }
    printf("\n\nQuantidade de pessoas na fila: %d.\n\n", qtd_fila(fila));
    printf("\t------------- Inicio da Fila -------------\t\n\n");
    while(fila->proximo){
        printf("' Nome: %s | Idade: %02d | Gravidade: %02d '\n", fila->nome, fila->idade, fila->gravidade);
        fila = fila->proximo;
    }
    printf("' Nome: %s | Idade: %02d | Gravidade: %02d '", fila->nome, fila->idade, fila->gravidade);
    printf("\n\n\t------------- Final da Fila -------------\t\n");
}

int qtd_fila(Fila *fila){  
    int qtd = 1;
    Fila * aux = NULL;
    if (verifica_vazia(fila)) return 0;
    aux = fila;
    while(aux->proximo){
        qtd++;
        aux = aux->proximo;
    }
    return qtd;
}

void mostramapa(Fila *maca){
  int i, k;
  char c;
  printf("\t\t\t MAPA DE OCUPACAO\n\n");
  for(i=0; i<QTDMACA;i++){
    printf("%02d. ", i+1);
    k=0;
    c = maca[i].nome[k];
    while((c!=' ') && (c != '\0')){
      c = maca[i].nome[k];
      printf("%c", c);
      k++;
    }
    printf("| ");
    if((i+1)%5==0) printf("\n");
  }
}  

void guia(void){
  printf("Bem Vindo ao programa de PS (Pronto Socorro)!\n\n");
  printf("O programa funciona da seguinte maneira:\n");
  printf("1 - Ao receber um paciente voce deve primeiramente inseri-lo (opcao 1) na fila de triagem, necessitando apenas de dados simples como nome e idade.\n");
  printf("1.1 - Pacientes que possuem 60 anos ou mais possuem prioridade na fila, sendo assim, serao atendidos primeiro.\n\n");
  printf("2 - Apos inserir o paciente na fila da triagem, sera realizado um exame para definir a gravidade do problema e sua descricao, esse processo sera realizado ao remover o paciente da fila de triagem (opcao 3 - 1), e apos o diagnostico ele sera mandado para a fila de atendimento do pronto socorro.\n");
  printf("2.1 - Apos serem diagnosticados pacientes que possuem maior gravidade em seu diagnostico possuem prioridade de atendimento, logo, serao atendidos primeiro.\n\n");
  printf("3 - Apos ser atendido pelo pronto socorro, o paciente sera mandado para uma maca. Este processo ocorre ao remover (opcao 3 - 0) o paciente da fila de pronto socorro.\n\n");
  printf("4 - Quando o paciente for redirecionado para uma maca e possivel ver o mapa das macas que estao disponiveis no PS (opcao 4 - 0). Caso a maca esteja ocupada sera mostrado apenas o primeiro nome do paciente que a ocupa.\n");
  printf("4.1 - E possivel visualizar todas as informacoes do paciente ao informar o numero de sua maca (opcao 4 - 1). Informacoes disponiveis: Nome, Idade, Gravidade e Sintomas. A busca pela maca para exibir essas informações é feita a partir de um algoritmo de busca binária.\n\n");
  printf("5 - Uma vez que todo o processo de atendimento for concluido a Alta Medica sera dada ao paciente (opcao 5). Este processo ocorre ao liberar a maca em que o paciente esta residindo, possibilitando novamente a utilizacao daquela maca.\n\n");
  printf("6 - Realiza a busca no mapa de macas (de forma sequencial). Em busca do nome do paciente. Caso encontre, retorna a maca cujo o nome foi encontrado, caso contrario retorna que o paciente nao se encontra em nenhuma maca.\n");
  printf("7 - Mostra a lista que contem todos os pacientes que foram liberados para ir de alta pelo médico plantonista do dia. Orderna eles por nome ou por gravidade.\n");
}

void pesquisalistabin(Fila * a, int num){
    int inicio=0, meio, fim=QTDMACA-1;
    char vazia[10] = { "(Vazia) \0" };
    num--;
    do{
      meio = (inicio+fim)/2;
      if(meio == num){
        if(strcmp(vazia, a[meio].nome) == 0) {printf("A maca esta vazia, sem informacoes de pacientes.\n");}
            else{
              printf("\n---------------------\t\nMACA %d\n\nPaciente: %s\nIdade: %02d\nGravidade: %02d\nSintomas: %s\n---------------------\n", meio+1, a[meio].nome, a[meio].idade, a[meio].gravidade, a[meio].sintomas);
              }
        return;
      }
      else if(meio<num) inicio = meio+1;
      else if(meio>num) fim = meio-1;
    }while(fim>=inicio);
    printf("O elemento nao esta na a.\n");
}

void buscanomeseq(Fila * maca, char * nome){
  int i;
  for(i=0;i<QTDMACA;i++){
    if(strcmp(nome, maca[i].nome) == 0){
      printf("O paciente: ' %s ' esta na maca de numero ' %d '.\n", nome, i+1);
      return;
    }
  }
  printf("O paciente: ' %s ' nao se encontra em nenhuma maca.\n", nome);
}

void printalta(Alta x){
  int i;
  system("clear");
  if(x.tam==0) {
    printf("Lista de alta médica vazia.\n");
    getchar();
  }
  else{
    for(i=0;i<x.tam;i++){
      printf("\n---------------------\nPaciente: %s\nIdade: %02d\nGravidade: %02d\nSintomas: %s", x.alta[i].nome, x.alta[i].idade, x.alta[i].gravidade, x.alta[i].sintomas);
    }
    printf("\n---------------------\n");
  }
}

void quick_sort(Fila *a, int inicio, int fim){
    int i, j;
    Fila y, x;
     
    i = inicio;
    j = fim;
    x = a[(inicio + fim) / 2];
     
    while(i <= j) {
        while(a[i].idade < x.idade && i < fim) {
            i++;
        }
        while(a[j].idade > x.idade && j > inicio) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > inicio) {
        quick_sort(a, inicio, j);
    }
    if(i < fim) {
        quick_sort(a, i, fim);
    }
}

void select_sort(Fila * a, int n){
    int i, tam, j;
    Fila aux;
    
    for (i=1;i<n;i++) {
        aux = a[i];
        j = i-1;
 
        while (j >= 0 && a[j].gravidade > aux.gravidade) {
            a[j+1] = a[j];
            j = j-1;
        }
        
        a[j+1] = aux;
    }

}
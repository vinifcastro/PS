// Vinicius de Freitas Castro 202103783
// Lucas Bernardes Feitosa 202103751

#include "ps.h"

int main(){
  Fila * ps = NULL, * triagem = NULL;
  int opcao,idade,op;
  char nome[80];
  Fila maca[QTDMACA];
  Alta alta;
  char vazia[10] = { "(Vazia) \0" };
  for(op=0; op<QTDMACA; op++) strcpy(maca[op].nome, vazia);
  alta.tam = 0;
  do{
    system("clear");
    printf("\t\tMENU\n\n\t1 - Adiciona um paciente a fila de triagem.\n\t2 - Mostra fila.\n\t3 - Remove da fila.\n\t4 - Mostrar mapa de macas.\n\t5 - Liberar maca (Alta medica).\n\t6 - Busca paciente pelo nome.\n\t7 - Mostrar Lista das Altas Medicas.\n\t8 - Guia sobre o programa.\n\n\t0 - Finaliza programa.\n\n");
    printf("Digite uma opcao: ");
    scanf("%d%*c", &opcao);
    system("clear");
    switch(opcao){
      case 1:
        printf("\tTRIAGEM\n\nDigite o nome completo do paciente: ");
        scanf("%[^\n]%*c",nome);
        printf("\nDigite a idade do paciente: ");
        scanf("%d%*c",&idade);
        enfileira_pessoa_triagem(&triagem,nome,idade);
        break;

      case 2:
        printf("Qual fila deseja ver? (1 - Triagem | 0 - PS): ");
        scanf("%d%*c",&op);
        if(op==1) mostra_fila(triagem);
        else if(op==0) mostra_fila(ps);
        else printf("Opcao invalida!\n");
        break;

      case 3:
        printf("De qual fila deseja remover? (1 - Triagem | 0 - PS): ");
        scanf("%d%*c",&op);
        if(op==1) desenfileirar(&triagem,op,&ps, maca);
        else if(op==0) desenfileirar(&ps,op,&ps, maca);
        else printf("Opcao invalida!\n");
        break;
      
      case 4:
        mostramapa(maca);
        printf("Deseja ver informacoes especificas sobre determinado paciente? (1 - Sim | 0 - Nao): ");
        scanf("%d%*c", &op);
        if(op == 1){
            printf("Digite o numero da maca que deseja saber mais informacoes: ");
            scanf("%d%*c", &idade);
            if(idade <= QTDMACA && idade >= 1){
              pesquisalistabin(maca, idade);
            }
          else printf("Maca selecionada invalida!\n");
          }
        else if(op == 0)printf("Retornando ao menu.\n");
        else printf("Opcao invalida!\n");
        break;
      
      case 5:
        mostramapa(maca);
        printf("Digite o numero do paciente que foi liberado pelo medico (01-40): ");
        scanf("%d%*c", &op);
        if(op>QTDMACA || op<1) printf("Maca selecionada invalida.\n");
        else{
          if(strcmp(maca[op-1].nome, vazia)!=0){
          alta.alta[alta.tam] = maca[op-1];
          alta.tam++;
          strcpy(maca[op-1].nome, vazia);
          printf("Paciente da maca %d removido com sucesso. (Alta medica)\n", op);
          }
          else printf("Esta maca ja esta vazia!\n");
        }
        break;
      case 6:
        printf("Digite o nome do paciente que deseja buscar nas macas: ");
        scanf("%[^\n]%*c",nome);
        buscanomeseq(maca, nome);
        break;
      case 8:
        guia();
        break;
      
      case 7:
        printalta(alta);
        printf("Deseja ver a lista ordenada de qual modo?\n");
        printf("1 - Ordenada por Idade\n");
        printf("2 - Ordenada por Gravidade\n\n");
        printf("--> ");
        scanf("%d%*c",&op);
        
        
        if(op == 1){
          quick_sort(alta.alta, 0, alta.tam-1);
        }
        else if (op == 2){
          select_sort(alta.alta, alta.tam);
        }
        else printf("Opcao invalida!\n");
        printalta(alta);
        
        break;
      
      default:
        if(opcao) printf("Opcao invalida!\n");
        else printf("Finalizando programa...\n");
        break;

    }
    if(opcao){
      printf("\nPRESSIONE ENTER PARA CONTINUAR.\n"); 
      getchar();
    }
    else sleep(1);
  
  }while(opcao);
  libera_fila(&triagem);
  libera_fila(&ps);
  return 0;
}
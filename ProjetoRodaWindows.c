#include <stdio.h> //blibiotecas
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

FILE *Alunos;

typedef struct //struct
{
    int matricula;
    float nota1;
    float nota2;
    float nota3;
    float nota4;
    char Nome[40];
    int Cod_Turma; 
    int frequencia;
}disciplina;

disciplina func[30]; //vetor de struct

void menu(int i); //protótipos de função
void cadastro();
void submenu_cadastro();
void auxmenu_remocao();
void remover();
void submenu_remocao();
void auxmenu_atualizar();
void atualizar();
void submenu_atualizar();
void alunos();
void aprovados();
void reprovados_media();
void reprovados_falta();
void menuslistas();
void auxmenu_ordenacao();
int cont();
float mediadenota(float nota1, float nota2, float nota3, float nota4);
void Troca(int j, int i);
void cresce_matricula();
void decre_matricula();
void media_cresce();
void media_decresce();
void faltascresce();
void faltasdecresce();
void nomeaz();
void nomeza();
void sinc();
int sincro();



//MENU DE OPÇÕES
void menu(int i)
{
  iniciar: // rótulo para o goto iniciar do case 12 e 13, serve pra quando uma função chamar o menu novamente, ele irá rodar o menu desde o começo das informações.

  //printf para o menu, ele explica o que deve ser digitado, escolhi números em vez da própria string pois diminui os erros que podem ocorrer.
  printf("Digite o numero da operacao a ser executada:\n1 Para cadastrar aluno.\n2 Para remover aluno.\n3 Para atualizar dados de um aluno.\n4 Para listar alunos cadastrados.\n5 Para listar alunos aprovados.\n6 Para listar alunos reprovados por média.\n7 Para listar alunos reprovados por faltas.\n8 Para iniciar a organização da lista.\n9 Para sincronizar os dados da memória.\n10 Para sincronizar os dados da memória e sair.\n11 Para sair sem sincronizar.\n");

  retornar: // rótulo de goto para se houver um número inválido.

  scanf("%i", &i);

  switch(i) //menu para os itens de 2 a 11, há um novo item que é o 13, mas ele foi incrementado apenas para a chamada de função, não sabia se deveria deixar vísivel ao usuário.
  {
    case 1:
    system("cls"); //system cls para a tela ficar mais limpa, foi colocado em cada opção.
    cadastro();
    break;
    case 2:
    system("cls");
    auxmenu_remocao();
    break;
    case 3:
    system("cls");
    auxmenu_atualizar();
    break;
    case 4:
    system("cls");
    alunos();
    break;
    case 5:
    system("cls");
    aprovados();
    break;
    case 6:
    system("cls");
    reprovados_media();
    break;
    case 7:
    system("cls");
    reprovados_falta();
    break;
    case 8:
    system("cls");
    auxmenu_ordenacao();
    break;
    case 9:
    sinc();
    printf("Sincronizado com sucesso!\n"); // case para sincronizar o menu
    menu(12);
    break;
    case 10:
    sinc();
    printf("Sincronizado com sucesso! Saindo...\n"); //case para sincronizar o menu e sair
    sleep(3);
    return;
    case 11: //case apenas para sair
    return;
    case 12:
    system("cls");
    printf("A ação de retorno ao menu foi um sucesso!\n"); // case de reinicio do menu, não visivel ao usuário
    goto iniciar;//goto com rótulo no ínicio do menu.
    case 13:
    goto iniciar; //função de reinicio mais escondia, usado na main
    break;
    default:
    printf("ERRO: Valor inválido, por favor digite novamente.\n"); //default pede para repetir o valor, foi usado um goto com o rótulo antes do scan.
    goto retornar; // aqui o goto sendo usado.
    break;
  }
}

//FUNÇÃO DE CADASTRO DE ALUNO, APENAS 1 POR VEZ.
void cadastro()
{   
  char condicional;

  int matric, contador =0; //matric para entrada de matricula e contador para mensagem de erro de turma cheia.
  printf("digite a matrícula do aluno\n");
  matricula_err:
  scanf("%i", &matric);
  if(matric>2021099 || matric<2021000) //checa se o número está dentro das normas
  {
    printf("Número Inválido de Matrícula, é permitido apenas 20210xx, Por favor digite novamente:\n");
    goto matricula_err;
  }
        
  for(int i = 0; i<30; i++) //aqui nós temos um for com dois if, um serve para transmitir a mensagem de erro de matrículas iguas se necessário, o outro conta quantos espaços do vetor estão cheios para depois transmitir a mensagem de erro de turma cheia se estiver.
  {
    if(matric==func[i].matricula) 
    {
      printf("ERRO: já existe um aluno com essa matricula\n\n");
      submenu_cadastro();
      return;
    }
    if(func[i].matricula!=0) 
    {
      contador++;
    }
  }

  if(contador==30) //if para se a turma estiver cheia ele dar o erro e ir para o submenu de cadastro.
  {
    printf("ERRO: Turma cheia.\n\n");
    submenu_cadastro();
    return;
  }

  for(int i=0; i<30; i++) //Por fim se não tiver tido nenhum dos erros acima ele vai normalmente para o cadrasto, irá igualar a variável matric a parte de matricula na struct, e também irá fazer os scanf das outras informações.
  {
    if(func[i].matricula==0)
    {
      func[i].matricula=matric;

      nota1: // rótulo usado para goto da nota1.
      printf("Digite a primeira nota:\n");
      scanf("%f", &func[i].nota1);
      if(func[i].nota1>10 || func[i].nota1 < 0)
      {
        printf("ERRO: Primeira nota com valor inválido, digite novamente:\n");
        goto nota1;     // Aqui foi usado goto com um if para se qualquer valor de nota passado não for 0<nota<10 o código pedir para repetir.
      }

      nota2:
      printf("Digite a segunda nota:\n");
      scanf("%f", &func[i].nota2);
      if(func[i].nota2>10 || func[i].nota2 < 0)
      {
        printf("ERRO: Segunda nota com valor inválido, digite novamente:\n");
        goto nota2;     // mesma lógica da nota1, apenas muda a variável.
      }

      nota3:
      printf("Digite a terceira nota:\n");
      scanf("%f", &func[i].nota3);
      if(func[i].nota3>10 || func[i].nota3 < 0)
      {
        printf("ERRO: Terceira nota com valor inválido, digite novamente:\n");
        goto nota3;     // mesma lógica da nota1, apenas muda a variável.
      }

      nota4:
      printf("Digite a quarta nota:\n");
      scanf("%f", &func[i].nota4);
      if(func[i].nota4>10 || func[i].nota4 < 0)
      {
        printf("ERRO: Quarta nota com valor inválido, digite novamente:\n");
        goto nota4;     // mesma lógica da nota1, apenas muda a variável.
      }
            
      printf("Digite o nome do aluno:\n");
      getchar();
      gets(func[i].Nome);

      printf("Digite o código da turma:\n");
      scanf("%i", &func[i].Cod_Turma);
            
      faltas:
      printf("Número de faltas do aluno:\n");
      scanf("%i", &func[i].frequencia);
      if(func[i].frequencia>36 || func[i].frequencia < 0)
      {
        printf("ERRO: Número de faltas com valor inválido, digite novamente:\n");
        goto faltas;    // mesmo goto usado na nota1, com a diferença de que aqui é até 36 faltas.
      }

      Alunos = fopen("Alunos.txt", "a"); //Abertura do arquivo singular, apenas o cadastro abre o arquivo com "a" pois apenas ele precisa escrever na ultima linha.
      if(Alunos == NULL)
      {
        printf("ERRO: falha ao salvar dados do aluno no sistema\n");
      }
      else
      {
        printf("Sucesso Ao abrir dados da turma, gravando dados do aluno...\n");
        sleep(2);
      }

      fprintf(Alunos, "%i\n", func[i].matricula);
      fprintf(Alunos, "%.2f\n", func[i].nota1);
      fprintf(Alunos, "%.2f\n", func[i].nota2);
      fprintf(Alunos, "%.2f\n", func[i].nota3);
      fprintf(Alunos, "%.2f\n", func[i].nota4);
      fprintf(Alunos, "%s\n", func[i].Nome);
      fprintf(Alunos, "%i\n", func[i].Cod_Turma);
      fprintf(Alunos, "%i\n\n", func[i].frequencia);


      fclose(Alunos);
      matric=0;
      submenu_cadastro(); //aqui vai para o submenu.
      return;
    }
  }
}

//SUBMENU PARA FINALIZAÇÃO DE CADASTRO DE ALUNO.
void submenu_cadastro() //submenu para a finalização do cadastro, é isso, quando acaba o cadastro ele vem para cá, serve para limpar o código mas antes poder ler informações.
{
  int i;
  printf("Cadastro finalizado !\nDigite 1 para continuar cadastrando.\nDigite 2 para voltar ao menu.\nDigite 3 para finalizar o código.\n");
  scanf("%i", &i);

  retorno:
  switch (i)
  {
    case 1 :
    system("cls");
    cadastro();
    break;
    case 2 :
    system("cls");
    menu(12);
    case 3 :
    printf("Finalizando...\n");
    sleep(3);
    break;
    default:
    printf("ERRO: Número inválido, digite novamente.\n");
    goto retorno;
    break;
  }
  return;
}

//MENU AUXILIAR DA REMOÇÃO DE CADASTRO.
void auxmenu_remocao() //Mostra alunos cadastrados para remoção, e se não houver alunos cadastrados finaliza a remoção.
{
  int contador=0;
  printf("No momento existem esses cadastrados que podem ser removidos:\n\n");

  for(int i=0; i<30; i++)
  {
    if(func[i].matricula!=0)
    {
      printf("Matrícula: %i\nNome: %s\n\n", func[i].matricula, func[i].Nome);
      contador++;
    }
  }
  if(contador==0)
  {
    printf("Ops, parece que ainda não há alunos cadastrados.\n");
    submenu_remocao();
  }
  else
  {
    remover();
  }
  return;
}

//FUNÇÃO DE REMOÇÃO DE CADASTRO DE ALUNO.
void remover()
{
  char condicional, tempnome[40]="\0";
  int matricula, contador=0; //variável para procurar a matrícula na struct.
  
  while(matricula > 2021099 || matricula < 2021000) //checa se a matricula tem o valor certo
  {
    printf("Digite a matricula do aluno a ter o cadastro removido:\n(Obs: para cancelar a ação digite 0)\n");
    scanf("%i", &matricula);
    if(matricula==0)
    {
      break;
    }
    if(matricula > 2021099 || matricula < 2021000 )
    {
      printf("ERRO: Valor Inválido de matrícula!\n");
    }
  }

  if(matricula==0) //matricula de valor 0 cancela a ação, foi usado um goto
  {
    printf("Operação cancelada com sucesso!\n");
    goto finale;
  }

  for(int i=0; i<30; i++)
  {
    if(func[i].matricula==matricula) //como ele reconhece 0 como nada na matrícula, eu apenas igualei tudo a 0 e esse conjunto já pode ser usado de novo para cadastro.
    {
      func[i].matricula=0;
      func[i].nota1=0;
      func[i].nota2=0;
      func[i].nota3=0;
      func[i].nota4=0;
      strcpy(func[i].Nome, tempnome); //igualo a string a uma com valor nulo.
      func[i].Cod_Turma=0;
      func[i].frequencia=0;
      contador++;
      break;
    }
  }

  if(contador==0) //erro de matricula não encontrada nos dados
  {
    printf("ERRO: Não foi encontrado nenhum aluno com essa matrícula.\n");
    goto finale;
  }
  sinc();
  
  finale:
  submenu_remocao();
  return;
}

//SUBMENU PARA FINALIZAÇÃO DE REMOÇÃO DE CADASTRO.
void submenu_remocao()// menu de finalização da remoção, bem parecido com o submenu do cadastro.
{
  int i;
  printf("A remoção foi finalizada!\nDigite 1 Para retornar a tela de remoção.\nDigite 2 para voltar ao menu.\nDigite 3 para finalizar o código.\n");

  retorna:
  scanf("%i", &i);

  switch (i)
  {
    case 1:
    system("cls");
    auxmenu_remocao();
    break;
    case 2:
    system("cls");
    menu(12);
    break;
    case 3:
    break;   
    default:
    printf("Número inválido, digite novamente.\n");
    goto retorna;
    break;
  }
  return;
}

// MENU AUXILIAR DE ATUALIZAÇÃO DE CADASTRO.
void auxmenu_atualizar() //Cópia do menu auxiliar de remoção, apenas com chamadas diferentes.
{
  int contador=0;
  char opcao;
  printf("No momento existem esses cadastrados que podem ser atualizados:\n\n");

  for(int i=0; i<30; i++)
  {
    if(func[i].matricula!=0)
    {
      printf("Matrícula: %i\nNome: %s\n", func[i].matricula, func[i].Nome);
      contador++;
    }
  }
  if(contador==0)
  {
    printf("Ops, parece que ainda não há alunos cadastrados.\n");
    submenu_atualizar();
  }
  else
  {
    atualizar();
  }
  return;
}

//FUNÇÃO DE ATUALIZAÇÃO DE DADOS DE UM CADASTRO.
void atualizar()
{
  int matricula, contador; //variável para matrícula novamente
  while(matricula > 2021099 || matricula < 2021000) //checa se a matricula tem o valor certo
  {
    printf("Digite a matricula do aluno a ter o cadastro Atualizado:\n(Obs: para cancelar a ação digite 0)\n"); //while para apontar erro de valor inválido.
    scanf("%i", &matricula);
    if(matricula==0)
    {
      break;
    }
    if(matricula > 2021099 || matricula < 2021000 )
    {
      printf("ERRO: Valor Inválido de matrícula!\n");
    }
  }

  if(matricula==0) //
  {
    printf("Cancelado com Sucesso!\n");
    goto finale;
  }

  for(int i=0; i<30; i++) //aqui procura a matrícula dentro da struct igual a informada para atualizar os dados dos alunos.
  {
    if(func[i].matricula==matricula)
    {
      do //foi utilizado do while nas funções para valores inválidos de nota ou faltas
      {
        printf("Digite a primeira nota:\n");
        scanf("%f", &func[i].nota1);
        if(func[i].nota1 > 10 || func[i].nota1 < 0)
        {
          printf("Número Inválido de nota, o permitido é de 0 a 10.\n");
        }
      }while(func[i].nota1 > 10 || func[i].nota1 < 0);
      
      do
      {
        printf("Digite a segunda nota:\n");
        scanf("%f", &func[i].nota2);
        if(func[i].nota2 > 10 || func[i].nota2 < 0)
        {
          printf("Número Inválido de nota, o permitido é de 0 a 10.\n");
        }
      }while(func[i].nota2 > 10 || func[i].nota2 < 0);
      
      do
      {
      printf("Digite a terceira nota:\n");
      scanf("%f", &func[i].nota3);
        if(func[i].nota3 > 10 || func[i].nota3 < 0)
        {
          printf("Número Inválido de nota, o permitido é de 0 a 10.\n");
        }
      }while(func[i].nota3 > 10 || func[i].nota3 < 0);
      
      do
      {
      printf("Digite a quarta nota:\n");
      scanf("%f", &func[i].nota4);
        if(func[i].nota4 > 10 || func[i].nota4 < 0)
        {
          printf("Número Inválido de nota, o permitido é de 0 a 10.\n");
        }
      }while(func[i].nota4 > 10 || func[i].nota4 < 0);

      do
      {
      printf("Digite o número de faltas:\n");
      scanf("%i", &func[i].frequencia);
        if(func[i].frequencia > 36 || func[i].frequencia < 0)
        {
          printf("Número Inválido de faltas, o permitido é de 0 a 36.\n");
        }
      }while(func[i].frequencia > 36 || func[i].frequencia < 0);
      
      sinc();
      break;
    }
  }

  if(contador==0)
  {
    printf("ERRO: Matrícula não foi encontrada na memória, aluno não está cadastrado.\n");
  }

  finale:
  submenu_atualizar();
  return;
}

//MENU DE FINALIZAÇÃO DA ATUALIZAÇÃO DE CADASTRO.
void submenu_atualizar() //é para cá que o user vai ser redirecionado na finalização do cadastro.
{
  int i;
  printf("A Atualização de cadastro foi finalizada!\nDigite 1 Para retornar a tela de atualização.\nDigite 2 para voltar ao menu.\nDigite 3 para finalizar o código.\n");

  retorna:
  scanf("%i", &i);

  switch (i)
  {
    case 1:
    system("cls");
    auxmenu_atualizar();
    break;
    case 2:
    system("cls");
    menu(12);
    break;
    case 3:
    break;   
    default:
    printf("Número inválido, digite novamente.\n");
    goto retorna;
    break;
  }
  return;
}

//LISTAR ALUNOS CADASTRADOS.
void alunos()
{
  int turma, contador=0;

  printf("Sincronização Iniciada...\n");
  sincro();

  printf("Digite o codigo da turma\n");
  scanf("%i", &turma);

  printf("Todos os alunos com esse codigo de turma:\n");

  for(int i=0; i<30; i++)//For com um if para listar apenas alunos daquela turma.
  {
    if(func[i].Cod_Turma==turma)
    {
      printf("Matrícula: %i\nPrimeira nota: %.2f\nSegunda nota: %.2f\nTerceira nota:%.2f\nQuarta nota:%.2f\nFaltas:%i\n\n", func[i].matricula, func[i].nota1, func[i].nota2, func[i].nota3, func[i].nota4, func[i].frequencia);
      contador++;
    }
  }
  if(contador==0)
  {
    printf("Ops, Não há alunos nessa turma.\n");
  }
  menuslistas();
  return;
}

//LISTAR ALUNOS APROVADOS.
void aprovados()
{
  int turma, frequencia, contador=0; //variável para procurar a turma e para calcular a frequência.
  float media;
  printf("Sincronização Iniciada...\n");
  sincro();

  printf("Digite o Código da turma:\n");
  scanf("%i", &turma);

  for(int i=0; i<30; i++) //usado para percorrer a struct.
  {
    if(func[i].Cod_Turma==turma)
    {
      media = (func[i].nota1+func[i].nota2+func[i].nota3+func[i].nota4)/4.0; //calculo da média
      frequencia = ((36-func[i].frequencia)*100)/36; //calculo da frequência com base nas faltas.

      if( media>=7 && frequencia>=60)
      {
        printf("Matrícula: %i\n", func[i].matricula);
        printf("Média: %.2f\n", media);
        printf("Frequência: %i%%\n\n", frequencia);
        contador++;
      }
    }
  }
  if(contador==0)
  {
    printf("Ops, Não há alunos aprovados.\n");
  }
  menuslistas();
  return;
}

//LISTAR ALUNOS REPROVADOS POR MÉDIA.
void reprovados_media() //aqui não tem muito o que falar, é quase o inverso de aprovados, só muda que não tem frequência.
{
  int turma, contador=0;
  float media; 

  printf("Sincronização Iniciada...\n");
  sincro();

  printf("Digite o Código da turma:\n");
  scanf("%i", &turma);

  for(int i=0; i<30; i++)
  {
    media = (func[i].nota1+func[i].nota2+func[i].nota3+func[i].nota4)/4.0;

    if(func[i].Cod_Turma==turma)
    { 
      if( media<=7)
      {
        printf("Matrícula: %i\n", func[i].matricula);
        printf("Média: %.2f\n\n", media);
        contador++;
      }
    }
  }
  if(contador==0)
  {
    printf("Ops, Não há alunos reprovados por média.\n");
  }
  menuslistas();
  return;
}    

//LISTAR ALUNOS REPROVADOS POR FALTA.
void reprovados_falta()
{
  int turma, frequencia, contador=0; //o mesmo do código de média, a diferença é que esse é por frequência.

  printf("Sincronização Iniciada...\n");
  sincro();

  printf("Digite o Código da turma:\n");
  scanf("%i", &turma);

  for(int i=0; i<30; i++)
  {
    if(func[i].Cod_Turma==turma)
    {
      frequencia = ((36-func[i].frequencia)*100)/36;

      if(frequencia<=60)
      {
        printf("Matrícula: %i\n", func[i].matricula);
        printf("Frequência: %i%%\n\n", frequencia);
        contador++;
      }
    }
  }
  if(contador==0)
  {
    printf("Ops, Não há alunos reprovados por falta.\n");
  }
  menuslistas();
  return;
}

//MENU DE FINALIZAÇÃO DAS LISTAS DE ALUNO.
void menuslistas()
{
  int i;
  printf("Operação realizada com Sucesso!!\nDigite 1 para listar cadastros\nDigite 2 para listar aprovados\nDigite 3 para listar reprovados por média\nDigite 4 para listar reprovados por falta.\nDigite 5 para voltar ao menu.\n");

  retorno:
  scanf("%i", &i);

  switch (i)
  {
    case 1:
    system("cls");
    alunos();
    break;
    case 2:
    system("cls");
    aprovados();
    break;
    case 3:
    system("cls");
    reprovados_media();
    break;
    case 4:
    system("cls");
    reprovados_falta();
    break;
    case 5:
    system("cls");
    menu(12);
    break;
    default:
    printf("Número Inválido, Por favor digite novamente:\n");
    goto retorno;
    break;
  }
  return;
}

//ORDENAÇÃO DE ARQUIVOS
//MENU AUXILIDAR DE ORDENAÇÃO
void auxmenu_ordenacao()
{
  int opcao1, opcao2;
  printf("A ordenação vai acontecer por qual tipo de dado?\nDigite 1 se for por Matrícula.\nDigite 2 se for por média.\nDigite 3 se for por quantidade de faltas.\nDigite 4 se for por nome.\nDigite 5 para voltar ao menu.\n");

  do
  {
    scanf("%i", &opcao1);

    switch(opcao1)
    {
      case 1:
      printf("Decrescente ou Crescente ?\n1 para Crescente e 2 para Decrescente.\n");
      scanf("%i", &opcao2);
      if(opcao2==1)
      {
        cresce_matricula();
      }
      if(opcao2==2)
      {
        decre_matricula();
      }
      system("cls");
      break;
      case 2:
      printf("Decrescente ou Crescente ?\n1 para Crescente e 2 para Decrescente.\n");
      scanf("%i", &opcao2);
      if(opcao2==1)
      {
        media_cresce();
      }
      if(opcao2==2)
      {
        media_decresce();
      }      
      break;
      case 3:
      printf("Decrescente ou Crescente ?\n1 para Crescente e 2 para Decrescente.\n");
      scanf("%i", &opcao2);
      if(opcao2==1)
      {
        faltascresce();
      }
      if(opcao2==2)
      {
        faltasdecresce();
      }      
      break;
      case 4:
      printf("Alfabética de A até Z ou Z até A ?\n1 para de A até Z e 2 para de Z até A.\n");
      scanf("%i", &opcao2);
      if(opcao2==1)
      {
        nomeaz();
      }
      if(opcao2==2)
      {
        nomeza();
      }
      break;
      case 5:
      system("cls");
      menu(12);
      break;
      default:
      printf("Número Inválido, por favor digite novamente:\n");
    }
  }while(opcao1>5 || opcao1 < 0);
  return;
}

//CONTAGEM DE ALUNOS
int cont() //conta os alunos válidos
{
  int quantidade_de_alunos=0;

  for(int i=0; i<30;i++)
  {
    if(func[i].matricula!=0)
    {
      quantidade_de_alunos++;
    }
  }
  return quantidade_de_alunos;
}

//CONTAGEM DE MÉDIA
float mediadenota(float nota1, float nota2, float nota3, float nota4) //conta as médias dos alunos
{
  float media;
  media = (nota1+nota2+nota3+nota4)/4;
  return media;
}

//FUNÇÃO PARA TROCA
void Troca(int j, int i) //serve apenas para a troca nas ordenações dos dados
{
  int tempmatr, tempnota1, tempnota2, tempnota3, tempnota4, tempturma, tempfaltas;
  char tempnome[40];

  tempmatr =func[j].matricula;
  tempnota1 =func[j].nota1;
  tempnota2 =func[j].nota2;
  tempnota3 =func[j].nota3;
  tempnota4 =func[j].nota4;
  strcpy(tempnome, func[j].Nome);
  tempturma =func[j].Cod_Turma;
  tempfaltas =func[j].frequencia;

  func[j].matricula = func[i].matricula;
  func[j].nota1 = func[i].nota1;
  func[j].nota2 = func[i].nota2;
  func[j].nota3 = func[i].nota3;
  func[j].nota4 = func[i].nota4;
  strcpy(func[j].Nome, func[i].Nome);
  func[j].Cod_Turma = func[i].Cod_Turma;
  func[j].frequencia = func[i].frequencia;

  func[i].matricula = tempmatr;
  func[i].nota1 = tempnota1;
  func[i].nota2 = tempnota2;
  func[i].nota3 = tempnota3;
  func[i].nota4 = tempnota4;
  strcpy(func[i].Nome, tempnome);
  func[i].Cod_Turma = tempturma;
  func[i].frequencia = tempfaltas;


  return;
}

//ORDENAÇÃO DE MATRICULA CRESCENTE
void cresce_matricula()//ordenação crescente em bubble sorting
{
  int i, j;

  for(int i=0; i<cont(); i++)
  {
    for(int j=0; j< cont()-i-1; j++)
    {
      if(func[j].matricula>func[j+1].matricula && func[j+1].matricula!=0)
      {
        Troca(j , j+1);
      }
    }
  }

  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(12);
  return;
}

//ORDENAÇÃO DE MATRICULA CRESCENTE
void decre_matricula() //ordenação decrescente em bubble sorting
{
  int i, j;

  for(i=0; i<cont(); i++)
  {
    for(j=0; j< cont()-i-1; j++)
    {
      if(func[j].matricula<func[j+1].matricula && func[j+1].matricula!=0)
      {
        Troca(j+1 , j);
      }
    }
  }
  
  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(10);
  return;
}

//ORDENAÇÃO DE MÉDIA CRESCENTE
void media_cresce() //ordenação crescente em buble sorting
{
  int i, j;

  for(i=0; i < cont(); i++)
  {
    for(j=0; j < cont()-i-1; j++)
    {
      if(mediadenota(func[j].nota1, func[j].nota2, func[j].nota3, func[j].nota4) > mediadenota(func[j+1].nota1, func[j+1].nota2, func[j+1].nota3, func[j+1].nota4) && func[j+1].matricula !=0)
      {
        Troca(j+1, j);
      }
    }
  }
  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(10);
  return;
}

//ORDENAÇÃO DE MÉDIA DECRESCENTE
void media_decresce() //ordenação decrescente em buble sorting
{
  int i, j;

  for(i=0; i < cont(); i++)
  {
    for(j=0; j < cont()-i-1; j++)
    {
      if(mediadenota(func[j].nota1, func[j].nota2, func[j].nota3, func[j].nota4) < mediadenota(func[j+1].nota1, func[j+1].nota2, func[j+1].nota3, func[j+1].nota4) && func[j+1].matricula !=0)
      {
        Troca(j+1, j);
      }
    }
  }
  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(10);
  return;
}

//FUNÇÃO DE ORDENAÇÃO POR QUANTIDADE DE FALTAS CRESCENTE
void faltascresce() //ordenação crescente de faltas em selection sort
{
  int i, j, max;

  for(i=0; i<cont(); i++)
  {
    max = 0;

    for(j=1; j< cont()-i; j++)
    {
      if(func[j].frequencia > func[max].frequencia)
      {
        max = j;
      }
    }
   Troca(max, (cont()-i-1)); 
  }

  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(10);
  return;
}

//FUNÇÃO DE ORNDENAÇÃO POR QUANTIDADE DE FALTAS DECRESCENTE
void faltasdecresce() //ordenação decrescente de faltas em selection sort
{
  int i, j, max;

  for(i=0; i<cont(); i++)
  {
    max = 0;

    for(j=1; j< cont()-i; j++)
    {
      if(func[j].frequencia < func[max].frequencia)
      {
        max = j;
      }
    }
   Troca(max, (cont()-i-1)); 
  }

  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(10);
  return;
}

//FUNÇÃO DE ORDENAÇÃO POR NOME ALFABÉTICO DE A ATÉ Z
void nomeaz() //ordenação de nomes em bubble sort
{
  int i, j;

  for(i=0; i < cont(); i++)
  {
    for(j=0; j < cont()-i-1; j++)
    {
      if(strcmp(func[j].Nome, func[j+1].Nome) > 0)
      {
        Troca(j+1, j);
      }
    }
  }
  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(10);
  return;  
}

//FUNÇÃO DE ORDENAÇÃO POR NOME ALFABÉTICO DE A ATÉ Z
void nomeza()  //ordenação de nome em bubble sort
{
  int i, j;

  for(i=0; i < cont(); i++)
  {
    for(j=0; j < cont()-i-1; j++)
    {
      if(strcmp(func[j].Nome, func[j+1].Nome) < 0)
      {
        Troca(j+1, j);
      }
    }
  }
  printf("Operação realizada com sucesso! Sincronizando dados e retornando ao menu...\n");
  sleep(2);
  sinc();
  menu(10);
  return;  
}

//FUNÇÃO PARA SINCRONIZAR O ARQUIVO DE TEXTO COM O BUFFER
void sinc() //função para sincronizar arquivo no buffer
{
  Alunos = fopen("Alunos.txt", "w");

  if(Alunos == NULL)
  {
    printf("ERRO: falha ao sincronizar com o sistema\n");
  }
  else
  {
    printf("Sucesso Ao abrir dados da turma, Iniciando sincronização...\n");
  }  
  sleep(2);

  for(int i=0; i<30; i++)
  {
    if(func[i].matricula != 0)
    {
      fprintf(Alunos, "%i\n", func[i].matricula);
      fprintf(Alunos, "%.2f\n", func[i].nota1);
      fprintf(Alunos, "%.2f\n", func[i].nota2);
      fprintf(Alunos, "%.2f\n", func[i].nota3);
      fprintf(Alunos, "%.2f\n", func[i].nota4);
      fputs(func[i].Nome, Alunos);
      fprintf(Alunos, "%i\n", func[i].Cod_Turma);
      fprintf(Alunos, "%i\n\n", func[i].frequencia);
    }
  }

  printf("A sincronização foi um sucesso!\n");
  sleep(2);

  fclose(Alunos);
  system("cls");
  return;
}

//FUNÇÃO PARA SINCRONIZAR O BUFFER COM O ARQUIVO DE TEXTO
int sincro() //sincronizar os dados temporários no arquivo
{
  int contador=0;

  system("cls");

  Alunos = fopen("Alunos.txt", "r");

  if(Alunos == NULL)
  {
    printf("ERRO: falha ao tentar abrir dados iniciais da turma\n");
    return 1;
  }
  else
  {
    printf("Sucesso Ao abrir dados da turma, Iniciando leitura de dados:\n");
  }


  while(contador != 110) // contador apenas para decoração
  {
    printf("%i%% Concluído!\n", contador);
    sleep(1/2);
    contador= contador+10;
  }

  printf("Sucesso ao ler dados!\n");

  sleep(3);

  system("cls");

  for(int i=0; i<30; i++)
  {
    fscanf(Alunos, "%i\n", &func[i].matricula);
    fscanf(Alunos, "%f\n", &func[i].nota1);
    fscanf(Alunos, "%f\n", &func[i].nota2);
    fscanf(Alunos, "%f\n", &func[i].nota3);
    fscanf(Alunos, "%f\n", &func[i].nota4);
    fgets(func[i].Nome, 40, Alunos);
    fscanf(Alunos, "%i\n", &func[i].Cod_Turma);
    fscanf(Alunos, "%i\n\n", &func[i].frequencia);
  }

  fclose(Alunos);
  return 0;
}

//FUNÇÃO MAIN PARA DAR CLEAN EM WARNS E LER TODO O CÓDIGO ANTES DE RODA-LO.
int main() 
{
  int contador=0;
  char condicional;

  system("cls");
  for(int i=0; i<30; i++) //For para definir todas as matrículas para 0, assim quando não houver uma matrícula ela será igual a 0, facilitando mensagens do tipo erro turma cheia.
  {
    func[i].matricula=0;
  }

  printf("Já há dados guardados no sistema de arquivos ? S ou N\n");
  scanf("%c", &condicional);

  if(condicional=='S' || condicional == 's')
  {
    if(sincro()==1)
    {
      return 0;
    }
  }
  else
  {
    Alunos = fopen("Alunos.txt", "w");

    if(Alunos == NULL)
    {
      printf("ERRO: Não foi possível criar arquivo de dados.");
    }
    else
    {
      printf("Arquivo de Dados criado com sucesso.\n");
    }

    sleep(2);
    system("cls");
    fclose(Alunos);
  }
  menu(13);
  return 0;
}


/****
*Titulo: Trabalho Final: UESCFLIX
*Autores: Diego Farias de Freitas
*Data de Criacao: 15/11/2021
*Ultima modificacao: 03/12/2021

*descricao: O programa e uma plataforma de streaming onde o usuario tem a possibilidade de realizar diversas
            acoes, como: inserir conteudos, lista-los, exclui-los, modificar suas notas e buscar o conteudo
            pelo ID, titulo ou tipo.
****/

//Inclusao das bibliotecas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

/****
*titulo: CADASTRO (struct cadastro_item)
*Data de Criacao: 15/11/2021
*Ultima modificacao: 16/11/2021

*Descricao: Armazena os dados inseridos pelos usarios.

****/
typedef struct cadastro_item CADASTRO;
struct cadastro_item{
    int id, ano, tipo;
    char titulo[100];
    float nota;
};

// DECLARACAO DAS FUNCOES
void interface();
void inserir_item();
void tipo_conteudo();
int cont_ID();
void listar();
void excluir();
void mudar_nota();
void buscar_ID();
void buscar_titulo();
void listar_tipo(char *nome[15]);
// FIM DAS DECLARACOES DAS FUNCOES

FILE *ARQUIVO; //Ponteiro que "aponta" para a localizacao de um registro.

//Optamos por deixar a funcao MAIN mais limpa, entao ela ficou responsavel por chamar as demais funcoes e realizar algumas.
    int main(){

        setlocale(LC_ALL,"Portuguese"); // Permitindo o uso de pontuacoes da lingua portuguesa
        int opcao_menu; //Variavel que armazena a opcao escolhida pelo usuario no MENU.
        int opcao_tipoFilme;
        char nome_tipoFilme[15];//Variavel que armazena a STRING do tipo do conteudo.
        CADASTRO novo_cadastro;

        do{
                interface();
                printf ("\n[1] Inserir um novo item no catalogo\n");
                printf ("[2] Listar itens, em ordem, do catalogo\n");
                printf ("[3] Excluir um item do catalogo\n");
                printf ("[4] Modificar a nota de um item informado\n");
                printf ("[5] Buscar itens atraves do ID\n");
                printf ("[6] Buscar itens atraves do titulo\n");
                printf ("[7] Listar itens com base no tipo\n");
                printf ("[8] Sair\n\n");
                printf ("Digite a opcao desejada: ");
                scanf ("%d", &opcao_menu);
                system("cls");

            //Inicio do swicth principal.
            switch(opcao_menu){
                case 1:
                    //Inserir um novo item no catalogo.
                    inserir_item();
                break;

                case 2:
                    //Listar todos os itens do catalogo ordenados pela chave prim�ria.
                    listar();
                break;

                case 3:
                    //Excluir um item do catalogo com base na chave prim�ria.
                    excluir();
                break;

                case 4:
                    //Modificar o campo nota de um item a partir da chave prim�ria.
                    mudar_nota();
                break;

                case 5:
                    //Buscar itens a partir da chave prim�ria.
                    buscar_ID();
                break;

                case 6:
                    //buscar itens a partir do titulo.
                    buscar_titulo();
                break;

                case 7:
                    //Listar itens com base no tipo.
                    interface();
                    tipo_conteudo();
                    printf ("\nDigite a opcao desejada: ");
                    //variavel responsavel por guardar a opcao do tipo do item escolhido a ser listado.
                    scanf ("%d", &opcao_tipoFilme);

                        //inicio do switch
                        switch(opcao_tipoFilme){

                        //Dentro desse switch, em cada um dos casos, o strcpy copiar� a string do tipo � variavel
                        //"nome_tipoFilme" que ser� passado para a funcao.
                            case 1:
                                strcpy(nome_tipoFilme,"filme");
                                listar_tipo(nome_tipoFilme);
                                break;

                            case 2:
                                strcpy(nome_tipoFilme,"serie");
                                listar_tipo(nome_tipoFilme);
                                break;

                            case 3:
                                strcpy(nome_tipoFilme,"documentario");
                                listar_tipo(nome_tipoFilme);
                                break;

                            default:
                                system("cls");
                                printf ("opcao invalida, tente novamente!\n");
                                getch();
                        } // fim do segundo SWITCH
                break;

                case 8:
                    interface();
                    printf ("Obrigado por nos escolher!\nAtt: UESCLIX\n");
                    getch();
                break;

                default:
                    interface();
                    printf ("opcao invalida. Tente novamente!\n");
                    getch();
                break;
            } // fim do primeiro SWITCH

        }while(opcao_menu != 8); // Fim do laço DO WHILE (iniciado na linha 56)

    return 0;
    }

/****
*titulo: interface().
*Data de criacao: 15/11/2021
*ultima modificacao:15/11/2021

*descricao: Imprime o layout do programa, dando boas vindas.

****/

void interface(){
    system ("cls");
    printf ("\t\t\t\t\t======================\n");
    printf ("\t\t\t\t\tBEM VINDO A UESCFLIX\n");
    printf ("\t\t\t\t\t======================\n\n");
}

/****
*titulo: tipo_conteudo().
*Data de criacao: 15/11/2021
*ultima modificacao:15/11/2021

*descricao: Mostra ao usuario as categorias dos itens que podem ser listados.

****/

void tipo_conteudo(){
    printf("\n---- CATEGORIAS ----\n");
    printf("\n--> 1 Filmes\n--> 2 Series\n--> 3 Documentarios\n");
}

/****
*titulo: inserir_item().
*Data de criacao: 15/11/2021
*ultima modificacao:20/11/2021

*descricao: A funcao usa variáveis do tipo struct para armazenar o conteudo informado pelo usuario e, apos isso,
            grava no arquivo.

****/

void inserir_item(){

    CADASTRO novo_cadastro;
    novo_cadastro.id = cont_ID();

    ARQUIVO = fopen("itens.dat", "a+");

            if (ARQUIVO == NULL){
                printf ("Erro ao abrir o arquivo...\n");
                exit(1);
            }else{
                do{
                    system ("cls");
                    interface();

                    fflush (stdin);
                    printf ("Digite o titulo: ");
                    scanf ("%[^\n]",novo_cadastro.titulo);
                    fflush(stdin);

                    tipo_conteudo();
                    printf ("\nDigite a opcao desejada: ");
                    scanf ("%d", &novo_cadastro.tipo);

                    printf("\nDigite o ano de lancamento: ");
                    scanf("%d", &novo_cadastro.ano);

                    printf("\nDigite uma nota para o conteudo: ");
                    scanf("%f", &novo_cadastro.nota);
                    system("cls");

                    //verifica se a nota está entre 1 e 5.
                    if(novo_cadastro.nota < 1 || novo_cadastro.nota > 5){
                        printf("ERRO! Informe uma nota entre 1 � 5 !!");
                    }else{
                        printf ("\nDeseja continuar?\n-->(1)sim\n-->(2)nao\n-->");

                        fprintf (ARQUIVO, "%d@", novo_cadastro.id);
                        fputs (novo_cadastro.titulo, ARQUIVO);

                            if(novo_cadastro.tipo == 1){
                                fprintf (ARQUIVO, "@%s", "filme");
                            }
                            else if(novo_cadastro.tipo == 2){
                                fprintf (ARQUIVO, "@%s", "serie");
                            }
                            else if(novo_cadastro.tipo == 3){
                                fprintf (ARQUIVO, "@%s", "documentario");
                            }

                        fprintf (ARQUIVO, "@%d", novo_cadastro.ano);
                        fprintf (ARQUIVO, "@%.2f\n", novo_cadastro.nota);
                        novo_cadastro.id++;
                    } // final do segundo else
                }while(getche() == '1');// final do laço de repeti��o DO WHILE.
                fclose(ARQUIVO);
            }// final do primeiro else
}

/****
*titulo: cont_ID()
*Data de criacao: 19/11/2021
*ultima modificacao:20/11/2021

*descricao: A funcao usa a quantidade de quebras de linhas no arquivo como metodo
            de contagem do ID do conteudo.

            O laço WHILE varre os caracteres do arquivo um por um e compara quando
            for igual a "\n" (Quebra de linha).

*Valor de retorno: Retorna a quantidade de quebras de linhas no arquivo(vulgo, ID).

****/

int cont_ID(){

    CADASTRO novo_cadastro;
	char c; // variavel que auxilia na leitura dos caracteres do arquivo.
    int ID; //Contador para quantidade de '/n', representando os ID's.

    ARQUIVO = fopen("itens.dat", "r+");

	while(fread (&c, sizeof(char), 1, ARQUIVO)) {
            if(c == '\n') {
                ID++;
            }
    }
	fclose(ARQUIVO);
	return ID+1;
}

/****
*titulo: listar()
*Data de criacao: 20/11/2021
*ultima modificacao:20/11/2021

*descricao: A funcao lista todos os itens contidos no arquivo.

****/

void listar(){

    CADASTRO novo_cadastro;
    char listagem[250]; //variavel responsavel pelo armazenamento dos conteudos do arquivo a serem listados

        ARQUIVO = fopen("itens.dat", "r+");
        //testa a abertura do arquivo
        if (ARQUIVO == NULL){
            printf ("Erro ao abrir o arquivo...\n");
            exit(1); // aborta o a funcao
        }else{
            interface();
            printf ("catalogo\n");

                //A funcao FGETS vai ler as STRINGS do arquivo
                while(fgets(listagem, 250, ARQUIVO) != NULL){
                    printf ("%s", listagem);
                    printf ("-----------------------------------\n");
                }
                //Fim do WHILE
            }

        fclose(ARQUIVO);
        getch();
}

/****
*titulo: excluir().
*Data de criacao: 21/11/2021
*ultima modificacao:23/11/2021

*descricao: Essa funcao recebe do usuario o ID de um item que ele deseja retirar, verificando se o mesmo
            existe e concluindo o processo de exclus�o. Caso n exista, e impressa uma mensagem de erro
            ao usuario.

            O processo funciona da seguinte maneira: abrem-se 2 arquivos, o "itens.dat" (para ler todo o conteudo armazenado)
            e o "Exclui.dat" (arquivo auxiliar para copiar apenas o desejado, excluindo-se o item que o cliente queria). Ao final,
            reabrem-se os mesmos arquivos, s� que com funcoes trocadas (itens.dat para ser copiado e Exclui.dat para ser lido),
            gerando assim, o arquivo principal sem o item informado pelo usuario.

****/

void excluir(){

    CADASTRO novo_cadastro;
    FILE *ARQUIVO2; // variavel que servir� de arquivo auxiliar para copiar apenas o conteudo que o usuario nao deseja excluir.
    int excluir;
    int k=0;
    unsigned int conteudo_atual = 1; // Inicia sempre no ID de numero 1 e serve para comparar com o excluir.
    char texto[1001];
    char arquivo_aux[1001];

    listar();
    printf ("\nDigite o conteudo a ser exclu�do (pelo ID): ");
    scanf ("%d", &excluir);

    ARQUIVO = fopen ("itens.dat", "r");
    ARQUIVO2 = fopen ("Exclui.dat", "w");

    if (ARQUIVO == NULL){
        printf ("Erro ao abrir o arquivo...\n");
        exit(1);
    }else{
        //Armazena todo o conteudo dentro do arquivo na variavel "texto"
        while (fgets (texto, 1001, ARQUIVO) != NULL){
            if (conteudo_atual != excluir){
                fputs (texto, ARQUIVO2); // atalho que copia no arquivo "Exclui.dat"
            }else{
                fprintf (ARQUIVO2, "\n"); // se achar o ID, pula a linha no arquivo
                k=1; // Verifcou-se que houve a exclus�o
            }// Fim do else
            memset(texto,0,sizeof(char)*1001); // Preenche a mem�ria da variavel "texto" a cada itera��o
            conteudo_atual += 1; // Aumenta o ID de um em um ao final de cada itera��o
        }
    //fecha os arquivos
    fclose (ARQUIVO);
    fclose(ARQUIVO2);

    //reabre os arquivos
    ARQUIVO = fopen ("itens.dat", "w");
    ARQUIVO2 = fopen ("Exclui.dat", "r");

        //Copiar� todo o conteudo do arquivo principal, com excess�o do ID escolhido
        while (fgets(arquivo_aux, 1001, ARQUIVO2) != NULL){
            fputs (arquivo_aux, ARQUIVO); // Coloca de volta o texto ao "itens.dat"
        }
    //fecha os arquivos
    fclose (ARQUIVO);
    fclose(ARQUIVO2);

        //verifica se o item foi excl�ido ou nao
        if (k == 1){
            printf ("Item exclu�do com sucesso!\n");
        }else{
            printf ("Erro! Item nao encontrado!\n");
        }
    }// fim do else

getch();
}

/****
*titulo: mudar_nota().
*Data de criacao: 29/11/2021
*ultima modificacao:01/12/2021

*descricao: Essa funcao pega do usuario o ID do item que ele deseja fazer a altera��o da antiga avalia��o
            e a nova nota a ser substitu�da. Copia-se tudo que tem no arquivo "itens.dat" em um arquivo auxiliar j� com
            a nota alterada e salva. Ao fim, retorna-se os dados ao arquivo principal, "itens.dat".

****/

void mudar_nota(){

    FILE *ARQUIVO3;
    char copia_dados[1001];
    char *delimitador; // ponteiro que servir� de par�metro para guardar as strings separadas pelo @
    char arquivo_aux[1001];
    int id;
    int id_atual = 1;
    int contador = 0;
    float nova_nota;

    ARQUIVO = fopen("itens.dat", "r");
    ARQUIVO3 = fopen("altera_nota.dat", "w");

    //verifica
    if(ARQUIVO == NULL) {
        printf( "Erro ao abrir o arquivo...\n");
        exit(0);
    }else{
        //recebe os dados pedidos ao usuario
        interface();
        fflush(stdin);
        printf ("Informe o ID do item a alterar a nota: ");
        scanf ("%d", &id);
        printf ("digite a nova nota: ");
        scanf ("%f", &nova_nota);

        if(nova_nota < 1 || nova_nota > 5){
            printf("ERRO! Informe uma nota entre 1 � 5 !!\n");
        }
        //fgets ir� pegar os dados do arquivo e armazenar em "copia_dados"
            while(fgets(copia_dados, 1001, ARQUIVO) != NULL) {
                    if(id_atual != id){
                        fputs(copia_dados, ARQUIVO3); //copia os dados normais no arquivo "altera_nota.dat"
                    }else{
                        delimitador = strtok (copia_dados,"@");//strtok limita a leitura at� o primeiro @ da linha
                            while( contador <= 3 ){
                                fprintf (ARQUIVO3, "@%s", delimitador); //copia no arquivo auxiliar a string toda, com excess�o da nota
                                delimitador = strtok ( NULL , "@");
                                contador++; // limita ler a string de cada linha(sempre) at� o ano, deixando o espa�o da nota "vazio"
                            }
                        fprintf (ARQUIVO3, "@%.2f", nova_nota);//inclui a nova nota na mesma linha do respectivo ID alterado
                        fprintf (ARQUIVO3, "\n");
                  }
                  id_atual++; //vai aumentando o ID de um em um a cada itera��o para que haja a compara��o com o o que o usuario quer
            }

            fclose(ARQUIVO);
            fclose(ARQUIVO3);

        //reabre-se os arquivos
        ARQUIVO= fopen("itens.dat", "w");
        ARQUIVO3 = fopen("altera_nota.dat", "r");

        while (fgets(arquivo_aux, 1001, ARQUIVO3) != NULL){
            fputs (arquivo_aux, ARQUIVO);
        }

        fclose (ARQUIVO);
        fclose(ARQUIVO3);
    }


    system("pause");
    getch();
}

/****
*titulo: buscar_ID().
*Data de criacao: 19/11/2021
*ultima modificacao: 21/11/2021
*
*descricao: funcao responsavel por buscar os conteudos atraves do ID de cada um.

            O FGETS ir� ler o conteudo contido no arquivo e o MEMSET ir� preencher
            a memoria da variavel responsavel por armazenar o conteudo com o espa�o
            alocado no arquivo.


****/

void buscar_ID(){

    CADASTRO novo_cadastro;
    char conteudo[1001]; //variavel que vai armazenar
    int conteudo_atual = 1;
    int id;
    int achou_ID = 0; //verificador

    ARQUIVO = fopen("itens.dat", "r");

    if (ARQUIVO == NULL){
        printf ("Erro ao abrir o arquivo...\n");
        exit(1);
    }else{

        interface();
        printf ("Informe o ID do conteudo que deseja buscar: ");
        scanf ("%d", &id);
        printf ("\n");

        char c = fgetc(ARQUIVO); //pega caractere a caractere do arquivo

        printf ("catalogo\n");
        printf ("===================================\n");

           while (fgets(conteudo, 1001, ARQUIVO) != NULL){

                //A variavel "conteudo_atual" ir� varrer os numeros inteiros ate o laço WHILE terminar e cada numero contido nessa variavel ser� comparado com ID que o usuario digitar
                if (conteudo_atual == id && id != c){
                    printf ("%s", conteudo);
                    printf ("===================================\n");
                    achou_ID = 1;
                }

                memset(conteudo, 0, sizeof(char)*1001); //Preenche a mem�ria da variavel "conteudo" com o respectivo numero de bytes inseridos
                conteudo_atual ++;
            }
            if(achou_ID != 1)
                printf("ID inexistente!!");
    }
    fclose(ARQUIVO);
    getch();
}

/****
*titulo: buscar_titulo()
*Data de criacao: 27/11/2021
*ultima modificacao: 03/12/2021

*descricao: Com o uso do STRTOK a funcao buscar_titulo divide as STRINGS
            armazenadas no arquivo atraves dos seus delimitadores (@).
            E com isso, compara a o conteudo da �rea delimitada pelo arroba.

****/
void buscar_titulo(){
    char ler_arquivo[1001], texto[1001], *armazenando;
    char *t;
    char *titulo_Item;
    char *pesq_Titulo = (char *) calloc(1, sizeof(char));
    int cont_Arroba = 0;
    int cont=0, i=0;
    int dados = 0;

    ARQUIVO = fopen("itens.dat", "r");

    interface();

    if (ARQUIVO == NULL){
        printf ("Desculpa! A pasta se encontra vazia...\n");
    }else{

        fflush(stdin);
        printf("Informe o titulo do item que deseja pesquisar: ");
        fgets(pesq_Titulo, 100, stdin);  //Armazenando o que for digitado pelo usuario no pesq_Titulo
        fflush(stdin);
        pesq_Titulo = (char *) realloc(pesq_Titulo, strlen(pesq_Titulo) * sizeof(char)); //Altera o tamanho alocado anteriormente para o tamanho do comprimento do vetor de caracter informado pelo usuario

        printf ("\nResultado da busca: \n");
        while(fgets(ler_arquivo, 1001, ARQUIVO)!=NULL){ //laço WHILE responsavel pela repeti��o constante do bloco, enquanto nao chegar no final do arquivo.
                                                        //A variavel ler_arquivo varre o arquivo e armazena nela o seu conteudo
                armazenando = (char *) calloc(cont, sizeof(char));
                t = strtok(ler_arquivo, "@"); // "t" retorna um ponteiro separado pelo delimitador (separado pelos @)

            /*ciclo WHILE(t != NULL) responsavel por delimitar a compara��o das strings at� o segundo @

                EXEMPLO: 1@friends@serie@1990@2,00

                t = friends  ||  O nome do conteudo ser� armazenado em "t" ||
            */
            while( t != NULL){
                cont_Arroba++;
                if(cont_Arroba == 2){ //Realiza o laço condicional quando o ponteiro apontar ao 2� "@".
                    titulo_Item = (char *) calloc(strlen(t), sizeof(char));
                    titulo_Item = t;
                        if(strncmp(titulo_Item, pesq_Titulo, strlen(pesq_Titulo)) == 0){ //Compara��o entre o conteudo e o tirulo digitado pelo usuario
                            dados = 1;
                        }
                }//fim do IF
                if(dados == 1){
                    printf("@%s", t);
                }//fim do IF
                t = strtok(NULL, "@"); //Com a chamada de um ponteiro NULL a funcao strtok indica para continuar no ponteiro anterior.
            }
        cont_Arroba = 0; //zera a variavel "cont_Arroba" pros ciclos seguintes
        dados = 0;    //zera a variavel "dados" pros ciclos seguintes
        cont++;
        }
    }
    fclose(ARQUIVO);
    getch();
}

/****
*titulo: listar_tipo().
*Data de criacao: 24/11/2021
*ultima modificacao: 26/11/2021
*
*descricao: A funcao tem por objetivo, listar todos os itens cadastrados de acordo com o tipo que o usuario desejar, seja ele
            filme, s�rie ou document�rio. Assim, percorre o arquivo inteiro procurando pela respectiva palavra e, caso encontre,
            imprime na tela; tal itera��o, ocorre at� o fim do arquivo. Contudo, caso nao encontre nenhum item com o respectivo ti-
            po, imprime uma mensagem informativa ao usuario.
*
*Par�metros: char *nome[15]: Dentro do case 7(na main), o usuario escolhe a opcao do tipo do item que deseja e � enviado
 (j� copiado, pelo strcpy, em uma variavel) para a poss�vel varredura no arquivo, em busca da mesma.

****/

void listar_tipo(char *nome[15]){

     ARQUIVO = fopen("itens.dat", "r");

    char armazena_dados[1001];
    int verifica = 0;

    interface();

    //Verificando se tem erro ao abrir o arquivo
    if (ARQUIVO == NULL){
        printf ("Erro ao abrir o arquivo...\n");
    }else{

        system("cls");
        interface();
        printf ("\nResultado da Busca: \n");
        printf ("===============================\n");

        //Inicio do DO WHILE
        do{
            //O fgets armazena tudo que tem no arquivo at� o final do mesmo
            fgets(armazena_dados, 1001, ARQUIVO);
                //Nesse caso, o strstr tem como objetivo, localizar a primeira ocorr�ncia de uma dada palavra.
                 if(strstr(armazena_dados, nome) != NULL){
                        printf("%s", armazena_dados);
                        printf ("===============================\n");
                        verifica = 1; // Verificador para informar caso ache um item.
                 }

            }while(!feof(ARQUIVO));//Final do DO WHILE
    }

        fclose(ARQUIVO);

            if(verifica == 0)
                printf("\nDesculpe, nao existe nenhum item cadastrado desse tipo... :(");

    system ("pause");
  getchar();
}

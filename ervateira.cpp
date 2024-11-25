#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <assert.h>
#include <fstream>
#define TAM 1000
using namespace std;

int pnt_auxiliar_entradas = 0;
float preco_erva_nativa, preco_erva_plantada;

typedef struct
{
    string nome;
    string data;
    bool nativa;
    float peso;
    float totalValue;

} entrega;

string formatacao(string msg)
{
    int i = 0;
    while (msg[i] != '\0')
    {
        if (msg[i] >= 97 && msg[i] <= 122)
        {
            msg[i] -= 32;
        }
        i++;
    }
    return msg;
}
bool cin_verifica_bool(string msg)
{
    string aux;
    bool loop_in = true;
    while (loop_in)
    {
        getline(cin, aux);
        aux = formatacao(aux);
        if (aux == "SIM" || aux == "NAO")
        {
            loop_in = false;
        }
        else
        {
            cout << msg << endl;
        }
    }
    cout << endl;
    if (aux == "SIM")
    {
        return true;
    }
    else
    {
        return false;
    }
}
int cin_verifica_int_intervalo(string msg, int min, int max)
{
    bool loop_in = true;
    int escolha;
    string texto;

    while (loop_in)
    {
        getline(cin, texto);

        stringstream ss(texto);

        if (ss >> escolha && ss.eof() && (escolha >= min && escolha <= max))
        {
            loop_in = false;
        }
        else
        {
            cout << msg;
        }
    }
    return escolha;
}
int cin_verifica_int(string msg)
{
    bool loop_in = true;
    int escolha;
    string texto;

    while (loop_in)
    {
        getline(cin, texto);

        stringstream ss(texto); // tranforma a string em um fluxo de string (string stream), parecido com o cin

        if (ss >> escolha && ss.eof()) // ss >> extrai os numeros de texto e ss.eof() verifica se nao existem mais carcteres apos os numeros (se a string acabou)
        {                              // tento atribuir ss (var do tipo stringstream), a escolha
            loop_in = false;
            // caso as condiçoes sejam aceitas, a entrada eh retornada
        }
        else
        {
            cout << msg;
        }
    }
    return escolha;
}

float cin_verifica_float(string msg)
{
    bool loop_in = true;
    float escolha;
    string texto;

    while (loop_in)
    {
        getline(cin, texto);

        stringstream ss(texto); // tranforma a string em um fluxo de string (string stream), parecido com o  fluxo da iostream cin

        if (ss >> escolha && ss.eof() && (escolha > 0)) // ss >> extrai os numeros de texto e ss.eof() verifica se nao existem mais carcteres apos os numeros (se a string acabou)
        {                                               // tento atribuir ss (var do tipo stringstream), a  variavel escolha
            loop_in = false;
            // caso as condiçoes sejam aceitas, a entrada eh
        }
        else
        {
            cout << msg;
        }
    }
    return escolha;
}

string cin_data()
{
    int dia, mes, ano;
    cout << "Digite o dia: ";
    dia = cin_verifica_int_intervalo("Dia invalido! Digite novamente: ", 1, 31);

    cout << "Digite o mes: ";
    mes = cin_verifica_int_intervalo("Mes invalido! Digite novamente: ", 1, 12);

    cout << "Digite o ano: ";
    ano = cin_verifica_int_intervalo("Ano invalido! Digite novamente: ", 1, 9999);

    return to_string(ano) + "/" + to_string(mes) + "/" + to_string(dia); // talvez colocar + (mes < 10? "0":"") + e pro dia tambem
}

int particao_dia(entrega *vetor, int inicio, int fim)
{
    string pivo = (*(vetor + fim)).data;
    int j = inicio - 1;
    for (int i = inicio; i < fim; i++)
    {
        if ((*(vetor + i)).data < pivo)
        {
            j++;
            swap(vetor[j], vetor[i]);
        }
    }
    swap(vetor[j + 1], vetor[fim]);

    return j + 1;
}

void quick_sort_dia(entrega *vetor, int inicio, int fim)
{
    int localPart;
    if (inicio < fim)
    {
        localPart = particao_dia(vetor, inicio, fim);

        quick_sort_dia(vetor, localPart + 1, fim);
        quick_sort_dia(vetor, inicio, localPart - 1);
    }
}
int binarySearch_ultima_ocorrencia_data(entrega *vetor, int inicio, int fim, string alvo)
{
    int esq = inicio;
    int dir = fim;
    int meio;
    int resultado = -1;
    while (esq <= dir)
    {
        meio = (esq + dir) / 2;
        if ((*(vetor + meio)).data < alvo)
        {
            esq = meio + 1;
        }
        else if ((*(vetor + meio)).data > alvo)
        {
            dir = meio - 1;
        }
        else
        {
            resultado = meio;
            esq = meio + 1;
        }
    }
    return resultado;
}

int binarySearch_primeira_ocorrencia_data(entrega *vetor, int inicio, int fim, string alvo)
{
    int esq = inicio;
    int dir = fim;
    int meio;
    int resultado = -1;
    while (esq <= dir)
    {
        meio = (esq + dir) / 2;
        if ((*(vetor + meio)).data < alvo)
        {
            esq = meio + 1;
        }
        else if ((*(vetor + meio)).data > alvo)
        {
            dir = meio - 1;
        }
        else
        {
            resultado = meio;
            dir = meio - 1;
        }
    }
    return resultado;
}
int particao_nome(entrega *vetor, int inicio, int fim)
{
    string pivo = (*(vetor + fim)).nome;
    int j = inicio - 1;
    for (int i = inicio; i < fim; i++)
    {
        if ((*(vetor + i)).nome < pivo)
        {
            j++;
            swap(vetor[j], vetor[i]);
        }
    }
    swap(vetor[j + 1], vetor[fim]);

    return j + 1;
}

void quick_sort_nome(entrega *vetor, int inicio, int fim)
{
    int localPart;
    if (inicio < fim)
    {
        localPart = particao_nome(vetor, inicio, fim);

        quick_sort_nome(vetor, localPart + 1, fim);
        quick_sort_nome(vetor, inicio, localPart - 1);
    }
}
int binarySearch_ultima_ocorrencia_nome(entrega *vetor, int inicio, int fim, string alvo)
{
    int esq = inicio;
    int dir = fim;
    int meio;
    int resultado = -1;
    while (esq <= dir)
    {
        meio = (esq + dir) / 2;
        if ((*(vetor + meio)).nome < alvo)
        {
            esq = meio + 1;
        }
        else if ((*(vetor + meio)).nome > alvo)
        {
            dir = meio - 1;
        }
        else
        {
            resultado = meio;
            esq = meio + 1;
        }
    }
    return resultado;
}

int binarySearch_primeira_ocorrencia_nome(entrega *vetor, int inicio, int fim, string alvo)
{
    int esq = inicio;
    int dir = fim;
    int meio;
    int resultado = -1;
    while (esq <= dir)
    {
        meio = (esq + dir) / 2;
        if ((*(vetor + meio)).nome < alvo)
        {
            esq = meio + 1;
        }
        else if ((*(vetor + meio)).nome > alvo)
        {
            dir = meio - 1;
        }
        else
        {
            resultado = meio;
            dir = meio - 1;
        }
    }
    return resultado;
}

void cin_carga(entrega *vetor)
{
    cout << "Digite o nome do entregador: ";
    getline(cin, (*(vetor + pnt_auxiliar_entradas)).nome);
    (*(vetor + pnt_auxiliar_entradas)).nome = formatacao((*(vetor + pnt_auxiliar_entradas)).nome);
    cout << endl;

    cout << "Digite o peso da entrega, em kg: ";
    (*(vetor + pnt_auxiliar_entradas)).peso = cin_verifica_float("Peso invalido! Digite novamente: ");
    cout << endl;

    cout << "A erva eh nativa? Digite (sim) ou (nao): ";
    (*(vetor + pnt_auxiliar_entradas)).nativa = cin_verifica_bool("Entrada invalida, tente novamente!");
    if (vetor[pnt_auxiliar_entradas].nativa)
    {
        (*(vetor + pnt_auxiliar_entradas)).totalValue = (*(vetor + pnt_auxiliar_entradas)).peso * preco_erva_nativa;
    }
    else
    {
        (*(vetor + pnt_auxiliar_entradas)).totalValue = (*(vetor + pnt_auxiliar_entradas)).peso * preco_erva_plantada;
    }

    cout << "Digite a data da entrega." << endl;
    (*(vetor + pnt_auxiliar_entradas)).data = cin_data();

    pnt_auxiliar_entradas++;
}

void removedor_entrega(entrega *vetor, int remover)
{
    swap(vetor[remover], vetor[pnt_auxiliar_entradas]);
    pnt_auxiliar_entradas--;
    swap(vetor[remover], vetor[pnt_auxiliar_entradas]);
}

entrega *cria_entregas()
{
    entrega *cargas = new (nothrow) entrega[TAM];
    if (cargas == nullptr)
    {
        cout << "Erro na alocacao" << endl;
        return nullptr;
    }
    return cargas;
}

void cout_cargas(entrega *cargas, int i, int tamanho)
{
    cout << "!(dias no formato YYYY/MM/DD)!" << endl;
    cout << endl;
    if (pnt_auxiliar_entradas == 0)
    {
        cout << "Nenhuma carga listada ainda!" << endl;
    }
    else
    {
        for (int aux = i; aux < tamanho; aux++)
        {
            cout << "[" << aux << "]------------------------" << endl;
            cout << "Data da entrega: " << (*(cargas + aux)).data << endl;
            cout << "Nome do entregador: " << (*(cargas + aux)).nome << endl;
            cout << "Nativa?: " << ((*(cargas + aux)).nativa ? "Sim" : "Nao") << endl;
            cout << "Peso da carga: " << (*(cargas + aux)).peso << endl;
            cout << "Valor total da carga: " << (*(cargas + aux)).totalValue << " R$" << endl;
            cout << "---------------------------" << endl;
        }
    }
}
void cout_cabecalho()
{
    cout << "Bem vindo ao sistema de armazenameto de dados de entregas \n"
         << "de erva-mate! O preco da erva nativa esta: " << preco_erva_nativa << " R$/kg,\n"
         << "e da plantada esta " << preco_erva_plantada << " R$/kg" << endl;
    cout << endl;
    cout << "Selecione uma opcao para continuar: \n"
         << "Digite (1) para registrar nova entrega. \n"
         << "Digite (2) para procurar por entrega(s) por data. \n"
         << "Digite (3) para procurar por entrega(s) por nome. \n"
         << "Digite (4) para listar todas as entregas do sistema.\n"
         << "Digite (5) para remover uma entrega do sistema.\n"
         << "Digite (6) para alterar o preco da erva-mate.\n"
         << "Digite (7) para sair." << endl;
    cout << endl;
    cout << "Digite aqui a opcao escolhida: ";
}

void carrega_csv(entrega *vetor, int capacidade_max)
{
    int i = 0;
    ifstream arquivo("entregas.csv");
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }
    string linha;
    getline(arquivo, linha);
    string campo;
    while (getline(arquivo, linha) && i < capacidade_max) // do arquivo eu retiro uma linha, cada vez que é chamado o getline, le nova linha
    {                                                     // pois a cada chamada o ponteiro do arquivo vai para a proxima linha da planilha
        istringstream stream(linha); // estou transformando a linha da planilha em um fluxo de entrada de string
        getline(stream, vetor[i].data, ',');
        getline(stream, vetor[i].nome, ','); //De modo semelhante, o getline() vai ler ate a virgula, avançando o ponteiro de leitura para essa virgula

        getline(stream, campo, ',');
        vetor[i].nativa = (campo == "SIM" ? true : false);
        getline(stream, campo, ',');
        vetor[i].peso = stof(campo);
        getline(stream, campo);
        vetor[i].totalValue = stof(campo); // codigo vai ler o arquivo.csv e atribuir linhas a indices do vetor de entregas

        i++;
    }
    pnt_auxiliar_entradas = i; // no fim o pnt_auxiliar deve receber quantas entradas ocorreram + 1, para que o codigo funcione
    arquivo.close();
}

string formata_float(float num, int precisao)
{
    ostringstream aux;
    aux << fixed << setprecision(precisao) << num;
    return aux.str();
}

void salva_csv(entrega *vetor, int capacidade_max)
{
    ofstream arquivo("entregas.csv");
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    arquivo << "Data,Nome,Nativa,Peso,TotalValue\n";
    for (int i = 0; i < capacidade_max; i++)
    {
        arquivo << vetor[i].data << ","
                << vetor[i].nome << ","
                << (vetor[i].nativa ? "SIM" : "NAO") << ","
                << formata_float(vetor[i].peso, 5) << ","
                << formata_float(vetor[i].totalValue, 5) << "\n"; // linha do arquivo.csv vai receber/ler todas essas informações
    }
    arquivo.close();
    cout << "Dados salvos! " << endl;
}

int main()
{
    int opcao, opcao2, first, last, aux;
    preco_erva_nativa = 1.46;
    preco_erva_plantada = 1.26;
    assert(formatacao("teste teste123") == "TESTE TESTE123");
    assert(pnt_auxiliar_entradas == 0); // verifica se o programa esta começando com o valor de pnt auxiliar de entradas igual a 0, caso nao esteja, termina a execuçao
    entrega *cargas_erva_mate = cria_entregas();
    assert(cargas_erva_mate != nullptr);
    bool keep_going = true;
    string alvo;

    carrega_csv(cargas_erva_mate, TAM);

    if (cargas_erva_mate != nullptr)
    {
        while (keep_going)
        {
            system("cls");
            cout_cabecalho();
            opcao = cin_verifica_int("Entrada invalida! Digite novamente: ");
            switch (opcao)
            {
            case 1: // nova entrega;
                system("cls");
                cin_carga(cargas_erva_mate);
                break;
            case 2: // Procura por entrega por dia
                if (pnt_auxiliar_entradas > 0)
                {
                    cout << "Digite a data que voce quer procurar por entregas." << endl;
                    quick_sort_dia(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1);
                    alvo = cin_data();
                    cout << endl;
                    first = binarySearch_primeira_ocorrencia_data(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1, alvo);
                    last = binarySearch_ultima_ocorrencia_data(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1, alvo);
                    if (first == -1 || last == -1)
                    {
                        cout << "Nenhuma entrega encontrada para a data especificada." << endl;
                    }
                    else
                    {
                        cout << "Entrega(s) no dia " << alvo << ":" << endl;
                        cout_cargas(cargas_erva_mate, first, last + 1);
                    }
                }
                else
                {
                    cout << "Nao ha entragas para procurar!" << endl;
                }
                system("pause");
                break;
            case 3: // procura por entrega por nome
                if (pnt_auxiliar_entradas > 0)
                {
                    cout << "Digite o nome que voce quer procurar por entregas: ";
                    quick_sort_nome(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1);
                    getline(cin, alvo);
                    alvo = formatacao(alvo);
                    cout << alvo << endl;
                    cout << endl;
                    first = binarySearch_primeira_ocorrencia_nome(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1, alvo);
                    last = binarySearch_ultima_ocorrencia_nome(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1, alvo);
                    cout << first << " " << last << endl;
                    if (first == -1 || last == -1)
                    {
                        cout << "Nenhuma entrega encontrada para o nome especificado." << endl;
                    }
                    else
                    {
                        cout << "Entrega(s) de " << alvo << ": " << endl;
                        cout_cargas(cargas_erva_mate, first, last + 1);
                    }
                }
                else
                {
                    cout << "Nao ha entragas para procurar!" << endl;
                }
                system("pause");

                break;
            case 4: // listagem de todas as entregas;
                cout << endl;
                system("cls");
                cout_cargas(cargas_erva_mate, 0, pnt_auxiliar_entradas);
                system("pause");
                break;
            case 5: // Remover entrega;
                if (pnt_auxiliar_entradas > 0)
                {
                    cout << "Qual entrega deseja remover? (Use os indices das linhas pontilhadas para selecionar) " << endl;
                    cout_cargas(cargas_erva_mate, 0, pnt_auxiliar_entradas);
                    cout << endl;
                    cout << "Digite aqui o indice: ";
                    aux = cin_verifica_int_intervalo("Indice invalido! Tente novamente: ", 0, pnt_auxiliar_entradas - 1);
                    removedor_entrega(cargas_erva_mate, aux);
                    cout << "Carga removida com sucesso!" << endl;
                }
                else
                {
                    cout << "Nao ha cargas para remover!" << endl;
                }
                system("pause");

                break;
            case 6: // Alterar preco;
                system("cls");
                cout << "Qual preco deseja alterar? \n"
                     << "Digite (1) para nativa e (2) para plantada" << endl;
                opcao2 = cin_verifica_int_intervalo("Opcao invalida! Digite novamente: ", 1, 2);
                if (opcao2 == 1)
                {
                    cout << "Digite o valor atualizado da erva nativa por kg: ";
                    preco_erva_nativa = cin_verifica_float("Valor invalido: ");
                }
                else
                {
                    cout << "Digite o valor atualizado da erva plantada por kg: ";
                    preco_erva_plantada = cin_verifica_float("Valor invalido: ");
                }
                cout << "Valor atualizado!" << endl;
                system("pause");
                break;
            case 7: // Sair;
                keep_going = false;
                break;
            default:
                cout << "Opcao invalida!" << endl;
                system("pause");
                break;
            }
        }
    }
    salva_csv(cargas_erva_mate, pnt_auxiliar_entradas);
    delete[] cargas_erva_mate;
    cargas_erva_mate = nullptr;
    return 0;
}
#include <iostream>
#include <limits>
#include <iomanip>
#define TAM 100
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
        cin >> aux;
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
    while (loop_in)
    {
        cin >> escolha;

        if (cin.fail() || (escolha < min || escolha > max))
        {
            cout << msg;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa todo o buffer, ate encontrar a quebra de linha "enter"
        }
        else
        {
            loop_in = false;
        }
    }
    return escolha;
}
int cin_verifica_int(string msg)
{
    bool loop_in = true;
    int escolha;
    while (loop_in)
    {
        cin >> escolha;

        if (cin.fail())
        {
            cout << msg;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa todo o buffer, ate encontrar a quebra de linha "enter"
        }
        else
        {
            loop_in = false;
        }
    }
    return escolha;
}

float cin_verifica_float(string msg)
{
    bool loop_in = true;
    float num;
    while (loop_in)
    {
        cin >> num;

        if (cin.fail() || num < 0)
        {
            cout << msg;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa todo o buffer, ate encontrar a quebra de linha "enter"
        }
        else
        {
            loop_in = false;
        }
    }
    return num;
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
    cin.ignore();
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
int main()
{
    int opcao, opcao2, first, last, aux;
    preco_erva_nativa = 11.2;
    preco_erva_plantada = 9.2;

    entrega *cargas_erva_mate = cria_entregas();
    bool keep_going = true;
    string alvo;
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
                system("pause");
                break;
            case 3: // procura por entrega por nome
                cout << "Digite o nome que voce quer procurar por entregas: ";
                quick_sort_nome(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1);
                cin.ignore();
                getline(cin, alvo);
                alvo = formatacao(alvo);
                cout << endl;
                first = binarySearch_primeira_ocorrencia_nome(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1, alvo);
                last = binarySearch_ultima_ocorrencia_nome(cargas_erva_mate, 0, pnt_auxiliar_entradas - 1, alvo);
                if (first == -1 || last == -1)
                {
                    cout << "Nenhuma entrega encontrada para o nome especificado." << endl;
                }
                else
                {
                    cout << "Entrega(s) de " << alvo << ": " << endl;
                    cout_cargas(cargas_erva_mate, first, last + 1);
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
                    preco_erva_nativa = cin_verifica_float("Valor invalido");
                }
                else
                {
                    cout << "Digite o valor atualizado da erva plantada por kg: ";
                    preco_erva_plantada = cin_verifica_float("Valor invalido");
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
    delete[] cargas_erva_mate;
    cargas_erva_mate = nullptr;
    return 0;
}
/* 
Nome: Ana Lara Alves Garcia
SO: Windows
Compilador: VSCode
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>

using namespace std;

// tokens
const int TOK_PCHAVE = 1;
const int TOK_ID = 2;
const int TOK_NUM = 3;
const int TOK_PONT = 4;
const int TOK_OP = 5;

// palavra reservada
const int PC_PROGRAM = 0;
const int PC_VAR = 1;
const int PC_PROCEDURE = 2;
const int PC_BEGIN = 3;
const int PC_END = 4;
const int PC_IF = 5;
const int PC_THEN = 6;
const int PC_ELSE = 7;
const int PC_WHILE = 8;
const int PC_DO = 9;
const int PC_INTEGER = 10;
const int PC_DIV = 11;
const int PC_READ = 12;
const int PC_WRITE = 13;
const int PC_FUNCTION = 14;
const int PC_REAL = 15;
const int PC_BOOLEAN = 16;
const int PC_CHAR = 17;
const int PC_STRING = 18;
const int PC_ARRAY = 19;
const int PC_REPEAT = 20;
const int PC_UNTIL = 21;
const int PC_FOR = 22;
const int PC_TO = 23;
const int PC_DOWNTO = 24;

// pontuação
const int PARESQ = 1; // (
const int PARDIR = 2; // )
const int VIRG = 3; // ,
const int PNTVIRG = 4; // ;
const int DPONT = 5; // :
const int PONT = 6; // .
const int COLCHETEE = 7; // [
const int COLCHETED = 8; // ]

// operadores
const int SOMA = 1; // +
const int SUB = 2; // -
const int MULT = 3; // *
const int IGUAL = 4; // =
const int MENORIG = 5; // <=
const int ATRIB = 6; // :=
const int DIV_REAL = 7; // /
const int MENOR = 8; // <
const int MAIOR = 9; // >
const int MAIORIG = 10; // >=
const int DIFERENTE = 11; // <>
const int OP_MOD = 12; // MOD
const int OP_AND = 13; // AND
const int OP_OR = 14; // OR
const int OP_NOT = 15; // NOT

struct Token {
    int tipo;
    int valor;
};

struct Simbolo {
    string nome;
    int valor;
};

void PROXIMO(ifstream& arq, char& c, int& linha) {
    if (arq.get(c)) {
        if (c == '\n') {
            linha++;
        } 
        c = toupper(c);
    } else { // fim de arquivo
        c = EOF;
    }
}

Token CODIGO(string atomo, vector<Simbolo>& tabela, int& contador_id) {
    Token t;

    static const unordered_map<string, Token> dicionario = {
        // palavra reservada
        {"PROGRAM", {TOK_PCHAVE, PC_PROGRAM}},
        {"VAR", {TOK_PCHAVE, PC_VAR}},
        {"PROCEDURE", {TOK_PCHAVE, PC_PROCEDURE}},
        {"BEGIN", {TOK_PCHAVE, PC_BEGIN}},
        {"END", {TOK_PCHAVE, PC_END}},
        {"IF", {TOK_PCHAVE, PC_IF}},
        {"THEN", {TOK_PCHAVE, PC_THEN}},
        {"ELSE", {TOK_PCHAVE, PC_ELSE}},
        {"WHILE", {TOK_PCHAVE, PC_WHILE}},
        {"DO", {TOK_PCHAVE, PC_DO}},
        {"INTEGER", {TOK_PCHAVE, PC_INTEGER}},
        {"DIV", {TOK_PCHAVE, PC_DIV}},
        {"READ", {TOK_PCHAVE, PC_READ}},
        {"WRITE", {TOK_PCHAVE, PC_WRITE}},
        {"FUNCTION", {TOK_PCHAVE, PC_FUNCTION}},
        {"REAL", {TOK_PCHAVE, PC_REAL}},
        {"BOOLEAN", {TOK_PCHAVE, PC_BOOLEAN}},
        {"CHAR", {TOK_PCHAVE, PC_CHAR}},
        {"STRING", {TOK_PCHAVE, PC_STRING}},
        {"ARRAY", {TOK_PCHAVE, PC_ARRAY}},
        {"REPEAT", {TOK_PCHAVE, PC_REPEAT}},
        {"UNTIL", {TOK_PCHAVE, PC_UNTIL}},
        {"FOR", {TOK_PCHAVE, PC_FOR}},
        {"TO", {TOK_PCHAVE, PC_TO}},
        {"DOWNTO", {TOK_PCHAVE, PC_DOWNTO}},

        // operadores
        {"+", {TOK_OP, SOMA}},
        {"-", {TOK_OP, SUB}},
        {"*", {TOK_OP, MULT}},
        {"=", {TOK_OP, IGUAL}},
        {"<=", {TOK_OP, MENORIG}},
        {":=", {TOK_OP, ATRIB}},
        {"/", {TOK_OP, DIV_REAL}},
        {"<", {TOK_OP, MENOR}},
        {">", {TOK_OP, MAIOR}},
        {">=", {TOK_OP, MAIORIG}},
        {"<>", {TOK_OP, DIFERENTE}},
        {"MOD", {TOK_OP, OP_MOD}},
        {"AND", {TOK_OP, OP_AND}},
        {"OR", {TOK_OP, OP_OR}},
        {"NOT", {TOK_OP, OP_NOT}},

        // pontuação
        {"(", {TOK_PONT, PARESQ}},
        {")", {TOK_PONT, PARDIR}},
        {",", {TOK_PONT, VIRG}},
        {";", {TOK_PONT, PNTVIRG}},
        {":", {TOK_PONT, DPONT}},
        {".", {TOK_PONT, PONT}},
        {"[", {TOK_PONT, COLCHETEE}},
        {"]", {TOK_PONT, COLCHETED}}
    };

    // busca no dicionario
    auto it = dicionario.find(atomo);
    if (it != dicionario.end()) {
        return it->second;
    }

    // numeros inteiros
    if (isdigit(atomo[0])) {
        t.tipo = TOK_NUM;
        t.valor = stoi(atomo);
        return t;
    }

    // identificadores (id)
    int tabela_len = tabela.size();
    for (int i = 0; i < tabela_len; i++) { // variavel já existe na tabela
        if (tabela[i].nome == atomo) {
            t.tipo = TOK_ID;
            t.valor = tabela[i].valor;
            return t;
        }
    }

    Simbolo novo_simb; // se não existe ainda, variável nova
    novo_simb.nome = atomo;
    novo_simb.valor = contador_id;

    tabela.push_back(novo_simb); // salva na tabela

    t.tipo = TOK_ID;
    t.valor = contador_id;
    contador_id--;

    return t;
}

void ERRO(int linha, string mensagem, vector<string>& lista_erros) {
    // faz uma lista de erros pra mostrar no final
    string erro = "Erro na linha " + to_string(linha) + ": " + mensagem;
    lista_erros.push_back(erro);
}

string obter_nome_tipo(int tipo) {
    switch (tipo) {
        case TOK_PCHAVE: 
            return "p_chave"; // palavra chave
        case TOK_ID:     
            return "id"; // ID
        case TOK_NUM:    
            return "num"; // número
        case TOK_PONT:   
            return "pont"; // pontuação
        case TOK_OP:     
            return "op"; // operador
        default:         
            return "desconhecido";
    }
}

void analisador_lexico(ifstream& arq, char& c, int& linha, vector<Simbolo>& tabela, int& contador_id, bool& nova_linha, vector<string>& lista_erros) {
    string atomo = "";
    
    // ignora espaço em branco, tab, quebra de linha
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        if (c == '\n') {
            cout << "\n";
            nova_linha = true;
        } else if (c != '\r') {
            if (nova_linha) {
                if (linha < 10) { // apenas para colocar um espaço antes do número da linha se for de 1 a 9
                    cout << " ";
                }
                cout << linha << "\t";
                nova_linha = false;
            }
            cout << c;
        }
        PROXIMO(arq, c, linha);
    }

    if (c == EOF) return;

    // começou com letra
    if (isalpha(c)) {
        while (isalpha(c) || isdigit(c)) {
            atomo += c; // juntando letras e números
            PROXIMO(arq, c, linha);
        }
    // começou com número
    } else if (isdigit(c)) {
        while (isdigit(c)) {
            atomo += c;
            PROXIMO(arq, c, linha);
        }

        // se tiver letra depois de número
        if (isalpha(c)) {
            // termina de juntar a palavra antes para mostrar no erro
            while (isalpha(c) || isdigit(c)) {
                atomo += c;
                PROXIMO(arq, c, linha);
            }
            ERRO(linha, "Identificador ou número mal formado '" + atomo + "'", lista_erros);
            atomo = "";
        }
    // símbolos compostos
    // atribuição e dois pontos
    } else if (c == ':') {
        atomo += c;
        PROXIMO(arq, c, linha);
        if (c == '=') {
            atomo += c;
            PROXIMO(arq, c, linha);
        }
    // menor, menor igual e diferente
    } else if (c == '<') {
        atomo += c;
        PROXIMO(arq, c, linha);
        if (c == '=' || c == '>') {
            atomo += c;
            PROXIMO(arq, c, linha);
        }
    // símbolos simples
    } else if (c == ';' || c == ',' || c == '.' || c == '+' || c == '-' || c == '*' || c == '=' || c == '(' || c == ')') {
        atomo += c;
        PROXIMO(arq, c, linha);
    // caractere inválido
    } else {
        ERRO(linha, "Símbolo especial desconhecido '" + string(1, c) + "'", lista_erros);
        PROXIMO(arq, c, linha);
        return;
    }

    if (atomo != "") {
        Token token = CODIGO(atomo, tabela, contador_id); // manda pro dicionário
        string nome_tipo = obter_nome_tipo(token.tipo);

        if (nova_linha) { 
            if (linha < 10) {
                cout << " ";
            }
            cout << linha << "\t";
            nova_linha = false;
        }
        // cout << "<" << atomo << ", " << nome_tipo << ", " << token.valor << ">";
        cout << "<" << nome_tipo << ", " << token.valor << ">";
    }
}

int main() {
    string nomeArq = "Trab1_Compiladores.txt";

    ifstream arq(nomeArq);

    if (!arq.is_open()) {
        cerr << "Erro ao abrir o arquivo\n";
        return 1;
    }

    char c = ' ';
    int linha = 1;
    vector<Simbolo> tabela_simb;
    int contador_id = -1;
    bool nova_linha = true; // variavel para saber se mudou de linha para printar o número da linha
    vector<string> lista_erros;
    PROXIMO(arq, c, linha);
    
    while (c != EOF) {
        analisador_lexico(arq, c, linha, tabela_simb, contador_id, nova_linha, lista_erros);
    }

    arq.close();

    cout << "\n\n";

    if (lista_erros.empty()) {
        cout << "\tNenhum erro para ser exibido.\n";
    } else {
        cout << "Erros: " << lista_erros.size() << " encontrados\n";
        int lista_len = lista_erros.size();
        for (int i = 0; i < lista_len; i++) {
            cout << lista_erros[i] << "\n";
        }
    }

    return 0;
}
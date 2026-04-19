/* 
Nome: Ana Lara Alves Garcia
SO: Windows
Compilador: VSCode
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

// pontuação
const int PARESQ = 1; // (
const int PARDIR = 2; // )
const int VIRG = 3; // ,
const int PNTVIRG = 4; // ;
const int DPONT = 5; // :
const int PONT = 6; // .

// operadores
const int SOMA = 1; // +
const int SUB = 2; // -
const int MULT = 3; // *
const int IGUAL = 4; // =
const int MENORIG = 5; // <=
const int ATRIB = 6; // :=

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

    // palavra reservada
    if (atomo == "PROGRAM") { t.tipo = TOK_PCHAVE; t.valor = PC_PROGRAM; return t; }
    if (atomo == "VAR") { t.tipo = TOK_PCHAVE; t.valor = PC_VAR; return t; }
    if (atomo == "PROCEDURE") { t.tipo = TOK_PCHAVE; t.valor = PC_PROCEDURE; return t; }
    if (atomo == "BEGIN") { t.tipo = TOK_PCHAVE; t.valor = PC_BEGIN; return t; }
    if (atomo == "END") { t.tipo = TOK_PCHAVE; t.valor = PC_END; return t; }
    if (atomo == "IF") { t.tipo = TOK_PCHAVE; t.valor = PC_IF; return t; }
    if (atomo == "THEN") { t.tipo = TOK_PCHAVE; t.valor = PC_THEN; return t; }
    if (atomo == "ELSE") { t.tipo = TOK_PCHAVE; t.valor = PC_ELSE; return t; }
    if (atomo == "WHILE") { t.tipo = TOK_PCHAVE; t.valor = PC_WHILE; return t; }
    if (atomo == "DO") { t.tipo = TOK_PCHAVE; t.valor = PC_DO; return t; }
    if (atomo == "INTEGER") { t.tipo = TOK_PCHAVE; t.valor = PC_INTEGER; return t; }
    if (atomo == "DIV") { t.tipo = TOK_PCHAVE; t.valor = PC_DIV; return t; }
    if (atomo == "READ") { t.tipo = TOK_PCHAVE; t.valor = PC_READ; return t; }
    if (atomo == "WRITE") { t.tipo = TOK_PCHAVE; t.valor = PC_WRITE; return t; }

    // operadores
    if (atomo == "+") { t.tipo = TOK_OP; t.valor = SOMA; return t; }
    if (atomo == "-") { t.tipo = TOK_OP; t.valor = SUB; return t; }
    if (atomo == "*") { t.tipo = TOK_OP; t.valor = MULT; return t; }
    if (atomo == "=") { t.tipo = TOK_OP; t.valor = IGUAL; return t; }
    if (atomo == "<=") { t.tipo = TOK_OP; t.valor = MENORIG; return t; }
    if (atomo == ":=") { t.tipo = TOK_OP; t.valor = ATRIB; return t; }

    // pontuação
    if (atomo == "(") { t.tipo = TOK_PONT; t.valor = PARESQ; return t; }
    if (atomo == ")") { t.tipo = TOK_PONT; t.valor = PARDIR; return t; }
    if (atomo == ",") { t.tipo = TOK_PONT; t.valor = VIRG; return t; }
    if (atomo == ";") { t.tipo = TOK_PONT; t.valor = PNTVIRG; return t; }
    if (atomo == ":") { t.tipo = TOK_PONT; t.valor = DPONT; return t; }
    if (atomo == ".") { t.tipo = TOK_PONT; t.valor = PONT; return t; }

    // numeros inteiros
    if (isdigit(atomo[0])) {
        t.tipo = TOK_NUM;
        t.valor = stoi(atomo);
        return t;
    }

    // identificadores (id)
    for (int i = 0; i < tabela.size(); i++) { // variavel já existe na tabela
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

void ERRO(int linha, string mensagem) {
    cout << "Erro na linha " << linha << ": " << mensagem << "\n";
}

void analisador_lexico(ifstream& arq, char c, int& linha) {
    string atomo = "";
    
    // while ()

    if (c == EOF) return;
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
    PROXIMO(arq, c, linha);
    
    while (c != EOF) {
        analisador_lexico(arq, c, linha);
    }

    arq.close();

    return 0;
}
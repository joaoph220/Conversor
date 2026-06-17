//Conversor bases c++

//  As bases numericas que estao como "string"
//  estao assim para q sejam lidas caracter por 
//  caracter, e nao como um valor inteiro, tipo
//  pra nao ler 1100(em binario) como mil e cem.
//  --------------------------------------------
//  Converter para Decimal e depois para outras
//  bases, fica "mais pesado" mas e menos role.

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype> // Para toupper
using namespace std;

//serve pra multiplicar a string
string multiplicarString(string numero, int multiplicador){
    string resultado = "";
    int sobe = 0;
    for(int i = numero.size() - 1; i >= 0; i--){ //vai pegar o tamanho numero que o user botar e tirar 1 pra ir pegando de char em char
        int digito = numero[i] - '0'; //nn e vetor, e mais um indice pegando os digitos de tras pra frente e transformando em numero
        int produto = digito * multiplicador + sobe;
        int novoDigito = produto % 10;
        sobe = produto / 10;
        resultado = char(novoDigito + '0') + resultado;
    } 
    while(sobe > 0){ //assegura que o sobe seja colocado no finalzinho da esquerda no numero
        resultado = char((sobe % 10) + '0') + resultado;
        sobe /= 10; //repete o loop ate sobe ser menor que 10, pq ai daria 0 o calculo
    }
    return resultado;
}

//serve pra somar a string
string somarString(string numero, int valor){
    int i = numero.size() - 1; //usa pra pegar os numeros da direita pra esquerda
    while(valor > 0 && i >= 0){ 
        int soma = (numero[i] - '0') + valor; //transforma os caracteres em numeros
        numero[i] = (soma % 10) + '0';
        valor = soma / 10; //pra subir um
        i--;
    }
    while(valor > 0){ //msm raciocinio do sobe do multiplicarString
        numero = char((valor % 10) + '0') + numero;
        valor /= 10;
    }
    return numero;
}

//serve pra dividir por qualquer base ate 16
string dividirString(string numero, int base, int &resto){
    string quociente = "";
    int atual = 0;
    for(char c : numero){
        atual = atual * 10 + (c - '0');
        int digito = atual / base;
        resto = atual % base;
        resto = atual % base;
        if(!(quociente.empty() && digito == 0))
            quociente += char(digito + '0');
        atual = resto;
    }
    if(quociente == "")
        quociente = "0";
    return quociente;
}

// Ternario-->Decimal (Trabalhando com String gigante)
string ternarioParaDecimal(string ternario) {
    string decimal = "0";
    for (char c : ternario) {
        int digito = c - '0';
        if (digito < 0 || digito > 2) return "ERRO"; 
        decimal = multiplicarString(decimal, 3);
        decimal = somarString(decimal, digito);
    }
    return decimal;
}

// Decimal-->Ternario (Trabalhando com String gigante)
string decimalParaTernario(string decimal) {
    if (decimal == "0" || decimal == "") return "0";
    string ternario = "";
    while (decimal != "0") {
        int resto;
        decimal = dividirString(decimal, 3, resto);
        ternario = to_string(resto) + ternario;
    }
    return ternario;
}

// Binario-->Decimal (Trabalhando com String gigante)
string binarioParaDecimal(string binario) {
    string decimal = "0";
    for (char c : binario) {
        if (c != '0' && c != '1') return "ERRO";
        decimal = multiplicarString(decimal, 2);
        decimal = somarString(decimal, c - '0');
    }
    return decimal;
}

// Decimal-->Binario (Trabalhando com String gigante)
string decimalParaBinario(string decimal) {
    if (decimal == "0" || decimal == "") return "0";
    string binario = "";
    while (decimal != "0") {
        int resto;
        decimal = dividirString(decimal, 2, resto);
        binario = to_string(resto) + binario;
    }
    return binario;
}

//octal-->decimal (Trabalhando com String gigante)
string octalParaDecimal(string octal) {
    string decimal = "0";
    for(char c : octal){
        int digito = c - '0';
        if(digito < 0 || digito > 7) return "ERRO";
        decimal = multiplicarString(decimal, 8);
        decimal = somarString(decimal, digito);
    }
    return decimal;
}

// Decimal -->Octal (Trabalhando com String gigante)
string decimalParaOctal(string decimal) {
    if (decimal == "0" || decimal == "") return "0";
    string octal = "";
    while (decimal != "0") {
        int resto;
        decimal = dividirString(decimal, 8, resto);
        octal = to_string(resto) + octal;
    }
    return octal;
}

//hexadecimal -->Decimal
string hexadecimalParaDecimal(string hexadecimal) {
    string decimal = "0";
    for(char c : hexadecimal){
        c = toupper(c);
        int valor;
        if(c >= '0' && c <= '9')
            valor = c - '0';
        else if(c >= 'A' && c <= 'F')
            valor = c - 'A' + 10;
        else if(c == 'H') continue;
        else return "ERRO";
        decimal = multiplicarString(decimal, 16);
        decimal = somarString(decimal, valor);
    }
    return decimal;
}

//Decimal-->hexadecimal
string decimalParaHexadecimal(string decimal) {
    if(decimal == "0" || decimal == "")
        return "0";
    string hexadecimal = "";
    while(decimal != "0"){
        int resto;
        decimal = dividirString(decimal, 16, resto); // Usa a nova funcao generica
        if(resto < 10)
            hexadecimal = char(resto + '0') + hexadecimal;
        else
            hexadecimal = char(resto - 10 + 'A') + hexadecimal;
    }
    return hexadecimal;
}

//  "Menu" e processamento da conversao
void menu(){
    int baseEntrada, baseSaida;
    string entrada;

    cout << "=== CONVERSOR DE BASES ===" << endl;
    cout << "1- Binario (base 2)" << endl;
    cout << "2- Ternaria (base 3)" << endl;
    cout << "3- Octal (base 8)" << endl;
    cout << "4- Decimal (base 10)" << endl;
    cout << "5- Hexadecimal (base 16)" << endl;
    
    cout << "\nEscolha a base de ENTRADA (1-5): ";
    cin >> baseEntrada;
    //caso digite um numero diferente de 1 2 3 4 ou 5
    if(baseEntrada<1 || baseEntrada>5){
    	cout<<"Opcao de base de entrada invalida (digite apenas numeros de 1 a 5)!";
    	return;
	}
     //caso digite uma letra na entrada
    if(cin.fail()) {
        cin.clear(); //limpa o estado de erro do cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //descarta o texto incorreto
        cout << "Opcao de base de entrada invalida (digite apenas numeros de 1 a 5)!" << endl;
        return;
    }
    cout << "Digite o numero na base escolhida: ";
    cin >> entrada;
   

    cout << "\nEscolha a base de SAIDA (1-5): ";
    cin >> baseSaida;
    //caso digite um numero na base de saida
    if(cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Opcao de base de saida invalida (digite apenas numeros de 1 a 5)!" << endl;
        return;
    }

    string decimalStr = "";  
    string resultado;

    // Converter entrada para decimal utilizando apenas strings
    switch (baseEntrada) {
        case 1:
            decimalStr = binarioParaDecimal(entrada);
            if (decimalStr == "ERRO") { cout << "Erro: Numero invalido para Binario!" << endl; return; }
            break;
        case 2:
            decimalStr = ternarioParaDecimal(entrada);
            if (decimalStr == "ERRO") { cout << "Erro: Numero invalido para Ternario!" << endl; return; }
            break;
        case 3:
            decimalStr = octalParaDecimal(entrada);
            if (decimalStr == "ERRO") { cout << "Erro: Numero invalido para Octal!" << endl; return; }
            break;
        case 4:
            // Garante que a entrada decimal e valida
            for(char c : entrada) {
                if(!isdigit(c)) { cout << "Erro: Numero decimal invalido!" << endl; return; }
            }
            decimalStr = entrada;
            break;
        case 5:
            decimalStr = hexadecimalParaDecimal(entrada);
            if (decimalStr == "ERRO") {
                cout << "Erro: Numero invalido para hexadecimal"<<endl;
                return;
            }
            break;
    }

    // Converter decimal para base de saida utilizando apenas strings
    switch (baseSaida) {
        case 1:
            resultado = decimalParaBinario(decimalStr);
            break;
        case 2:
            resultado = decimalParaTernario(decimalStr);
            break;
        case 3:
            resultado = decimalParaOctal(decimalStr);
            break;
        case 4:
            resultado = decimalStr;
            break;
        case 5:
            resultado = decimalParaHexadecimal(decimalStr);
            break;
        default:
            cout << "Opcao de base de saida invalida!" << endl;
            return;
    }

    cout << "\nResultado: " << resultado << endl;
}

int main() {
    char repetir;

    do {
        menu();
        do {
            cout << "\nDeseja fazer outra conversao? (S/N): ";
            cin >> repetir;
            
            if (cin.peek() != '\n') {
                repetir = 'I'; 
            } else {
                repetir = toupper(repetir); 
            }

            // Limpa o resto do digitado
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;

            if (repetir != 'S' && repetir != 'N') {
                cout << "Opcao invalida (digite apenas S ou N)\n";
            }

        } while (repetir != 'S' && repetir != 'N');
            
    } while (repetir == 'S');
    
    cout << "Programa encerrado.\n";
    return 0;
}
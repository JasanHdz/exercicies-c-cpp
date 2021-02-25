#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <string>
#include <wchar.h>
#include <locale.h>

using namespace std;

class Casino {
  private:
    int balance;
    int betAmount;
    int selectNumber;
    int crupierBalance;
    string name;
    void showMenu();
    void toBet();
    void chooseNumber();
    void compareNumbers(int);
    bool setBetAmount(int);
    bool setSelectNumber(int);
    int rollDice(int, int);
  public:
    void runGame();
    int getBalance();
    int getCrupierBalance();
    Casino(int, int);
};

int Casino::getBalance() {
  return this->balance;
}
int Casino::getCrupierBalance() {
  return this->crupierBalance;
}

Casino::Casino(int balance, int crupierBalance) {
  this->balance = balance;
  this->crupierBalance = crupierBalance;
}

bool Casino::setBetAmount(int betAmount) {
  if(betAmount <= this->balance) {
    if(betAmount <= 0) {
      cout << "La apuesta no debe ser menor o igual que 0 \n";
      return false;
    } 
    this->betAmount = betAmount;
    return true;
  } 
  cout << "Saldo insuficiente :( \n";
  return false;
}

bool Casino::setSelectNumber(int number) {
  if(number <= 6) {
    if(number <= 0) {
      cout << "El número seleccionado no debe ser menor que 0 \n";
      return false;
    }
    this->selectNumber = number;
    return true;
  }
  cout << "El número seleccionado no debe ser mayor que 6 \n";
  return false;
}

int Casino::rollDice(int from, int to) {
  srand(time(NULL));
  int random = rand()%(to - from+1)+from;
  return random;
}

void Casino::compareNumbers(int randomNumber) {
  if(randomNumber == this->selectNumber) {
    this->balance = this->balance + this->betAmount;
    this->crupierBalance = this->crupierBalance - this->betAmount;
    cout << "Felicidades a GANADO " << this->betAmount << " PESOS MX :) \n";
    cout << "El número aletorio es " << randomNumber << " y el número selecionado es: " << this->selectNumber << "\n";
    cout << "Su saldo actual ahora es de $" << this->balance << " PESOS MX \n";
    cout << "El saldo de CRUPIER ahora es de $" << this->crupierBalance << " PESOS MX \n";
  } else if(randomNumber % 2 != 0 && this->selectNumber % 2 != 0) {
    cout << "Golpe de SUERTE :) \n";
    cout << "El número aletorio es " << randomNumber << " y el número selecionado es: " << this->selectNumber;
    cout << "\nAmbos Números son IMPARES por lo tanto estó es un EMPATE \n";
  } else if(randomNumber % 2 == 0 && this->selectNumber % 2 == 0) {
    cout << "Golpe de SUERTE :) \n";
    cout << "El número aletorio es " << randomNumber << " y el número selecionado es: " << this->selectNumber;
    cout << "\nAmbos Números son PARES por lo tanto estó es un EMPATE \n";
  } else {
    this->balance = this->balance - this->betAmount;
    this->crupierBalance = this->crupierBalance + this->betAmount;
    cout << "Upps: :( No tuvó suerte en esté tiro \n";
    cout << "El número aletorio es " << randomNumber << " y el número selecionado es: " << this->selectNumber << " \n";
    cout << this->name << " usted acaba de perder " << this->betAmount << " PESOS MX \n";
    cout << "Su saldo actual ahora es de $" << this->balance << " PESOS MX \n";
    cout << "El saldo de CRUPIER ahora es de $" << this->crupierBalance << " PESOS MX \n";
  }
}

void Casino::showMenu() {
  cout << "*******************************************************************************************\n";
  cout << ":::::::::::::::: Bienvenido al Casino " << this->name <<  " :::::::::::::::: \n\n";
  cout << "Descripción del Juego: \n";
  cout << "Se Tira un dado entre 1 y 6 y usted deberá adivinar que número cayo. \n\n";
  cout << "**Reglas** \n";
  cout << "1. Usted tiene la cantidad inicial de " << this->balance << " PESOS MX. \n";
  cout << "2. El CRUPIER tiene un saldo de: " << this->crupierBalance << " PESOS MX. \n";
  cout << "3. Usted es capaz de apostar una cantidad que no sea 0 y tampoco sea mayor a su saldo actual. \n";
  cout << "4. Si usted le atina al número que cayó usted GANA Y CRUPIER le pagá su apuesta. \n";
  cout << "5. Si el número que escribió es IMPAR y el número que cayó es IMPAR, se considerará EMPATE. \n";
  cout << "6. Si el número que escribió es PAR y el número que cayó es PAR, se considerará EMPATE. \n";
  cout << "7. Si usted no le atina al número que cayo pierde su apuesta y el CRUPIER la gana. \n";
  cout << "8. El juego terminará cuando su saldo esté en 0 o el saldo del CRUPIER sea 0. \n";
  cout << "*******************************************************************************************\n";
}

void Casino::toBet() {
  int apuesta;
  cout << "Ingresa la cantidad que deseas apostar: ";
  cin >> apuesta;
  bool isCorrect = this->setBetAmount(apuesta);
  if(isCorrect == false) {
  	this->toBet();
  }
}

void Casino::chooseNumber() {
  int selectNumber;
  cout << "Elige un número del 1 al 6: ";
  cin >> selectNumber;
  bool isCorrect = this->setSelectNumber(selectNumber);
  if(isCorrect == false) {
    this->chooseNumber();
  }
}


void Casino::runGame() {
  cout << "Escribe tu nombre antes de comenzar: ";
  getline(cin, this->name);
  this->showMenu();
  while (this->getBalance() && this->getCrupierBalance()) {
    this->toBet();
    this->chooseNumber();
    int random = this->rollDice(1, 6);
    this->compareNumbers(random);
  }
  
}

int main() {
  setlocale(LC_ALL, "");
  Casino casino = Casino(500, 1000);
  casino.runGame();
  system("pause");
  return 0;
}

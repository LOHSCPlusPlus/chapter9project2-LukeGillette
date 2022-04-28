#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Videogame{
  Videogame();
  enum{MAX_CHAR_SIZE = 100};
  char Name[MAX_CHAR_SIZE];
  double Sales;
  char Platform[MAX_CHAR_SIZE];
  char Release[MAX_CHAR_SIZE];
  char Developer[MAX_CHAR_SIZE];
  char Publisher[MAX_CHAR_SIZE];
};

const int maxGames = 300;

Videogame::Videogame(){
  for(int index = 0; index < MAX_CHAR_SIZE; index++){
    Name[index] = 0;
    Platform[index] = 0;
    Release[index] = 0;
    Developer[index] = 0;
    Publisher[index] = 0;
  }
  Sales = 0;
}

double readdouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
int readint(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

Videogame readGame(ifstream &inFile){
  Videogame game;
  inFile.get(game.Name, Videogame::MAX_CHAR_SIZE,';');
  inFile.ignore(100,';');
  inFile >> game.Sales;
  inFile.ignore(100,';');
inFile.get(game.Platform,Videogame::MAX_CHAR_SIZE,';');
  inFile.ignore(100,';'); 
inFile.get(game.Release,Videogame::MAX_CHAR_SIZE,';');
  inFile.ignore(100,';');
  inFile.get(game.Developer, Videogame::MAX_CHAR_SIZE,';');
  inFile.ignore(100,';');
  inFile.get(game.Publisher, Videogame::MAX_CHAR_SIZE,'\n');
  inFile.ignore(100,'\n');
  return game;
}

int readGame(Videogame games[]){
  ifstream GameFile("videogames.txt");
  int numGames = 0;
  while(GameFile.peek() != EOF){
    games[numGames] = readGame(GameFile);
    numGames++;
  }
  return numGames;
}

const int MaxGame = 51;
Videogame readGameUser(){
  Videogame game;
  cout << "enter the name";
  cin.get(game.Name, Videogame::MAX_CHAR_SIZE,'\n');
  cin.ignore(100,'\n');
  game.Sales = readdouble("enter the sales");
  cin.ignore(100,'\n');
  cout << "enter the platform";
  cin.get(game.Platform, Videogame::MAX_CHAR_SIZE,'\n');
  cin.ignore(100,'\n');
  cout << "enter the release date";
  cin.get(game.Release, Videogame::MAX_CHAR_SIZE,'\n');
  cin.ignore(100,'\n');
  cout << "enter the developer";
  cin.get(game.Developer, Videogame::MAX_CHAR_SIZE,'\n');
  cin.ignore(100,'\n');
  cout << "enter the publisher";
  cin.get(game.Publisher, Videogame::MAX_CHAR_SIZE,'\n');
  cin.ignore(100,'\n');
  return game;
}

void printGame(ostream &out, Videogame game){
    out << game.Name << ";";
    out << game.Sales << ";";
    out << game.Platform << ";";
    out << game.Release << ";";
    out << game.Developer << ";";
    out << game.Publisher << endl;
  }

void printArrayToScreen(Videogame examples[], int numExamples) {
    for (int index = 0; index < numExamples; index++) {
        cout << "Index " << index << ": ";
        printGame(cout, examples[index]);
    }
}

void printArrayToFile(const char fileName[], Videogame examples[], int numExamples) {
    ofstream outFile(fileName);
    for (int index = 0; index < numExamples; index++) {
        printGame(outFile, examples[index]);
    }
}

void addGame(Videogame game[], int index){
  game[index] = readGameUser();
}

void removeGame(Videogame game[], int numGames){
  int index = readint("which index would you like to remove?");
  if (index >= 0){
    for(int delIndex = index; delIndex < numGames - 1; delIndex++){
      game[delIndex] = game[delIndex + 1];
    }
  }
  
}

void searchGame(Videogame examples[], int numExamples) {
  int numSales = readint("enter the number of sales");
    for (int index = 0; index < numExamples; index++) {
      if(examples[index].Sales > numSales){
        cout << "Index " << index << ": ";
        printGame(cout, examples[index]);
        }
    }
}
void menu(){
  Videogame Game[maxGames];
  int numGames;
 numGames = readGame(Game);
   string option;
  while(option != "quit"){
  cout << "Car File:" << endl << "List" << endl << "Remove" << endl << "Add" << endl << "search" << endl << "Quit" << endl;
  cin >> option;
  if (option == "List"){
    printArrayToScreen(Game,numGames);
    }
  else if (option == "Remove"){
    removeGame(Game,numGames);
    numGames--;
  }
  else if (option == "Add"){
    addGame(Game,numGames);
    numGames++;
  }
  else if (option == "search"){
    searchGame(Game,numGames);
  }
  else if (option == "quit"){
      return;
  }
  else{
    cout << "not a valid option" << endl;
  }
}
  }
int main(){
menu();

  
}

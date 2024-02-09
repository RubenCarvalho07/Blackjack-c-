#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 

using namespace std;

string deck[52];

int x = 0;
int y = -1;

int dealerSum = 0;
int dealerAceCount = 0;
int dealerCards[52] = {};
int yourSum = 0;
int yourAceCount = 0; 
int yourCards[52] = {};

void createAndShuffleDeck();
void drawCard(int& sum, int cards[], int& count, int& aceCount);
void reduceAces(int& sum, int& aceCount);
void checkResults();

int value(string card, int& aceCount);
int length(int array[]);

int main(){
    createAndShuffleDeck();
    int dealerCount = 0;
    while (dealerSum < 17){
        drawCard(dealerSum, dealerCards, dealerCount, dealerAceCount);
    }
    
    int yourCount = 0;
    for (int i = 0; i < 2; i++){
        drawCard(yourSum, yourCards, yourCount, yourAceCount);
    }
    while (y != 0 && yourSum <= 21){
        system("clear");
        cout << "Dealer (?) : ?-?";
        for (int i = 1; i < length(dealerCards); i++){
            cout << " " << deck[dealerCards[i] - 1];
        }
        cout << "\nTu (" << yourSum << ") : ";
        for (int i = 0; i < length(yourCards); i++){
            cout << deck[yourCards[i] - 1] << " ";
        }
        
        cout << "\n\nFicar(0) / Pedir(1) -> ";
        cin >> y;
        switch (y){
            case 0:
                checkResults();
                break;
            case 1:
                drawCard(yourSum, yourCards, yourCount, yourAceCount);
                break;
            default:
                cout << "\nIrreconhecido!!!\n\n";
                break;
        }
    }
    if (yourSum > 21){
        system("clear");
        cout << "Dealer (?) : ?-?";
        for (int i = 0; i < length(dealerCards); i++){
            cout << " " << deck[dealerCards[i] - 1];
        }
        cout << "\nTu (" << yourSum << ") : ";
        for (int i = 0; i < length(yourCards); i++){
            cout << deck[yourCards[i] - 1] << " ";
        }
            cout << "\n\nRebentas-te...";
        }
    return 0;
}

void createAndShuffleDeck(){
    char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char types[4] = {'S', 'H', 'C', 'D'};
    srand((unsigned)time(0));

    int index = 0;
    for (int i = 0; i < 4; i++){
        for (int c = 0; c < 13; c++){
            deck[index++] = string(1, values[c]) + "-" + types[i];
        }
    }
    
    for (int i = 0; i < 52; i++){
        int r = rand() % 52;
        string temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

void drawCard(int& sum, int cards[], int& count, int& aceCount){
    if (x >= 52) {
        x = 0;
    }
    sum += value(deck[x], aceCount);
    cards[count] = x + 1;
    count++;
    x++;
    reduceAces(sum, aceCount);
}

void reduceAces(int& sum, int& aceCount){
    while (sum > 21 && aceCount > 0){
        sum -= 10;
        aceCount--;
    }
}

void checkResults(){
    system("clear");
    cout << "Dealer (" << dealerSum << ") : ";
    for (int i = 0; i < length(dealerCards); i++){
        cout << " " << deck[dealerCards[i] - 1];
    }
    cout << "\nTu (" << yourSum << ") : ";
    for (int i = 0; i < length(yourCards); i++){
        cout << deck[yourCards[i] - 1] << " ";
    }
    if (dealerSum > 21 || yourSum > dealerSum){
        cout << "\n\nGanhas-te!!!";
    } else if (dealerSum > yourSum){
        cout << "\n\nPerdes-te...";
    } else {
        cout << "\n\nEmpate!!!";
    }
}

int value(string card, int& aceCount){
    char valor = card[0];

    if (valor == 'A'){
        aceCount++;
        return 11;
    } else if (valor == 'T' || valor == 'J' || valor == 'Q' || valor == 'K') {
        return 10;
    }
    return valor - '0';
}

int length(int array[]){
    int i = 0;
    while (array[i] != 0) {
        i++;
    }
    return i;
}

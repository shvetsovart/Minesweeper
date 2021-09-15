#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void out(vector<vector<char>> a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

void Flag(vector<vector<char>>& player, int a, int b) {
    if (player[a][b] == '*') {
        player[a][b] = '#';
        return;
    }
    if (player[a][b] >= '0' && player[a][b] <= '9') {
        cout << "This field is already opened\n";
    }
    else {
        player[a][b] = '*';
    }
}

void Open(vector<vector<int>>& pole, vector<vector<char>>& player, int a, int b) {
    if (player[a][b] == '*') {
        cout << "Unlock the field first\n";
        return;
    }
    if (pole[a][b]) {
        cout << "Game Over\n";
        exit(0);
    }
    player[a][b] = '0';
    int cnt_mines = 0;
}

void numbers(vector<vector<int>>& pole, vector<vector<char>>& player, int a, int b) {

}

int main() {
    //load_game
    //добавить нормальный рандом с временем

    srand(time(0));
    int n, m;
    //cin >> n >> m;
    n = 5, m = 5;

    int mines = 2 + rand() % 3; //fix
    vector<vector<int>> pole(n, vector<int>(m, 0));
    vector<vector<char>> player(n, vector<char>(m, '#'));
    out(player);

    int a, b;
    string option;

    while (1) {
        cin >> a >> b >> option;
        a--;
        b--;
        if (option == "Flag") {
            Flag(player, a, b);
            out(player);
        }
        else if (option == "Open") {
            for (int i = 0; i < mines; ++i) {
                int y = rand() % n, x = rand() % m;
                while (pole[y][x] || (y == a && x == b)) {
                    y = rand() % n, x = rand() % m;
                }
                pole[y][x] = 1;
            }
            Open(pole, player, a, b);
            out(player);
            if (player[a][b] == '0') {
                break;
            }
        }
        else {
            cout << "Unknown command\n";
        }
    }

    /*out(player);*/
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << pole[i][j] << ' ';
        }
        cout << endl;
    }

    while (1) {
        int a, b;
        string action;
        cin >> a >> b >> action;
        a--;
        b--;
        if (action == "Flag") {
            Flag(player, a, b);
        }
        else if (action == "Open") {
            Open(pole, player, a, b);
            numbers(pole, player, a, b);
        }
        if (mines == 0) {
            cout << "You win!";
            return 0;
        }
        out(player);
    }
}

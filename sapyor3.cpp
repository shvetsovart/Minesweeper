#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int n, m;

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

char numbers(vector<vector<int>>& pole, vector<vector<char>>& player, int a, int b) {
    int cnt_numbers = 0;
    if (pole[a][b]) {
        return '(';
    }
    if (a > 0) {
        if (pole[a - 1][b]) {
            cnt_numbers++;
        }
    }
    if (b > 0) {
        if (pole[a][b - 1]) {
            cnt_numbers++;
        }
    }
    if (a < n - 1) {
        if (pole[a + 1][b]) {
            cnt_numbers++;
        }
    }
    if (b < m - 1) {
        if (pole[a][b + 1]) {
            cnt_numbers++;
        }
    }
    if (a > 0 && b > 0) {
        if (pole[a - 1][b - 1]) {
            cnt_numbers++;
        }
    }
    if (a > 0 && b < m - 1) {
        if (pole[a - 1][b + 1]) {
            cnt_numbers++;
        }
    }
    if (a < n - 1 && b > 0) {
        if (pole[a + 1][b - 1]) {
            cnt_numbers++;
        }
    }
    if (a < n - 1 && b < n - 1) {
        if (pole[a + 1][b + 1]) {
            cnt_numbers++;
        }
    }
    return cnt_numbers + '0';
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
    player[a][b] = numbers(pole, player, a, b);
    int cnt_mines = 0;
}

void check(vector<vector<int>>& pole, vector<vector<char>>& player, int a, int b) {
    for (int a1 = a - 1; a1 <= a + 1; a1++) {
        for (int b1 = b - 1; b1 <= b + 1; b1++) {
            if (a1 == a && b1 == b) {
                continue;
            }
            if (a1 >= 0 && a1 < n) {
                if (b1 >= 0 && b1 < m) {
                    if (numbers(pole, player, a1, b1) == '(') {
                        continue;
                    }
                    else {
                        player[a1][b1] = numbers(pole, player, a1, b1);
                    }
                }
            }
        }
    }
}

int main() {
    //load_game
    //добавить нормальный рандом с временем

    srand(time(0));
    //cin >> n >> m;
    n = 5, m = 5;

    int mines = 2 + rand() % 3; //fix
    vector<vector<int>> pole(n, vector<int>(m, 0));
    vector<vector<char>> player(n, vector<char>(m, '#'));
    out(player);
    cout << "Make your move\n";

    int a, b;
    string option;
    int opened = 0;

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
            if (player[a][b] != '#' && player[a][b] != '*') {
                check(pole, player, a, b);
                out(player);
                break;
            }
            out(player);
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
            check(pole, player, a, b);
        }
        else {
            cout << "Unknown command\n";
            continue;
        }
        if (mines == 0) {
            cout << "You win!";
            return 0;
        }
        out(player);
    }
}

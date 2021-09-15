#include <iostream>
#include <string>
#include <vector>

using namespace std;

void out(vector<vector<char>> a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    //load_game

    int n, m;
    //cin >> x >> y;
    n = 5, m = 5;

    int mines = 2 + rand() % 3; //fix
    vector<vector<int>> pole(n, vector<int>(m, 0));
    vector<vector<char>> player(n, vector<char>(m, 0));

    for (int i = 0; i < mines; ++i) {
        int y = rand() % n, x = rand() % m;
        while (pole[y][x]) {
            y = rand() % n, x = rand() % m;
        }
        pole[y][x] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            player[i][j] = '#';
        }
    }

    int flags = mines;

    while (1) {
        int a, b;
        string action;
        cin >> a >> b >> action;
        if (action == "Flag") { // нужно проверить, открыта ли ячейка
            if (player[a][b] >= '0' && player[a][b] <= '9') {
                cout << "This field is opened";
            }
            else {
                player[a][b] = '*';
            }
        }
        else if (action == "Open") {
            if (pole[a][b]) {
                cout << "Game Over";
                return 0;
            }
            int cnt_mines = 0;
            if (1) { // показать циферки
                continue;
            }
        }
        out(player);
    }
}

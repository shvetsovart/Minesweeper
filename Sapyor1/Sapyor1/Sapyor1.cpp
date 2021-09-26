#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

int n, m;

vector<vector<char>> player;
vector<vector<int>> pole, nums, seen;

void player_out(vector<vector<char>> a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

void pole_out(vector<vector<int>> a) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

void flag_player(int a, int b) {
    if (player[a][b] == '*') {
        player[a][b] = '#';
        return;
    }
    if (player[a][b] >= '0' && player[a][b] <= '9') {
        return;
    }
    else {
        player[a][b] = '*';
    }
}

char numbers(int a, int b) {
    int cnt_numbers = 0;
    if (pole[a][b]) {
        return 0;
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
    return cnt_numbers;
}

int game_over() {
    int cnt = 0;
    for (int i = 0; i < player.size(); ++i) {
        for (int j = 0; j < player[i].size(); ++j) {
            if (player[i][j] >= '0' && player[i][j] <= '9') {
                cnt++;
            }
        }
    }
    return cnt;
}

void open_player(int a, int b) {
    if (seen[a][b]) {
        return;
    }
    seen[a][b] = 1;
    if (pole[a][b]) {
        return;
    }
    player[a][b] = (nums[a][b] + '0');
    if (a > 0) {
        if (nums[a - 1][b] == 0) {
            open_player(a - 1, b);
        }
        else {
            player[a - 1][b] = (nums[a - 1][b] + '0');
        }
    }
    if (b > 0) {
        if (nums[a][b - 1] == 0) {
            open_player(a, b - 1);
        }
        else {
            player[a][b - 1] = (nums[a][b - 1] + '0');
        }
    }
    if (a < n - 1) {
        if (nums[a + 1][b] == 0) {
            open_player(a + 1, b);
        }
        else {
            player[a + 1][b] = (nums[a + 1][b] + '0');
        }
    }
    if (b < m - 1) {
        if (nums[a][b + 1] == 0) {
            open_player(a, b + 1);
        }
        else {
            player[a][b + 1] = (nums[a][b + 1] + '0');
        }
    }
}

void neww() {
    ofstream fout("load_game.txt");
    //ifstream fin;
    //fin.open("load_game.txt");
    cout << "Enter the size of the field (each size >= 3)\n";
    cin >> n >> m;

    fout << n << ' ' << m << '\n';
    pole.resize(n, vector<int>(m, 0));
    nums.resize(n, vector<int>(m, 0));
    seen.resize(n, vector<int>(m, 0));
    player.resize(n, vector<char>(m, '#'));

    int mines = 1 + (n * m) / 12 + rand() % (1 + (n * m) / 12);

    int a, b;
    string option;
    int opened = 0;

    while (1) {
        cout << "Make your move\n";
        cin >> a >> b >> option;
        a--;
        b--;
        if (option == "Flag") {
            flag_player(a, b);
            player_out(player);
        }
        else if (option == "Open") {
            //cout << 1 << endl;
            for (int i = 0; i < mines; ++i) {
                int y = rand() % n, x = rand() % m;
                while (pole[y][x] || (y == a && x == b)) {
                    y = rand() % n, x = rand() % m;
                }
                pole[y][x] = 1;
            }
            //cout << 1 << endl;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    nums[i][j] = numbers(i, j);
                }
            }
            //cout << 1 << endl;
            bool was_opened = false;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (pole[i][j] != 0) {
                        was_opened = true;
                        break;
                    }
                }
            }
            //pole_out(nums);
            //cout << '\n';
            //pole_out(pole);
            if (was_opened == true) {
                open_player(a, b);
                //cout << 1 << endl;
                player_out(player);
                break;
            }
            player_out(player);
        }
        else {
            cout << "Unknown command\n";
        }
    }

    //pole_out(nums);
    //pole_out(pole);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int rand1 = rand() % 100, rand2 = 1 + rand() % 100;
            fout << (pole[i][j] + 4 * rand1) * rand2 << ' ' << rand1 << ' ' << rand2 << '\n';
        }
    }

    fout << a + 1 << ' ' << b + 1 << ' ' << option << '\n';

    while (1) {
        if (n * m - game_over() <= mines) {
            cout << "You Win!\n";
            pole_out(pole);
            //fin.close();
            fout.close();
            return;
        }
        cout << "Make your move\n";
        cin >> a >> b >> option;
        if (a == -1 && b == -1 && option == "Save") {
            cout << "The game is saved. See you soon\n";
            fout.close();
            return;
        }
        fout << a << ' ' << b << ' ' << option << '\n';
        a--;
        b--;
        if (option == "Flag") {
            if (player[a][b] >= '0' && player[a][b] <= '9') {
                cout << "This field is already opened\n";
                player_out(player);
                continue;
            }
            flag_player(a, b);
            player_out(player);
        }
        else if (option == "Open") {
            if (player[a][b] == '*') {
                cout << "Unlock the field first\n";
                player_out(player);
                continue;
            }
            if (pole[a][b] == 1) {
                cout << "Game Over!\n";
                pole_out(pole);
                //fin.close();
                fout.close();
                return;
            }
            if (n * m - game_over() <= mines) {
                cout << "You Win!\n";
                pole_out(pole);
                //fin.close();
                fout.close();
                return;
            }
            open_player(a, b);
            player_out(player);
        }
        else {
            cout << "Unknown command\n";
        }
    }
    //fin.close();
    fout.close();
}

void load() {
    ifstream fin("load_game.txt");
    //cout << '!' << '\n';

    fin >> n >> m;
    int mines = 0;
    pole.resize(n, vector<int>(m, 0));
    nums.resize(n, vector<int>(m, 0));
    seen.resize(n, vector<int>(m, 0));
    player.resize(n, vector<char>(m, '#'));
    //cout << '!' << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a, b, c;
            fin >> a >> b >> c;
            pole[i][j] = (a / c) - 4 * b;
            if (pole[i][j]) {
                mines++;
            }
        }
    }
    //cout << '!' << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            nums[i][j] = numbers(i, j);
        }
    }

    int a, b;
    string option;
    vector<string> options;
    //cout << '!' << '\n';
    while (fin >> a >> b >> option) {
        if (n * m - game_over() <= mines) {
            cout << "You Win!\n";
            pole_out(pole);
            fin.close();
            //fout.close();
            return;
        }
        //cout << "Make your move\n";
        options.push_back(to_string(a));
        options.push_back(to_string(b));
        options.push_back(option);
        a--;
        b--;
        if (option == "Flag") {
            if (player[a][b] >= '0' && player[a][b] <= '9') {
                continue;
            }
            flag_player(a, b);
        }
        else if (option == "Open") {
            if (player[a][b] == '*') {
                continue;
            }
            if (pole[a][b] == 1) {
                cout << "Game Over!\n";
                pole_out(pole);
                fin.close();
                //fout.close();
                return;
            }
            if (n * m - game_over() <= mines) {
                cout << "You Win!\n";
                pole_out(pole);
                fin.close();
                //fout.close();
                return;
            }
            open_player(a, b);
        }
        else {
            cout << "Unknown command\n";
        }
    }
    //cout << '!' << '\n';
    fin.close();
    player_out(player);
    ofstream fout("load_game.txt");

    fout << n << ' ' << m << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int rand1 = rand() % 100, rand2 = 1 + rand() % 100;
            fout << (pole[i][j] + 4 * rand1) * rand2 << ' ' << rand1 << ' ' << rand2 << '\n';
        }
    }
    for (int i = 0; i < options.size(); i += 3) {
        fout << options[i] << ' ' << options[i + 1] << ' ' << options[i + 2] << '\n';
    }

    while (1) {
        if (n * m - game_over() <= mines) {
            cout << "You Win!\n";
            pole_out(pole);
            fout.close();
            return;
        }
        cout << "Make your move\n";
        cin >> a >> b >> option;
        if (a == -1 && b == -1 && option == "Save") {
            cout << "The game is saved. See you soon\n";
            fout.close();
            return;
        }
        fout << a << ' ' << b << ' ' << option << '\n';
        a--;
        b--;
        if (option == "Flag") {
            if (player[a][b] >= '0' && player[a][b] <= '9') {
                cout << "This field is already opened\n";
                player_out(player);
                continue;
            }
            flag_player(a, b);
            player_out(player);
        }
        else if (option == "Open") {
            if (player[a][b] == '*') {
                cout << "Unlock the field first\n";
                player_out(player);
                continue;
            }
            if (pole[a][b] == 1) {
                cout << "Game Over!\n";
                pole_out(pole);
                fout.close();
                return;
            }
            if (n * m - game_over() <= mines) {
                cout << "You Win!\n";
                pole_out(pole);
                fout.close();
                return;
            }
            open_player(a, b);
            player_out(player);
        }
        else {
            cout << "Unknown command\n";
        }
    }
    fout.close();
}

int main() {
    srand(time(0));

    cout << "\"Load\" or \"New\" game?\n";
    string start;
    cin >> start;
    while (start != "Load" && start != "New") {
        cout << "Unknown command\n\"Load\" or \"New\" game?\n";
        cin >> start;
    }

    if (start == "New") {
        neww();
    }
    else {
        load();
    }
}

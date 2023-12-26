#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const int N = 19;
const int way = -3, wall = -2, pass = -1;
int labyrinth[N][N];
vector<pair<int, int>> wave;


bool tupik(int x, int y, int labyrinth[N][N], int height, int width) {
    int a = 0;

    if (x != 1) {
        if (labyrinth[y][x - 2] == pass)
            a += 1;
    }
    else a += 1;

    if (y != 1) {
        if (labyrinth[y - 2][x] == pass)
            a += 1;
    }
    else a += 1;

    if (x != width - 2) {
        if (labyrinth[y][x + 2] == pass)
            a += 1;
    }
    else a += 1;

    if (y != height - 2) {
        if (labyrinth[y + 2][x] == pass)
            a += 1;
    }
    else a += 1;

    if (a == 4)
        return 1;
    else
        return 0;
}

bool end(int labyrinth[N][N], int height, int width) {
    bool b = 1;

    for (int i = 1; i < (height - 1); i += 2)
        for (int j = 1; j < (width - 1); j += 2)
            if (labyrinth[i][j] == wall)
                b = 0;
    return b;
}

void generate(int labyrinth[N][N], int height, int width) {
    int x, y, c, a;
    bool b;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            labyrinth[i][j] = wall;

    x = 3; y = 3; a = 0;
    while (1)
    {
        a++;
        if (a % 100 == 0)
            if (end(labyrinth, height, width))
                break;
        labyrinth[y][x] = pass;
        while (1) {
            c = rand() % 4;
            switch (c) {
            case 0: if (y != 1)
                if (labyrinth[y - 2][x] == wall) {
                    labyrinth[y - 1][x] = pass;
                    labyrinth[y - 2][x] = pass;
                    y -= 2;
                }
            case 1: if (y != height - 2)
                if (labyrinth[y + 2][x] == wall) {
                    labyrinth[y + 1][x] = pass;
                    labyrinth[y + 2][x] = pass;
                    y += 2;
                }
            case 2: if (x != 1)
                if (labyrinth[y][x - 2] == wall) {
                    labyrinth[y][x - 1] = pass;
                    labyrinth[y][x - 2] = pass;
                    x -= 2;
                }
            case 3: if (x != width - 2)
                if (labyrinth[y][x + 2] == wall) {
                    labyrinth[y][x + 1] = pass;
                    labyrinth[y][x + 2] = pass;
                    x += 2;
                }
            }
            if (tupik(x, y, labyrinth, height, width))
                break;
        }

        if (tupik(x, y, labyrinth, height, width))
            do {
                x = 2 * (rand() % ((width - 1) / 2)) + 1;
                y = 2 * (rand() % ((height - 1) / 2)) + 1;
            } while (labyrinth[y][x] != pass);
    }
}

void print()
{
    system("cls");
    int count = 0;
    string name1 = std::to_string(N) + "way_to_exit.txt";
    ifstream wayin(name1);
    wayin.close();
    ofstream wayout(name1);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (labyrinth[i][j] == wall) {
                cout << "O ";
                wayout << "O ";
            }
            else if (labyrinth[i][j] == way) {
                cout << "+ ";
                wayout << "+ ";

            }
            else {
                cout << "  ";
                wayout << "  ";
            }

        }
        wayout << '\n';
        cout << '\n';
    }
    wayout.close();
}

int main(int argc, char** argv)
{
h1:
    int x = N - 2;
    int y = N - 2;
    int next = 0;
    vector<pair<int, int>> vect;
    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { -1, 0, 1, 0 };
    int res, n, s;
    int count1 = 0;
    bool flag = true;
    int check = 0;
    int check1 = 0;
    char m;
    std::string coords;
    string name2 = std::to_string(N) + "way_to_exit(coords).txt";
    ifstream coordsin(name2);
    coordsin.close();
    ofstream coordout(name2);
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    system("cls");
    printf("\t\t\tМинистерство науки и образования Российской Федерации\n");
    printf("\t\t\t\tПензенский государственный университет\n\n");
    printf("\t\t\t\t\tКурсовая работа на тему:\n");
    printf("\t\t\t    Реализация алгоритма поиска путей в лабиринте\n\n\n\n");
    printf("\t\t\t\t\t\t\t\tСделал ст. гр. 22ВВС1:\n");
    printf("\t\t\t\t\t\t\t\t\tБеккаревич К.А.\n\n\n");
    printf("Выберите действие:\n");
    printf("1 - Сгенерировать лабиринт случайно\n");
    printf("2 - Получить лабирит из файла\n");
    printf("3 - Выйти\n");
    do {
        res = scanf_s("%d", &n);
        while (getchar() != '\n');
        if (res == 1 && (n <= 3 && n > 0)) {
            printf("\n");
        }
        else {
            system("cls");
            printf("%s\n", "Ошибка! Попробуйте еще раз\n");
            goto h1;
        }
    } while (res != 1);
    string name = std::to_string(N) + "labyrinth.txt";
    ifstream fin(name);
    if (N % 2 == 0) {
        system("cls");
        printf("Недопустимый размер лабиринта! Измените параметр N на нечетный");
        goto h2;
    }
    if (n == 1)
    {
    h3:
        fin.close();
        ofstream fout(name);
        generate(labyrinth, N, N);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (labyrinth[i][j] == wall) {
                    fout << "O ";
                    if (i == 0 || i == (N - 1) || j == 0 || j == (N - 1)) count1++;
                }
                else
                    fout << "  ";
            }
            fout << '\n';
        }
        fout.close();
    }
    else if (n == 2)
    {
        for (int i = 0; i < N; i++)
        {
            printf("\n");
            for (int j = 0; j < N; j++)
            {
                m = fin.get();
                if (m == -1) {
                    goto h1;
                }
                if (m == 'O') {
                    labyrinth[i][j] = wall;
                }
                else
                    labyrinth[i][j] = pass;
                fin.seekg(1, ios_base::cur);
            }
            fin.seekg(2, ios_base::cur);
        }
        fin.close();
    }
    else {
        goto h2;
    }
h4:
    print();
    printf("Выберите действие:\n");
    printf("1 - Найти путь\n");
    printf("2 - Перегенерировать лабиринт\n");
    printf("3 - Вернуться в главное меню\n");
    printf("4 - Завершить программу\n");
    do {
        res = scanf_s("%d", &s);
        while (getchar() != '\n');
        if (res == 1 && (s <= 4 && s > 0)) {
            printf("\n");
        }
        else {
            system("cls");
            printf("%s\n", "Ошибка! Попробуйте еще раз\n");
            goto h4;
        }
    } while (res != 1);
    if (s == 2) goto h3;
    else if (s == 3) goto h1;
    else if (s == 4) goto h2;
    labyrinth[1][1] = pass;
    vect.push_back(pair<int, int>(1, 1));
    labyrinth[1][1] = next;
    while (vect.size() > 0)
    {
        ++next;
        wave.clear();
        for (vector < pair<int, int>> ::iterator i = vect.begin(); i != vect.end(); i++)
        {
            for (int d = 0; d < 4; ++d)
            {
                int nx = i->first + dx[d];
                int ny = i->second + dy[d];
                if (labyrinth[nx][ny] == pass)
                {
                    wave.push_back(pair<int, int>(nx, ny));
                    labyrinth[nx][ny] = next;
                    if (nx == N - 2 && ny == N - 2)
                        goto done;
                }
            }
        }
        vect = wave;
    }
done:
    wave.clear();
    wave.push_back(pair<int, int>(x, y));
    while (labyrinth[x][y] != 0)
    {
        for (int d = 0; d < 4; ++d)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (labyrinth[x][y] - 1 == labyrinth[nx][ny])
            {
                x = nx;
                y = ny;
                wave.push_back(pair<int, int>(x, y));
            }
        }
    }
    coordout << "Путь от выхода из лабиринта до входа:" << endl;
    for (vector < pair<int, int>> ::iterator i = wave.begin(); i != wave.end(); ++i)
    {
        labyrinth[i->first][i->second] = way;
        coords.append("(");
        coords.append(std::to_string(i->first));
        coords.append(", ");
        coords.append(std::to_string(i->second));
        coords.append(")");
        if (((N - 1) - i->first == (N - 2)) && ((N - 1) - i->second == (N - 2))) NULL;
        else coords.append("->");


    }
    coordout << coords;
    coordout.close();
h5:
    print();
    printf("Выберите действие:\n");
    printf("1 - Перейти в главное меню\n");
    printf("2 - Звершить программу\n");
    do {
        res = scanf_s("%d", &s);
        while (getchar() != '\n');
        if (res == 1 && (s <= 2 && s > 0)) {
            printf("\n");
        }
        else {
            system("cls");
            printf("%s\n", "Ошибка! Попробуйте еще раз\n");
            goto h5;
        }
    } while (res != 1);
    if (s == 1) goto h1;
    if (s == 2) goto h2;
h2:
    if (n == 3) system("cls");
    else system("cls");

}

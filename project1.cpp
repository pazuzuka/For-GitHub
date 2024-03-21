#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

const int WALL = 1;
const int PATH = 0;
const int GIFT = 2;

//Ну что бы было)
void just()
{
    int a = 2, b = 0;
    int c = a / b;
    try
    {
        cout << c;
    }
    catch (const exception&)
    {
        exception;
    }
}


void generateMaze(int rows, int cols, vector<vector<int>>& maze, pair<int, int>& giftLocation) {
    stack<pair<int, int>> cells;
    cells.push({ 1, 1 });

    maze[1][1] = PATH;

    while (!cells.empty())
    {
        auto current = cells.top();
        int row = current.first;
        int col = current.second;

        vector<pair<int, int>> neighbors;

        if (row >= 3 && maze[row - 2][col] == WALL)
        {
            neighbors.push_back({ row - 2, col });
        }
        if (row < rows - 2 && maze[row + 2][col] == WALL)
        {
            neighbors.push_back({ row + 2, col });
        }
        if (col >= 3 && maze[row][col - 2] == WALL) 
        {
            neighbors.push_back({ row, col - 2 });
        }
        if (col < cols - 2 && maze[row][col + 2] == WALL)
        {
            neighbors.push_back({ row, col + 2 });
        }

        if (!neighbors.empty())
        {
            int next_index = rand() % neighbors.size();
            auto next = neighbors[next_index];
            int next_row = next.first;
            int next_col = next.second;

            maze[next_row][next_col] = PATH;
            maze[(next_row + row) / 2][(next_col + col) / 2] = PATH;

            cells.push(next);
        }
        else
        {
            cells.pop();
        }
    }

    // Place the gift randomly
    int giftRow, giftCol;
    do
    {
        giftRow = rand() % (rows - 2) + 1;
        giftCol = rand() % (cols - 2) + 1;
    } while (maze[giftRow][giftCol] != PATH);

    maze[giftRow][giftCol] = GIFT;
    giftLocation = { giftRow, giftCol };
}


void player(int& playerRows, int& playerColumns, int rows, int columns, char gamer, const vector<vector<int>>& maze, const pair<int, int>& giftLocation) {
    char moving;
    cout << "Enter a move(W - Up, A - left, S - down, D - right): ";
    cin >> moving;

    switch (tolower(moving)) {
    case 'w':
        if (playerRows > 1 && maze[playerRows - 1][playerColumns] != WALL) playerRows--;
        break;
    case 'a':
        if (playerColumns > 1 && maze[playerRows][playerColumns - 1] != WALL) playerColumns--;
        break;
    case 's':
        if (playerRows < rows - 1 && maze[playerRows + 1][playerColumns] != WALL) playerRows++;
        break;
    case 'd':
        if (playerColumns < columns - 1 && maze[playerRows][playerColumns + 1] != WALL) playerColumns++;
        break;
    default:
        cout << "Invalid move! Please try again." << endl;
        break;
    }
}

int main() {
    char gamer = '@';
    int playerRows = 1, playerColumns = 1;
    pair<int, int> giftLocation; // Переменная для хранения координат подарка
    int rows = 25, columns = 50;

    vector<vector<int>> maze(rows, vector<int>(columns, WALL)); // Создаем лабиринт с заполненными стенами

    srand(time(nullptr));

    generateMaze(rows, columns, maze, giftLocation);

    bool foundGift = false;

    while (!foundGift)
    {
        player(playerRows, playerColumns, rows, columns, gamer, maze, giftLocation);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (i == playerRows && j == playerColumns)
                {
                    cout << gamer;
                }
                else if (i == giftLocation.first && j == giftLocation.second)
                {
                    cout << "$";
                }
                else if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1)
                {
                    cout << "#";
                }
                else if (maze[i][j] == PATH)
                {
                    cout << " ";
                }
                else {
                    cout << "#";
                }
            }
            cout << endl;
        }

        cout << "Player position: (" << playerRows << ", " << playerColumns << ")" << endl;
        cout << "Gift position: (" << giftLocation.first << ", " << giftLocation.second << ")" << endl;

        if (playerRows == giftLocation.first && playerColumns == giftLocation.second)
        {
            cout << "Congratulations! You found a gift!" << endl;
            foundGift = true;
        }
    }

    just();
    return 0;
}
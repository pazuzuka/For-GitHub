#include<iostream>
using namespace std;

void generateLab(int, int);
void player(int&, int&, int, int, char);

int main()
{
	char gamer = '@';
	int playerRows = 1, playerColumns = 1;
	int rows = 25, columns = 50;

	generateLab(rows, columns);

	while (true)
	{
		player(playerRows, playerColumns, rows, columns, gamer);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (i == playerRows && j == playerColumns) {
					cout << gamer;
				}
				else if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
					cout << "#";
				}
				else {
					cout << " ";
				}
			}
			cout << endl;
		}
	}

	return 0;
}

void generateLab(int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1)
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

void player(int& playerRows, int& playerColumns, int rows, int columns, char gamer)
{
	char moving;
	cout << "Enter a move(W - Up, A - left, S - down, D - right): ";
	cin >> moving;

	switch (tolower(moving)) {
	case 'w':
		if (playerRows > 1) playerRows--;
		break;
	case 'a':
		if (playerColumns > 1) playerColumns--;
		break;
	case 's':
		if (playerRows < rows - 2) playerRows++;
		break;
	case 'd':
		if (playerColumns < columns - 2) playerColumns++;
		break;
	default:
		cout << "Invalid move! Please try again." << endl;
		break;
	}
}
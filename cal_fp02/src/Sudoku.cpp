/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte?do inicial.
 * Lan?a excep??o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n?meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte?do actual (s? para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j? est? completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}





/**
 * Resolve o Sudoku.
 * Retorna indica??o de sucesso ou insucesso (sudoku imposs?vel).
 */
bool Sudoku::solve()
{
	vector<int> lowest_solution(10);
	int multiplicity = 1;
	int x = -1, y = -1;
	while (!this->isComplete()){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                vector<int> newest_solution = this->possibleNumbers(i, j);
                if(newest_solution.size() < lowest_solution.size() && !newest_solution.empty()){
                    lowest_solution = newest_solution;
                    x = i;
                    y = j;
                }
            }
        }

        if(x == -1 && y == -1)
            return false;
        this->numbers[x][y] = lowest_solution[0];
        this->countFilled++;
        multiplicity*=lowest_solution.size();
        this->columnHasNumber[x][lowest_solution[0]] = true;
        this->lineHasNumber[y][lowest_solution[0]] = true;
        this->block3x3HasNumber[x/3][y/3][lowest_solution[0] - 1] = true;
        lowest_solution.clear();
    }
	cout << "The multiplicity is "  << multiplicity << endl;
	return this->isComplete();
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++){
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}



vector<int> Sudoku::possibleNumbers(int x, int y) {
	vector<int> possibleSols;
	for(int i = 1; i <= 9; i++ ){
		if(isNumberPossible(x, y, i))
			possibleSols.push_back(i);
	}
    return possibleSols;
}

bool Sudoku::isNumberPossible(int x, int y, int num) {
	return (this->columnHasNumber[x][num] || this->lineHasNumber[y][num] || this->block3x3HasNumber[x/3][y/3][num]);
}

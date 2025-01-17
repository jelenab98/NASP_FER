#include "stdafx.h"
#include<algorithm>
#include<string>
#include<iostream>
#include<stack>
#include<set>
#include<vector>
#include<fstream>

using namespace std;

typedef pair<unsigned int, unsigned int> Pair;

bool isValid(int row, int col, int maxRow, int maxCol)
{
	return (row >= 0) && (row < maxRow) &&
		(col >= 0) && (col < maxCol);
}

unsigned int solve(const unsigned int N, const unsigned int M, uint16_t *const problem, vector<pair<unsigned int, unsigned int>> &solution)
{

	unsigned int* cost = (unsigned int*) malloc(N * M * sizeof(unsigned int));
	int i, j;

	stack<Pair> path;
	path.push(make_pair(N - 1, M - 1));
	unsigned int finalCost = problem[(N - 1)*M + M - 1];

	for (i = 0; i<N; i++)
	{
		for (j = 0; j<M; j++)
		{
			cost[i*M + j] = 0;
		}
	}

	*(cost) = problem[0];
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if (isValid(i + 1, j, N, M) == true) {
				if (*(cost + (i + 1)*M + j) == 0) {
					*(cost + (i + 1)*M + j) = *(cost + i * M + j) + problem[(i + 1) * M + j];
				}
				else {
					*(cost + (i + 1)*M + j) = min(*(cost + i * M + j) + problem[(i + 1) * M + j], *(cost + (i + 1)*M + j));
				}
			}
			if (isValid(i, j + 1, N, M) == true) {
				if (*(cost + i*M + j + 1) == 0) {
					*(cost + i*M + j + 1) = *(cost + i * M + j) + problem[i* M + j + 1];
				}
				else {
					*(cost + i*M + j + 1) = min(*(cost + i * M + j) + problem[i * M + j + 1], *(cost + i*M + j + 1));
				}
			}
		}
	
	}

	i = N - 1;
	j = M - 1;

	while (i >= 0 && j >= 0) {
		if (isValid(i-1, j ,N, M) == true && isValid(i, j-1, N, M) == true) {
			unsigned int cost1 = *(cost + (i - 1)*M + j);
			unsigned int cost2 = *(cost + i * M + j - 1);
			if (cost1 < cost2) {
				path.push(make_pair(i - 1, j));
				finalCost += problem[(i - 1)*M + j];
				i = i - 1;
			}
			else {
				path.push(make_pair(i, j - 1));
				finalCost += problem[i*M + j - 1];
				j = j - 1;
			}
		}
		else if (isValid(i - 1, j, N, M) == true) {
			path.push(make_pair(i - 1, j));
			finalCost += problem[(i - 1)*M + j];
			i = i - 1;
		}
		else if (isValid(i, j - 1, N, M) == true) {
			path.push(make_pair(i, j - 1));
			finalCost += problem[i*M + j - 1];
			j = j - 1;
		}
		if (i == 0 && j == 0) {
			break;
		}
	}
	free(cost);

	while (!path.empty())
	{
		pair<unsigned int, unsigned int> p = path.top();
		path.pop();
		solution.push_back(make_pair(p.first, p.second));
	}

	return finalCost;
}

int main() {

	uint16_t polje[] = {1, 7, 9, 2, 8, 6, 6, 7, 1, 3, 2, 8};
	uint16_t *ptr;
	ptr = p;
	vector<pair<unsigned int, unsigned int>> solution;

	unsigned int costNumber = solve(3, 4, ptr, solution);

	cout << "Cost: " << costNumber;
	cout << "\n";
	
	for (int i = 0; i<solution.size(); ++i) {
		cout << "(" << solution[i].first << ", " << solution[i].second << ")" << endl;
	}
	
	return 0;
}



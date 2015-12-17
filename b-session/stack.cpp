#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

char adj[51][51];
int nBracket[51][51][51];
int nBalanced[51][51][51];
int nValid[51][51];

bool isPushPopPair(char a, char b) {
	if (a < 'A' || a > 'Z') {
		return false;
	}

	if (b < 'a' || b > 'z') {
		return false;
	}

	if ((a - 'A' + 'a') == b) {
		return true;
	}

	return false;
}

int main() {
	FILE* inputFile = fopen("stackin.txt", "r");

	int N, R, K;
	fscanf(inputFile, "%d %d %d", &N, &R, &K);

	int lastFrom = 0;

	for (int i = 0; i < R; i++) {
		int from, to;

		if (lastFrom > 0) {
			fscanf(inputFile, "%d", &to);
			from = lastFrom;
			lastFrom = 0;
		} else {
			fscanf(inputFile, "%d %d", &from, &to);
		}

		char action = '-';
		fscanf(inputFile, " %c", &action);

		if (action >= '0' && action <= '9') {
			lastFrom = action - '0';
			action = '-';
		}

		adj[from][to] = action;
		adj[to][from] = action;
	}

	for (int a = 1; a <= N; a++) {
		nBalanced[a][a][0] = 1;
	}

	for (int k = 1; k <= K; k++) {
		for (int a = 1; a <= N; a++) {
			for (int b = 1; b <= N; b++) {
				if (k < 2) {
					nBracket[a][b][k] = 0;
				} else {
					for (int c = 1; c <= N; c++) {
						for (int d = 1; d <= N; d++) {
							if (isPushPopPair(adj[c][d], adj[b][d])) {
								nBracket[a][b][k] += nBalanced[c][d][k-2];
							}
						}
					}
				}
			}
		}

		for (int a = 1; a <= N; a++) {
			for (int b = 1; b <= N; b++) {
				for (int c = 1; c <= N; c++) {
					if (adj[a][c] == '-') {
						nBalanced[a][b][k] += nBalanced[c][b][k - 1];
					}
				}
				for (int j = 2; j <= k; j++) {
					for (int c = 1; c <= N; c++) {
						nBalanced[a][b][k] += nBracket[a][c][j] * nBalanced[c][b][k-j];
					}
				}
			}
		}

		for (int a = 1; a <= N; a++) {
			nValid[a][k] += nBalanced[a][N][k];
			for (int j = 0; j <= k - 1; j++) {
				for (int c = 1; c <= N; c++) {
					for (int d = 1; d <= N; d++) {
						if (adj[c][d] >= 'A' && adj[c][d] <= 'Z') {
							// cout << nBalanced[a][c][j] << ":" << nValid[d][k-1-j] << endl;
							nValid[a][k] += nBalanced[a][c][j] * nValid[d][k-1-j];
							if (a == 1 && k == 5 && nBalanced[a][c][j] > 0 && nValid[d][k-1-j] > 0) {
								cout << "balanced from " << a << ":" << c << endl;
								cout << "valid from " << d << ":" << N << endl;
								cout << "balance: " << nBalanced[a][c][j] << endl;
								cout << "valid: " << nValid[d][k-1-j] << endl;
							}
						}
					}
				}
			}
		}
	}

	int total = 0;
	for (int k = 1; k <= K; k++) {
		total += nValid[1][k];
	}

	cout << "answer: " << total << endl;
}
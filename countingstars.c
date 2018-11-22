#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(char grid[][100], int visited[][100], int numbers[][100], int x, int y, int id, int maxX, int maxY, char type) {
	if(x < 0 || x >= maxX || y < 0 || y >= maxY) {
		return;
	} else if (grid[x][y] != type || visited[x][y]) {
		return;
	} else {
		numbers[x][y] = id;
		visited[x][y] = 1;

		dfs(grid, visited, numbers, x - 1, y, id, maxX, maxY, type);
		dfs(grid, visited, numbers, x + 1, y, id, maxX, maxY, type);
		dfs(grid, visited, numbers, x, y - 1, id, maxX, maxY, type);
		dfs(grid, visited, numbers, x, y + 1, id, maxX, maxY, type);
	}
}

int main() {
	int m, n, id, count = 0;

	while (scanf("%d %d", &m, &n) > 0) {
		id = 0;
		count++;
		char grid[100][100];
		int visited[100][100] = {{0}};
		int numbers[100][100];

		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				if(scanf(" %c", &grid[i][j]) == 1)
					continue;
			}
		}

		for (int i = 0; i < m; i++)
			for(int j = 0; j < n; j++) {
				if (!visited[i][j])
					if (grid[i][j] == '-') {
						dfs(grid, visited, numbers, i, j, ++id, m, n, grid[i][j]);
					} else {
						visited[i][j] = 1;
					}
			}


		printf("Case %d: %d\n", count, id);
	}

	return 0;
}

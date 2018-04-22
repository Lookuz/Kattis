import java.util.*;

public class TenKindsOfPeople {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int row = scanner.nextInt();
		int col = scanner.nextInt();
		int[][] grid = new int[row][col];

		for(int i = 0; i < row; i++) {
			String nextLine = scanner.next();
			for(int j = 0; j < col; j++) {
				int next = Character.getNumericValue(nextLine.charAt(j));
				grid[i][j] = next;
			}
		}

		int[][] sameCluster = new int[row][col];
		boolean[][]visited = new boolean[row][col];
		int count = 0;

		for(int i = 0; i < row; i++)
			for(int j = 0; j < col; j++) {
				if(!visited[i][j]) {
					checkClusterDFS(grid, sameCluster, visited,
							i, j, row, col, grid[i][j], count++);
				}
			}

		int numQueries = scanner.nextInt();
		for(int i =0; i < numQueries; i++) {
			int firstx = scanner.nextInt();
			int firsty = scanner.nextInt();
			int secondx = scanner.nextInt();
			int secondy = scanner.nextInt();

			if(sameCluster[firstx - 1][firsty - 1] == sameCluster[secondx - 1][secondy - 1]) {
				if(grid[firstx - 1][firsty - 1] == 1)
					System.out.println("decimal");
				else
					System.out.println("binary");
			} else {
				System.out.println("neither");
			}
		}
	}
	private static void checkClusterDFS(int[][] grid, int[][] cluster, boolean[][]visited,
			int row, int col, int maxR, int maxC, int type, int count) {
		if(row < 0 || col < 0|| row >= maxR || col >= maxC)
			return;

		if(grid[row][col] != type)
			return;

		if(visited[row][col])
			return;

		visited[row][col] = true;
		cluster[row][col] = count;
		checkClusterDFS(grid, cluster, visited, row - 1, col, maxR, maxC, type, count);
		checkClusterDFS(grid, cluster, visited, row + 1, col, maxR, maxC, type, count);
		checkClusterDFS(grid, cluster, visited, row, col - 1, maxR, maxC, type, count);
		checkClusterDFS(grid, cluster, visited, row, col + 1, maxR, maxC, type, count);
	}
}

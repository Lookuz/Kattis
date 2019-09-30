import java.util.*;

public class conformity {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		List<Integer> line;
		String frosh;
		int currMax = 0, total = 0;
		HashMap<String, Integer> map = new HashMap<>();

		for (int i = 0; i < n; i++) { 
			line = new ArrayList<>();
			for (int j = 0; j < 5; j++) {
				line.add(sc.nextInt());
			}
			Collections.sort(line);
			frosh = "";
			for (Integer number : line) {
				frosh += Integer.toString(number);
			}

			if (map.containsKey(frosh)) {
				map.put(frosh, map.get(frosh) + 1);
			} else {
				map.put(frosh, 1);
			}

			if (map.get(frosh) > currMax) {
				currMax = map.get(frosh);
			}
		}

		for (Map.Entry<String, Integer> entry : map.entrySet()) {
			if (entry.getValue() == currMax) {
				total += entry.getValue();
			}
		}

		System.out.println(total);
		
	}
}
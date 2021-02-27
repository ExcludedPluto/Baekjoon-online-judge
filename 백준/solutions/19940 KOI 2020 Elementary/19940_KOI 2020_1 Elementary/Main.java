
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		OvenTimer test = new OvenTimer();
		int[][] minTimeSet = test.getMinTimeSet();
		for(int[] row : minTimeSet) {
			for(int time : row)
				System.out.print(time + " ");
			System.out.println();
		}
	}

}

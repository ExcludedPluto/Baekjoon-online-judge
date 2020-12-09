
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Hibe test = new Hibe();
		int[][] hibe = test.getHibeAfterDays2();
		for(int[] line : hibe) {
			for(int i : line)
				System.out.print(i + " ");
			System.out.println();
		}
	}

}

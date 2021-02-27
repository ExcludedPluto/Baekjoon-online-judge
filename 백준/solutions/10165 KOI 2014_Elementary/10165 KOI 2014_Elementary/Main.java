
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BusLine test = new BusLine();
		int[] temp = test.deleteDuplicateLine();
		for(int i : temp)
			System.out.print(i + " ");
	}

}

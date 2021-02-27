
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BeltSystem test = new BeltSystem();
		long []lastBeltState = test.getLastBeltStates();
		
		for(int i = 0; i<2; i++)
			System.out.print(lastBeltState[i] + " ");
	}

}

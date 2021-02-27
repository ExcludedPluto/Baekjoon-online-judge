
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		CardGame test = new CardGame();
		String[] records = test.getRecordForGame();
		
		for(int i = 0; i<records.length; i++)
			System.out.println(records[i]);
	}

}


public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PalindromeFinder test = new PalindromeFinder();
		int[] isPalindrome = test.returnPalidromeRecords();
		for(int i : isPalindrome) 
			System.out.println(i);
	}

}

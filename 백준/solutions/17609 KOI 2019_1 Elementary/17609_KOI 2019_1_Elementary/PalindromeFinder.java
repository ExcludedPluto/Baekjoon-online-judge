
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PalindromeFinder {
	private String[] str;
	
	public PalindromeFinder() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int numOfStr = 0;
		try {
			numOfStr = Integer.parseInt(br.readLine());
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		str = new String[numOfStr];
		try {
			for(int i = 0; i<str.length; i++)
				str[i] = br.readLine();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	
	public int[] returnPalidromeRecords() {
		int[] palindromeRecord = new int[str.length];
		
		for(int i = 0; i<str.length; i++) {
			palindromeRecord[i] = isPalindrome(str[i], 0);
		}
		
		return palindromeRecord;
	}
	
	
	private int isPalindrome(String str, int deep) {
		char[] charArray = str.toCharArray();
		int maxIndexForLoop = charArray.length / 2;
		int maxIndex = charArray.length-1;
		
		int howManyDifferent = 0;
		for(int i = 0; i<maxIndexForLoop;i++) {
			if(charArray[i] == charArray[maxIndex]) {
				maxIndex--;
			}
			else {
				if(deep >= 1)
					return 2;
				
				howManyDifferent = 1;
				
				int front = isPalindrome(str.substring(i+1, maxIndex+1), deep+1);
				int rear = isPalindrome(str.substring(i, maxIndex), deep+1);
				
				howManyDifferent += front > rear ? rear : front;
				break;
			}
		}
			
		
		if(howManyDifferent <= 1)
			return howManyDifferent;
		else 
			return 2;
	}
}

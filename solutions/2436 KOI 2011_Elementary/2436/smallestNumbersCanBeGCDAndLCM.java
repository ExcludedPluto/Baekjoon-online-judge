
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class smallestNumbersCanBeGCDAndLCM {
	int GCD;
	int LCM;
	int []smallestNumbers = new int[2];
	int []candidates = new int[3000];
	int lengthOfCandidate = 0;
	
	public smallestNumbersCanBeGCDAndLCM()  {
		try {
			getGCDandLCM();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		for(int i = 0; i<3000; i++)
			candidates[i] = 0;
		smallestNumbers[0] = 0;
		smallestNumbers[1] = 0;
		
	}
	private void getGCDandLCM()  throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String []str = new String[2];
		str = br.readLine().split(" ");
		GCD = Integer.parseInt(str[0]);
		LCM = Integer.parseInt(str[1]);
	}
	public void printSmallestNumbers() {
		findSmallestNumbers();
		System.out.println(smallestNumbers[0] + " " + smallestNumbers[1]);
	}
	private void findSmallestNumbers() {
		//후보 : gcd의 배수이며, lcm을 나눌 수 있는 수. 이때, 후보들은 gcd이상, lcm의 반이하 이다.
		//후보를 모두 구한 후, 최대공약수, 최소공배수 구하는 공식으로 gcd, lcm이 맞는지 확인 후 smallestNumber에 추가.
		findCandidate(); //clear
		findSmallestNumbersForGCDandLCM();
	}
	private void findCandidate() {
		int halfLCM = LCM/2 + 1;
		int index = 0;
		if(GCD == LCM) {
			candidates[0] = GCD;
			candidates[1] = GCD;
			this.lengthOfCandidate = 2;
			return;
		}
		for(int i = GCD; i<=halfLCM; i += GCD) {
			if(LCM % i == 0) {
				candidates[index++] = i;
			}
		}
		if(LCM % GCD == 0)
			candidates[index++] = LCM;
		this.lengthOfCandidate = index;
	}
	private void findSmallestNumbersForGCDandLCM() {
		for(int i = 0; i<this.lengthOfCandidate-1; i++) {
			for(int j = i+1; j<this.lengthOfCandidate; j++) {
				if(isGCDandLCM(candidates[i], candidates[j])) {
					this.smallestNumbers[0] = candidates[i];
					this.smallestNumbers[1] = candidates[j];
					break;
				}
			}
		}
	}
	private boolean isGCDandLCM(int first, int second) {
		int tempGCD = 1;
		int tempLCM = 1;
		int tempFirst = first;
		int tempSecond = second;
		boolean flag = true;
		
		while(flag) {
			if(tempFirst == 1)
				flag = false;
			for(int divideBy = 2; divideBy<=tempFirst; divideBy++) {
				if(tempFirst % divideBy == 0 && tempSecond % divideBy == 0) {
					tempGCD *= divideBy;
					tempFirst /= divideBy;
					tempSecond /= divideBy;
					break;
				}
				else if(divideBy == tempFirst)
					flag = false;
			}
		}
		
		tempLCM = tempGCD*tempFirst*tempSecond;
		
		if(tempGCD == this.GCD && tempLCM == this.LCM)
			return true;
		else
			return false;
	}
}

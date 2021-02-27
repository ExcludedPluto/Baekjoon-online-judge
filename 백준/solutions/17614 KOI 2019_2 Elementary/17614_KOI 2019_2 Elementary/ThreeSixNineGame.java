
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ThreeSixNineGame {
	private int lastNumber;
	
	public ThreeSixNineGame() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			this.lastNumber = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public int getClappingNum(int lastNumber) {
		
		int countClapping = ((lastNumber/10)*3) + ((lastNumber % 10)/3);	//첫번째 자리에 3 6 9가 나온 만큼 더함
		
		if(lastNumber >= 10) {	//두번째 자리에 3 6 9가 나온만큼 더함
			int num = ((lastNumber/100)*3) +  ((lastNumber % 100) / 30);
			int restNum = (lastNumber % 100) % 30;
			countClapping += (num*10);
			if(restNum < 10) {
				countClapping -= (9-restNum);
			}
		}
		if(lastNumber >= 100) {
			int num = ((lastNumber/1000)*3) + ((lastNumber % 1000) / 300);
			int restNum = (lastNumber % 1000) % 300;
			countClapping += (num*100);
			if(restNum < 100) {
				countClapping -= (99-restNum);
			}
		}
		if(lastNumber >= 1000) {
			int num = ((lastNumber/10000)*3) + ((lastNumber % 10000) / 3000);
			int restNum = (lastNumber % 10000) % 3000;
			countClapping += (num*1000);
			if(restNum < 1000) {
				countClapping -= (999-restNum);
			}
		}
		if(lastNumber >= 10000) {
			int num = ((lastNumber/100000)*3) + ((lastNumber % 100000) / 30000);
			int restNum = (lastNumber % 100000) % 30000;
			countClapping += (num*10000);
			if(restNum < 10000) {
				countClapping -= (9999-restNum);
			}
		}
		if(lastNumber >= 100000) {
			int num = ((lastNumber/1000000)*3) + (lastNumber % 1000000) / 300000;
			int restNum = (lastNumber % 1000000) % 300000;
			countClapping += (num*100000);
			if(restNum < 100000) {
				countClapping -= (99999-restNum);
			}
		} /*
int countClapping = 0;
		
		for(int i = 0; i<=this.lastNumber; i++) {
			int one = i % 10;
			int ten = i % 100 - one;
			int hund = i % 1000 - (i%100);
			int thou = i % 10000 - (i%1000);
			int tenThou = i % 100000 - (i%10000);
			int hundThou = i% 1000000 - (i%100000);
			
			if(one == 3 || one == 6 || one == 9)
				countClapping++;
			if(ten == 30 || ten == 60 || ten == 90)
				countClapping++;
			if(hund == 300 || hund == 600 || hund == 900)
				countClapping++;
			if(thou == 3000 || thou == 6000 || thou == 9000)
				countClapping++;
			if(tenThou == 30000 || tenThou == 60000 || tenThou == 90000)
				countClapping++;
			if(hundThou == 300000 || hundThou == 600000 || hundThou == 900000)
				countClapping++;
		}*/
		return countClapping;
	}
	
	public int getClappingNum2(int lastNumber) {
		int countClapping = 0;
		
		for(int i = 0; i<=lastNumber; i++) {
			int one = i % 10;
			int ten = i % 100 - one;
			int hund = i % 1000 - (i%100);
			int thou = i % 10000 - (i%1000);
			int tenThou = i % 100000 - (i%10000);
			int hundThou = i% 1000000 - (i%100000);
			
			if(one == 3 || one == 6 || one == 9)
				countClapping++;
			if(ten == 30 || ten == 60 || ten == 90)
				countClapping++;
			if(hund == 300 || hund == 600 || hund == 900)
				countClapping++;
			if(thou == 3000 || thou == 6000 || thou == 9000)
				countClapping++;
			if(tenThou == 30000 || tenThou == 60000 || tenThou == 90000)
				countClapping++;
			if(hundThou == 300000 || hundThou == 600000 || hundThou == 900000)
				countClapping++;
		}
		return countClapping;
	
	}
}

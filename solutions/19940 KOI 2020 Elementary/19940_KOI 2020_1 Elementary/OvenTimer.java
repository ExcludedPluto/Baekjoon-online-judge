
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class OvenTimer {
	private int[] testCase;
	
	public OvenTimer() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfTestCase = 0;
		try {
			numOfTestCase =Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		testCase = new int[numOfTestCase];
		try {
			for(int i = 0; i<numOfTestCase; i++) {
				testCase[i] = Integer.parseInt(br.readLine());
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public int[][] getMinTimeSet() {
		int[][] minTimeSet = new int[testCase.length][5];
		
		for(int i = 0; i < this.testCase.length; i++)
			minTimeSet[i] = makeTimeSet(this.testCase[i]);
		
		return minTimeSet;
	}
	
	private int[] makeTimeSet(int minute) {
		int[] timeSet = new int[5];
		for(int i = 0; i<5; i++)
			timeSet[i] = 0;
		
		timeSet[0] = minute / 60;
		int restMinute = minute % 60;
		
		if(restMinute <=35) {
			timeSet[1] = restMinute / 10;
			int restOneMinutes = restMinute % 10;
			
			if(restOneMinutes <= 5)
				timeSet[3] = restOneMinutes;
			else {
				timeSet[1] += 1;
				timeSet[4] = 10 - restOneMinutes;
			}
		}
		else {
			timeSet[0] += 1;
			timeSet[2] = (64 - restMinute) / 10;
			int restOneMinutes = (restMinute - 60) + timeSet[2]*10;
			
			if(restOneMinutes < 0)
				timeSet[4] = (-1)*restOneMinutes;
			else 
				timeSet[3] = restOneMinutes;
		}
		return timeSet;
	}
	
	
}

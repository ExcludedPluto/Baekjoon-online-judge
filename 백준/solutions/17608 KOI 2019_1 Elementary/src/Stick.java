
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Stick {
	private int[] sticks;
	
	public Stick() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfStick = 0;
		try {
			numOfStick = Integer.parseInt(br.readLine());
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		sticks = new int[numOfStick];
		try {
			for(int i = 0; i<sticks.length; i++)
				sticks[i] = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public int getNumOfStickCanSeeFromRight() {
		int []tempStick = sticks;
		
		int tempMax = tempStick[tempStick.length-1];
		for(int i = tempStick.length-2; i>=0; i--) {
			if(tempStick[i] <= tempMax)
				tempStick[i] = 0;
			else
				tempMax = tempStick[i];
		}
		
		int numOfStickCanSee = 0;
		
		for(int i = 0; i<tempStick.length; i++)
			if(tempStick[i] != 0)
				numOfStickCanSee++;
		
		return numOfStickCanSee;
	}

}

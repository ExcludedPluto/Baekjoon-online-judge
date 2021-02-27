
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BeltSystem {
	private int [][]beltProperties;
	
	public BeltSystem() {
		try {
			getProperties();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	private void getProperties() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfBelt = Integer.parseInt(br.readLine());
		
		beltProperties = new int[numOfBelt][3];
		for(int i = 0; i<beltProperties.length; i++) {
			String []str = new String[3];
			str = br.readLine().split(" ");
			
			beltProperties[i][0] = Integer.parseInt(str[0]);
			beltProperties[i][1] = Integer.parseInt(str[1]);
			beltProperties[i][2] = Integer.parseInt(str[2]);
 		}
		
	}
	
	public long[] getLastBeltStates() {
		long[] lastBeltState = new long[2];
		lastBeltState[0] = 0;
		lastBeltState[1] = 1;
		
		for(int i = 0; i<beltProperties.length; i++) {
			if(beltProperties[i][2] == 1)
				lastBeltState[0] = lastBeltState[0] == 1 ? 0 : 1;
			
			lastBeltState[1] = ((lastBeltState[1] * beltProperties[i][1]) / beltProperties[i][0]);
		}
		
		return lastBeltState;
	}
}

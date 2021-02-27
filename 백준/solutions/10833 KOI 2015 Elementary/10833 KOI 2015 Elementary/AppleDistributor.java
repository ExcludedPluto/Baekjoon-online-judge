
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class AppleDistributor {
	private int []applesForEachSchool;
	private int []studentsEachSchool;
	
	public AppleDistributor() {
		try {
			getProperties();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void getProperties() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfSchool = Integer.parseInt(br.readLine());
		
		applesForEachSchool = new int[numOfSchool];
		studentsEachSchool = new int[numOfSchool];
		
		for(int i = 0; i<numOfSchool; i++) {
			String []str = new String[2];
			str = br.readLine().split(" ");
			
			studentsEachSchool[i] = Integer.parseInt(str[0]);
			applesForEachSchool[i] = Integer.parseInt(str[1]);
		}
	}
	
	public int getLeftApple() {
		int []applesLeft = new int[applesForEachSchool.length];
		
		for(int i = 0; i<applesLeft.length; i++) {
			applesLeft[i] = applesForEachSchool[i] % studentsEachSchool[i];
		}
		
		int appleCount = 0;
		for(int i = 0; i<applesLeft.length; i++) 
			appleCount += applesLeft[i];
		
		return appleCount;
	}
}

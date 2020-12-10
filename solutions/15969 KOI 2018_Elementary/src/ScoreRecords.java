
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ScoreRecords {
	private int[] scoreRecords;

	public ScoreRecords() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfScoreRecord = 0;
		try {
			numOfScoreRecord = Integer.parseInt(br.readLine());
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		scoreRecords = new int[numOfScoreRecord];
		try {
			String []str = br.readLine().split(" ");
			for(int i = 0; i<numOfScoreRecord; i++) {
				scoreRecords[i] = Integer.parseInt(str[i]);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public int differentOfHighestAndLowest() {
		int max = 0;
		int min = 2000000;
		
		for(int i : scoreRecords) {
			max = i > max ? i : max;
			min = i < min ? i : min;
		}
		
		return max - min;
	}
}

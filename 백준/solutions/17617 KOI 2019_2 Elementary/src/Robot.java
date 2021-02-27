
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Robot {
	private int[] robot;
	private int range;
	private int maxCircleNum;
	
	public Robot() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfRobot = 0;
		try {
			numOfRobot = Integer.parseInt(br.readLine());
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		robot = new int[numOfRobot];
		try {
			String[] str = br.readLine().split(" ");
			range = Integer.parseInt(str[0]);
			maxCircleNum = Integer.parseInt(str[1]);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		try {
			String[] str = br.readLine().split(" ");
			for(int i = 0; i < this.robot.length; i++)
				robot[i] = Integer.parseInt(str[i]);
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	
	public int getMinDistanceToCoverCircle() {
		int minDistanceToCoverCircle = 0;
		
		return minDistanceToCoverCircle;
	}
}

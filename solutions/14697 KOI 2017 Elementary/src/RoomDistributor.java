
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class RoomDistributor {
	private int capacityOfA;
	private int capacityOfB;
	private int capacityOfC;
	private int numOfStudents;
	
	public RoomDistributor() {
		try {
			getProperties();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void getProperties() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String []str = br.readLine().split(" ");
		this.capacityOfA = Integer.parseInt(str[0]);
		this.capacityOfB = Integer.parseInt(str[1]);
		this.capacityOfC = Integer.parseInt(str[2]);
		this.numOfStudents = Integer.parseInt(str[3]);
	}
	
	public boolean canDistributeWithoutBlankBed() {
		boolean isPossible = false;
		
		int maxA = this.numOfStudents / this.capacityOfA;
		int maxB = this.numOfStudents / this.capacityOfB;
		int maxC = this.numOfStudents / this.capacityOfC;
		
		for(int a = 0; a<= maxA; a++) {
			for(int b = 0; b <= maxB; b++) {
				for(int c = 0; c <=maxC; c++) {
					if(isZeroStudent(a, b, c)) {
						isPossible = true;
						return isPossible;
					}
				}
			}
		}
		return isPossible;
	}
	
	private boolean isZeroStudent(int a, int b, int c) {
		int tempA = a*this.capacityOfA;
		int tempB = b*this.capacityOfB;
		int tempC = c*this.capacityOfC;
		
		if((this.numOfStudents - tempA - tempB - tempC) == 0)
			return true;
		else
			return false;
		
	}

}

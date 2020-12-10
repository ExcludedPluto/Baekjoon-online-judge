
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class BallLine {
	private int[] balls;	//red == 0, blue == 1
	
	public BallLine() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfBall = 0;
		try {
			numOfBall = Integer.parseInt(br.readLine());
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		balls = new int[numOfBall];
		try {
			char[] cha = br.readLine().toCharArray();
			for(int i = 0; i<balls.length; i++) {
				if(cha[i] == 'R')
					balls[i] = 0;
				else
					balls[i] = 1;
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	
	/*�� ���� ���� ������ ��
	 *���� ������ ���� ������ �� -> �������� ���� � �ִ°�, �Ķ����� ���� ��ִ°�. -> �̶� ���� �������� ���� ������.
	 *���� ��, ���� ��, ������ ��, ������ �ĸ� ���ϰ�, �� ������ �´� ���� �� �������� �� ������ ��.
	 *���� ���� ���� ���� �� �ּ� �̵�Ƚ��.
	 */
	public int getMinMove() {
		int minMove = 0;
		
		int countRed = 0;
		int countBlue = 0;
		for(int i : balls)
			if(i == 0)
				countRed++;
			else
				countBlue++;
		
		int leftRed = 0;
		int leftBlue = 0; 
		int rightRed = 0;
		int rightBlue = 0;
		for(int i : balls) {
			if(i != balls[0])
				break;
			
			if(i == 0)
				leftRed++;
			else
				leftBlue++;
		}
		
		for(int i = balls.length -1; i>=0; i--) {
			if(balls[i] != balls[balls.length -1])
				break;
			
			if(balls[i] == 0)
				rightRed++;
			else
				rightBlue++;
		}
		int restLeftRed = countRed - leftRed;
		int restLeftBlue = countBlue - leftBlue;
		int restRightRed = countRed - rightRed;
		int restRightBlue = countBlue - rightBlue;
		
		minMove = min(min(restLeftRed, restLeftBlue), min(restRightRed, restRightBlue));
		return minMove;
	}
	
	private int min(int a, int b) {
		return a < b ? a : b;
	}
	
}

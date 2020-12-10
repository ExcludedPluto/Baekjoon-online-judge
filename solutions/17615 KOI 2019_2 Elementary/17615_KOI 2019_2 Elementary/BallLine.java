
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
	
	
	/*두 개의 공의 개수를 셈
	 *끝에 분포된 공의 개수를 셈 -> 빨간색이 끝에 몇개 있는가, 파란색이 끝에 몇개있는가. -> 이때 왼쪽 오른쪽을 따로 세야함.
	 *왼쪽 빨, 왼쪽 파, 오른쪽 빨, 오른쪽 파를 구하고, 각 색깔의 맞는 공의 총 개수에서 그 수들을 뺌.
	 *남은 수가 가장 적은 게 최소 이동횟수.
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

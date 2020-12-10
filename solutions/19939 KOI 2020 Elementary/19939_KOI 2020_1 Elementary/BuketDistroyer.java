
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class BuketDistroyer {
	private int numOfBall;
	private int numOfBuket;
	
	public BuketDistroyer() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			String[] str = br.readLine().split(" ");
			this.numOfBall = Integer.parseInt(str[0]);
			this.numOfBuket = Integer.parseInt(str[1]);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	//그냥 바구니에 들어간 공의 개수가 가능한 1씩만 차이나면 됨.
	//따라서 n(n+1)/2 공식을 써서, 1에서 시작했을때, 몇개가 필요한지 계산
	//그 최소 공의 개수를 전체 공의 개수에서 빼고 나온 수를, 버켓으로 나누어 몫과 나머지를 구함
	//나머지가 0이면, 1 + 몫이 최소, 버켓개수+ 몫이 최대 -> 즉, 버켓 개수 - 1이 반환값이 된다.
	//0이 아니면, 최소는 1+ 몫으로 둠. 최대는 위에서부터 1씩 증가해나가면 필연적으로 최소 전에 다 끝나므로, 최대는 버켓개수 + 몫 + 1임 -> 즉, 차이는 버켓개수
	public int getMinDiffrenceBetweenMaxAndMinBuket() {
		if(!isPossibleToSplit())
			return -1;
		
		int minBall = getSumOfIncreasingOne(numOfBuket);
		int restBall = this.numOfBall - minBall;
		int restBallAfterDistribution = restBall % this.numOfBuket;
		
		if(restBallAfterDistribution == 0)
			return this.numOfBuket -1;
		else
			return this.numOfBuket;
	}
	
	private boolean isPossibleToSplit() {
		int minBall = getSumOfIncreasingOne(numOfBuket);
		if(this.numOfBall >= minBall)
			return true;
		else
			return false;
	}
	
	private int getSumOfIncreasingOne(int end) {
		return (end*(end+1))/2;
	}
	
}

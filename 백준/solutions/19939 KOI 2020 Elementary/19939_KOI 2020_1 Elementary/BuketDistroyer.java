
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
	
	//�׳� �ٱ��Ͽ� �� ���� ������ ������ 1���� ���̳��� ��.
	//���� n(n+1)/2 ������ �Ἥ, 1���� ����������, ��� �ʿ����� ���
	//�� �ּ� ���� ������ ��ü ���� �������� ���� ���� ����, �������� ������ ��� �������� ����
	//�������� 0�̸�, 1 + ���� �ּ�, ���ϰ���+ ���� �ִ� -> ��, ���� ���� - 1�� ��ȯ���� �ȴ�.
	//0�� �ƴϸ�, �ּҴ� 1+ ������ ��. �ִ�� ���������� 1�� �����س����� �ʿ������� �ּ� ���� �� �����Ƿ�, �ִ�� ���ϰ��� + �� + 1�� -> ��, ���̴� ���ϰ���
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

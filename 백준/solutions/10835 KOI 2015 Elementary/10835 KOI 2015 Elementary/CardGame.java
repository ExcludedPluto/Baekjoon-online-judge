
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CardGame {
	private int[] leftCard;
	private int[] rightCard;
	private int[][] maxScoreRecord;
	
	public CardGame() {
		getCard();
	}
	private void getCard() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfCard = 0;
		try {
			numOfCard = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		leftCard = new int[numOfCard];
		rightCard = new int[numOfCard];
		try {
			String[] left = br.readLine().split(" ");
			String[] right = br.readLine().split(" ");
			for(int i = 0; i<numOfCard; i++) {
				this.leftCard[i] = Integer.parseInt(left[i]);
				this.rightCard[i] = Integer.parseInt(right[i]);
			} 
		}catch(Exception e) {
			e.printStackTrace();
		}
		this.maxScoreRecord = new int[numOfCard+1][numOfCard+1];
		for(int i = 0; i<numOfCard+1; i++)
			for(int j = 0; j<numOfCard+1; j++)
				this.maxScoreRecord[i][j] = -1;
	}
	public int getMaxScore() {
		return calculateMaxScore(0,0);
	}
	
	//���� ī�庸�� ���� �ְų�, ���� ���� �־�� ������ �� �� ����. �� ���� ���� ���� ������ ����� ī�尡 �����߸� ������.
	//�� ������ ���� ���� ���� ��, ���ʺ��� ���� ���ڰ� �����ʿ� ������ �־�� �������� ������ �� ����.
	//�̷��� ������ �ִ��� ����.
	private int calculateMaxScore(int left, int right) {
		if(left >= this.leftCard.length || right >= this.rightCard.length)
			return this.maxScoreRecord[left][right] = 0;
		else if(this.maxScoreRecord[left][right] != -1)
			return this.maxScoreRecord[left][right];
		
		
		if(this.leftCard[left] > this.rightCard[right])
			return this.maxScoreRecord[left][right] = calculateMaxScore(left, right+1) + rightCard[right];
		else
			return this.maxScoreRecord[left][right] = max(calculateMaxScore(left + 1, right), calculateMaxScore(left+1, right + 1));
	}
	
	private int max(int a, int b) {
		return a > b ? a : b;
	}
}

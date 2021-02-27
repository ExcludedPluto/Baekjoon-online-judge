
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;

public class GradeGenerator {
	private int numOfStudent;
	private int myNum;
	private Answer[] answer;
	
	public GradeGenerator() {
		getProperties();
	}
	
	private class Answer {
		int higher;
		int lower;
		public Answer(int higher, int lower) {
			this.higher = higher;
			this.lower = lower;
		}
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfAnswer = 0;
		try {
			String[] str = br.readLine().split(" ");
			this.numOfStudent = Integer.parseInt(str[0]);
			numOfAnswer = Integer.parseInt(str[1]);
			this.myNum = Integer.parseInt(str[2]) -1;
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		answer = new Answer[numOfAnswer];
		try {
			for(int i = 0; i<numOfAnswer; i++) {
				String[] str = br.readLine().split(" ");
				answer[i] = new Answer(Integer.parseInt(str[0]) - 1, Integer.parseInt(str[1]) -1);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	//�� �л��� �ڽź��� �Ʒ�, �ڽź��� ���� �ִ� �л��� ����� �迭�� ����.
 	//ã�� ��ȣ�� �л����� �����Ͽ� DFS�� �� ������ count�� �ϳ��� �÷���.
	//�׷��� �ڱ� ��, �Ʒ��� ����ִ��� Ȯ����. 1 + �ڱ� �� ��� / NumOfStudent - �ڱ� �Ʒ� ���
	public int[] calculateAndReturnMaxAndMinGrade() {
		int[] maxAndMinGrade = new int[2];
		
		int numOfHigherStudentThanMyNum = getNumOfHigherStudentThanMyNum();
		int numOfLowerStudentThanMyNum = getNumOfLowerStudentThanMyNum();
		
		maxAndMinGrade[0] = 1 + numOfHigherStudentThanMyNum;
		maxAndMinGrade[1] = this.numOfStudent - numOfLowerStudentThanMyNum;
		
		return maxAndMinGrade;
	}
	
	private int[][] getArrayLowerStudentThanMe() {
		int[] indexs = new int[this.numOfStudent];
		for(int i = 0; i<indexs.length; i++)
			indexs[i] = 0;
		for(int i = 0; i<answer.length; i++)
			indexs[answer[i].higher]++;
		
		
		int[][] arrayLowerStudentThanMe = new int[this.numOfStudent][];
		for(int i = 0; i<arrayLowerStudentThanMe.length; i++)
			arrayLowerStudentThanMe[i] = new int[indexs[i]];
		for(int i = 0; i<indexs.length; i++)
			indexs[i] = 0;
		for(int i = 0; i<answer.length; i++) {
			arrayLowerStudentThanMe[answer[i].higher][indexs[answer[i].higher]++] = answer[i].lower;
		}
		
		return arrayLowerStudentThanMe;	//0~N-1������ ����
	}
	private int[][] getArrayHigherStudentThanMe() {
		int[] indexs = new int[this.numOfStudent];
		for(int i = 0; i<indexs.length; i++)
			indexs[i] = 0;
		for(int i = 0; i<answer.length; i++)
			indexs[answer[i].lower]++;
		
		
		int[][] arrayHigherStudentThanMe = new int[this.numOfStudent][];
		for(int i = 0; i<arrayHigherStudentThanMe.length; i++)
			arrayHigherStudentThanMe[i] = new int[indexs[i]];
		for(int i = 0; i<indexs.length; i++)
			indexs[i] = 0;
		for(int i = 0; i<answer.length; i++) {
			arrayHigherStudentThanMe[answer[i].lower][indexs[answer[i].lower]++] = answer[i].higher;
		}
		
		return arrayHigherStudentThanMe;	//0~N-1������ ����
	}

	private int getNumOfHigherStudentThanMyNum() {
		int numOfHigherStudentThanMyNum = 0;
		int[][] higherStudentsThanMe = getArrayHigherStudentThanMe();
		
		boolean[] isChecked = new boolean[this.numOfStudent];
		for(int i = 0; i<isChecked.length; i++)
			isChecked[i] = false;
		
		LinkedList<Integer> queue = new LinkedList<Integer>();
		for(int i = 0; i<higherStudentsThanMe[myNum].length; i++) {
			queue.add(higherStudentsThanMe[myNum][i]);
			isChecked[higherStudentsThanMe[myNum][i]] = true;
		}
		
		while(!queue.isEmpty()) {
			int nowStudent = queue.getFirst();
			queue.removeFirst();
			
			numOfHigherStudentThanMyNum++;
			
			for(int i = 0; i<higherStudentsThanMe[nowStudent].length; i++) {
				if(isChecked[higherStudentsThanMe[nowStudent][i]])
					continue;
				else {
					queue.add(higherStudentsThanMe[nowStudent][i]);
					isChecked[higherStudentsThanMe[nowStudent][i]] = true;
				}
			}
		}
		
		return numOfHigherStudentThanMyNum;
	}
	private int getNumOfLowerStudentThanMyNum() {
		int numOfLowerStudentThanMyNum = 0;
		int[][] lowerStudentsThanMe = getArrayLowerStudentThanMe();
		
		boolean[] isChecked = new boolean[this.numOfStudent];
		for(int i = 0; i<isChecked.length; i++)
			isChecked[i] = false;
		
		LinkedList<Integer> queue = new LinkedList<Integer>();
		for(int i = 0; i<lowerStudentsThanMe[myNum].length; i++) {
			queue.add(lowerStudentsThanMe[myNum][i]);
			isChecked[lowerStudentsThanMe[myNum][i]] = true;
		}
		
		while(!queue.isEmpty()) {
			int nowStudent = queue.getFirst();
			queue.removeFirst();
			
			numOfLowerStudentThanMyNum++;
			
			for(int i = 0; i<lowerStudentsThanMe[nowStudent].length; i++) {
				if(isChecked[lowerStudentsThanMe[nowStudent][i]])
					continue;
				else{
					queue.add(lowerStudentsThanMe[nowStudent][i]);
					isChecked[lowerStudentsThanMe[nowStudent][i]] = true;
				}
			}
		}
		
		return numOfLowerStudentThanMyNum;
	}
}

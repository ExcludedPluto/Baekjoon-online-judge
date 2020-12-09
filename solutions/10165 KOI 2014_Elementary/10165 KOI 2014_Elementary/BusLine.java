
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;

public class BusLine {
	private int numOfBusStop;
	private BusLineInfo[] busLines;
	
	private class BusLineInfo implements Comparable<BusLineInfo> {
		int num;
		int start;
		int end;

		public BusLineInfo(int num, int start, int end) {
			this.num = num;
			this.start = start;
			this.end = end;
		}
		@Override
		public int compareTo(BusLineInfo info) {
			// TODO Auto-generated method stub
			int temp = this.start - info.start;
			return temp != 0 ? temp : (this.end - info.end);
		}
	}
	
	public BusLine() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			this.numOfBusStop = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		int numOfBusLine = 0;
		try {
			numOfBusLine = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		this.busLines = new BusLineInfo[numOfBusLine];
		try {
			for(int i = 0; i<numOfBusLine; i++) {
				String[] str = br.readLine().split(" ");
				this.busLines[i] = new BusLineInfo(i+1, Integer.parseInt(str[0]), Integer.parseInt(str[1]));
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public int[] deleteDuplicateLine() {
		LinkedList<Integer> lineAfterDelete = new LinkedList<Integer>();
		
		Arrays.sort(this.busLines);
		
		lineAfterDelete.add(0);
		for(int i = 1; i<this.busLines.length; i++) {
			int beforeIndex = lineAfterDelete.getLast();
			boolean isBeforeExceed0 = this.busLines[beforeIndex].end < this.busLines[beforeIndex].start;
			boolean isCurrentExceed0 = this.busLines[i].end < this.busLines[i].start;
			
			if(this.busLines[i].start == this.busLines[beforeIndex].start) {
				if(isBeforeExceed0 && !isCurrentExceed0)
					continue;
				else if(isBeforeExceed0 && isCurrentExceed0) {
					lineAfterDelete = deleteAnyCan(lineAfterDelete, i);
				}
				lineAfterDelete.removeLast();
				lineAfterDelete.add(i);
			}
			else {
				if(isCurrentExceed0) {	//��������� �� ������ �� 0�� ���� ���
					//������ 0�� �Ѱ�, ���� end���� ���� end�� �� ũ�� ����� ��Ƹ���. continue
					if(isBeforeExceed0 && this.busLines[beforeIndex].end >= this.busLines[i].end)
						continue;
					
					//������ ��찡 �ƴϸ�, ��� ���� ����. ���簡 ������ ���� �� �ִ��� Ȯ���ϰ� ���� �� -1�� ǥ��
					lineAfterDelete = deleteAnyCan(lineAfterDelete, i);
					
					//�ٷ� ������ -1�� ǥ�õǾ��ٸ� ������ġ�� ���� ��ġ�� ����ְ�, �ƴϸ� ������ġ�� �ְ� 1����
					lineAfterDelete.add(i);
				}
				else {		//�ȳ��� ���
					//������ ������ ������ ��Ƹ���
					//���������� ���� end�� ���� end���� Ŭ�� ��Ƹ���.
					//�ƴϸ� ����� ���.
					if(!isBeforeExceed0 && this.busLines[i].end > this.busLines[beforeIndex].end)
						lineAfterDelete.add(i);
				}
			}
		}
		
		int[] numsLine = new int[lineAfterDelete.size()];
		for(int i = 0; i<numsLine.length; i++)
			numsLine[i] = lineAfterDelete.get(i);
		
		Arrays.sort(numsLine);
		
		return numsLine;
	}
	
	private LinkedList<Integer> deleteAnyCan(LinkedList<Integer> lineAfterDelete, int current) {
		int currentEnd = this.busLines[current].end;
		LinkedList<Integer> temp = new LinkedList<Integer>();
		
		for(int i = 0; i<lineAfterDelete.size(); i++) {		//������ end�� � ���� start�� end���� ũ�� -1�� �ٲ�. �̶� � ���� 0�� ���� ���ƾ��Ѵ�.
			int currentIndex = lineAfterDelete.get(i);
			if(currentEnd >= this.busLines[currentIndex].end && this.busLines[currentIndex].end > this.busLines[currentIndex].start) {
				;
			}
			else
				temp.add(lineAfterDelete.get(i));
		}
		
		return temp;
	}
	
}

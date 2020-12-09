
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
				if(isCurrentExceed0) {	//출발지점이 더 나중인 게 0을 넘을 경우
					//이전게 0을 넘고, 현재 end보다 이전 end이 더 크면 현재게 잡아먹힘. continue
					if(isBeforeExceed0 && this.busLines[beforeIndex].end >= this.busLines[i].end)
						continue;
					
					//위같은 경우가 아니면, 잡아 먹지 않음. 현재가 이전에 먹을 게 있는지 확인하고 먹은 건 -1로 표시
					lineAfterDelete = deleteAnyCan(lineAfterDelete, i);
					
					//바로 이전에 -1로 표시되었다면 이전위치에 현재 위치를 집어넣고, 아니면 현재위치에 넣고 1증가
					lineAfterDelete.add(i);
				}
				else {		//안넘을 경우
					//이전에 넘으면 무조건 잡아먹힘
					//넘지않으면 이전 end가 현재 end보다 클때 잡아먹음.
					//아니면 현재걸 기록.
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
		
		for(int i = 0; i<lineAfterDelete.size(); i++) {		//현재의 end가 어떤 것의 start와 end보다 크면 -1로 바꿈. 이때 어떤 것은 0을 넘지 말아야한다.
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

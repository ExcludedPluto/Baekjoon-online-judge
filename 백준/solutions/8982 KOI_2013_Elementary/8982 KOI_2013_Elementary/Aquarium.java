
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;

public class Aquarium {
	private VerticalLine[] vl;
	private HorizontalLine[] hl;
	private int[] holeIndex;
	private int waterAmount;
	int[] tempAquarium;
	
	private class Line{
		int first;
		int second;
		public Line() {
			this.first = 0;
			this.second = 0;
		}
	}
	
	private class VerticalLine extends Line{
		int x;
		
		public VerticalLine(int first, int second, int x) {
			this.first = first;
			this.second = second;
			this.x = x;
		}
	}
	
	private class HorizontalLine extends Line {
		int y;
		
		public HorizontalLine(int first, int second, int y) {
			this.first = first;
			this.second = second;
			this.y = y;
		}
	}
	
	public Aquarium() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int numOfDot = 0;
		try {
			numOfDot = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		int[][] dot = new int[numOfDot][2];
		try {
			for(int i = 0; i<numOfDot; i++) {
				String[] str = br.readLine().split(" ");
				dot[i][0] = Integer.parseInt(str[0]);
				dot[i][1] = Integer.parseInt(str[1]);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.vl = makeVerticalLine(dot);
		this.hl = makeHorizontalLine(dot);
		this.waterAmount = getWaterAmount();
		tempAquarium = new int[this.vl[this.vl.length-1].x];
		
		int numOfHole = 0;
		try {
			numOfHole = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		int[][] holeFirst = new int[numOfHole][4];
		try {
			for(int i = 0; i<numOfHole; i++) {
				String[] str = br.readLine().split(" ");
				holeFirst[i][0] = Integer.parseInt(str[0]);
				holeFirst[i][1] = Integer.parseInt(str[1]);
				holeFirst[i][2] = Integer.parseInt(str[2]);
				holeFirst[i][3] = Integer.parseInt(str[3]);
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
		getInstanceHole(holeFirst);
	}
	
	private VerticalLine[] makeVerticalLine(int[][] dot) {
		VerticalLine[] vl = new VerticalLine[dot.length/2];
		for(int i = 0; i<dot.length; i+=2) {	//0 2 4 6 8 10 12
			int first = 0;
			int second = 0;
			if(dot[i][1] < dot[i+1][1]) {
				first = dot[i][1];
				second = dot[i+1][1];
			}
			else {
				first = dot[i+1][1];
				second = dot[i][1];
			}
			
			vl[i/2] = new VerticalLine(first, second, dot[i][0]);
		}
		
		return vl;
	}
	
	private HorizontalLine[] makeHorizontalLine(int[][] dot) {
		HorizontalLine[] hl = new HorizontalLine[dot.length/2 -1];
		for(int i = 0; i<hl.length; i++) {
			int odd = 2*i + 1;
			int y = dot[odd][1];
			hl[i] = new HorizontalLine(dot[odd][0], dot[odd+1][0], y);
		}
		
		return hl;
	}
	
	private int getWaterAmount() {
		int waterAmount = 0;
		for(int i = 0; i<hl.length; i++) {
			waterAmount += (hl[i].y*(hl[i].second - hl[i].first));
		} 
		
		return waterAmount;
	}
	
	private void getInstanceHole(int[][] holeFirst) {
		this.holeIndex = new int[holeFirst.length];
		int index = 0;
		for(int i = 0; i<holeFirst.length; i++) {
			int first = holeFirst[i][0];
			int second = holeFirst[i][2];
			int y = holeFirst[i][1];
			
			for(int j = 0; j<hl.length; j++) {
				if(first >= hl[j].first && second <= hl[j].second && y == hl[j].y) {
					this.holeIndex[index++] = j;
					break;
				}
			}
		}
	}
	
	//구멍에서 왼쪽-오른쪽으로 진행 -> 부딫히는 벽이 있으면 스탑하고 위로 올라감 -> 다 올라갔는데 그곳이 0이면 스탑, 아니면 다시 왼쪽-오른쪽으로 꺾어서 진행하여 다 올라갈때가지 반복
	//스탑할때마다 점들을 기록
	//
	public int getRestWater() {
		for(int i = 0; i<tempAquarium.length; i++)
			tempAquarium[i] = 0;
		
		for(int i = 0; i<this.holeIndex.length; i++) {
			int currentHoleIndex = this.holeIndex[i];
			
			//왼쪽
			LinkedList<int[]> dotLeft = new LinkedList<int[]>();
			int nowY = this.hl[currentHoleIndex].y;
			for(int leftVl = currentHoleIndex; leftVl >=0; leftVl--) {
				if(nowY > this.vl[leftVl].first) {
					dotLeft.add(new int[] {this.vl[leftVl].x, nowY});
					nowY = this.vl[leftVl].first;
					dotLeft.add(new int[] {this.vl[leftVl].x, nowY});
					if(nowY == 0)
						break;
				}
			}
			
			//오른쪽
			LinkedList<int[]> dotRight = new LinkedList<int[]>();
			nowY = this.hl[currentHoleIndex].y;
			for(int rightVl = currentHoleIndex+1; rightVl < this.vl.length; rightVl++) {
				if(nowY > this.vl[rightVl].first) {
					dotRight.add(new int[] {this.vl[rightVl].x, nowY});
					nowY = this.vl[rightVl].first;
					dotRight.add(new int[] {this.vl[rightVl].x, nowY});
					if(nowY == 0)
						break;
				}
			}
			
			int[][] dot = new int[dotLeft.size() + dotRight.size()][2];
			int end = dotLeft.size();
			for(int k = 0; k<end; k++) {
				dot[k] = dotLeft.getLast();
				dotLeft.removeLast();
			}
			for(int k = end; k < dot.length; k++) {
				dot[k] = dotRight.getFirst();
				dotRight.removeFirst();
			}
			dotLeft.clear();
			dotRight.clear();
			
			int length = dot.length/2 -1;
			for(int k = 0; k<length; k++) {
				int odd = 2*k +1;
				for(int j = dot[odd][0]; j<dot[odd+1][0]; j++) {
					if(dot[odd][1] > tempAquarium[j])
						tempAquarium[j] = dot[odd][1];
				}
			}
		}
		
		int waterSinked = 0;
		for(int i = 0; i<tempAquarium.length; i++) {
			waterSinked += tempAquarium[i];
		}
		return this.waterAmount - waterSinked;
	}
}
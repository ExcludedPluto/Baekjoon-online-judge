
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

public class WaterTank {
	private int[][] waterTank;
	private Hole[][] holes;
	
	private class Hole {
		int up;
		int down;
		int left;
		int right;
	}
	
	private class Temp implements Comparable<Temp>{
		int row;
		int col;
		int h;
		
		public Temp(int i, int j, int h) {
			this.row = i;
			this.col = j;
			this.h = h;
		}
		@Override
		public int compareTo(Temp t) {
			return this.h - t.h;
		}
	}
	
	public WaterTank() {
		getProperties();
	}
	
	private void getProperties(){
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int height = 0;
		int width = 0;
		int waterHeight = 0;
		try {
			String[] str = br.readLine().split(" ");
			height = Integer.parseInt(str[0]);
			width = Integer.parseInt(str[1]);
			waterHeight = Integer.parseInt(str[2]);
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		waterTank = new int[height][width];
		for(int i = 0; i<waterTank.length; i++)
			for(int j = 0; j<waterTank[i].length; j++)
				waterTank[i][j] = waterHeight;
		
		holes = new Hole[height][width];
		for(int i = 0; i<height; i++)
			for(int j = 0; j<width; j++)
				holes[i][j] = new Hole();
		try {
			int heightIndex = height+1;
			for(int i = 0; i<heightIndex; i++) {
				String[] str = br.readLine().split(" ");
				if(i == height)
					for(int row = 0; row<width; row++) {
						holes[i-1][row].down = Integer.parseInt(str[row]);
					}
				else if(i == 0)
					for(int row = 0; row<width; row++) {
						holes[i][row].up = Integer.parseInt(str[row]);
					}
				else
					for(int row = 0; row<width; row++) {
						holes[i][row].up = holes[i-1][row].down = Integer.parseInt(str[row]);
					}
			}
		
			for(int i = 0; i<height; i++) {
				String[] str = br.readLine().split(" ");
				holes[i][0].left = Integer.parseInt(str[0]);
				for(int row = 1; row < width; row++) {
					holes[i][row-1].right = holes[i][row].left = Integer.parseInt(str[row]);
				}
				holes[i][width-1].right = Integer.parseInt(str[width]);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public int getTotalAmountOfWaterTank() {
		initialHoles();
		sinkWaterTank();
		int volume = 0;
		for(int i = 0; i<waterTank.length; i++)
			for(int j = 0; j<waterTank[i].length; j++)
				volume += waterTank[i][j];
		return volume;
	}
	
	private void initialHoles() {
		if(this.waterTank.length == 1) {
			for(int i = 0; i<this.waterTank[0].length; i++) {
				if(holes[0][i].up != -1 && holes[0][i].down != -1) {
					if(holes[0][i].up < holes[0][i].down)
						holes[0][i].down = -1;
					else
						holes[0][i].up = -1;
				}
			}
		}
		if(this.waterTank[0].length == 1) {
			for(int i = 0; i<this.waterTank.length; i++) {
				if(holes[i][0].left != -1 && holes[i][0].right != -1) {
					if(holes[i][0].left < holes[i][0].right)
						holes[0][i].right = -1;
					else
						holes[0][i].left = -1;
				}
			}
		}
		
		if(holes[0][0].up != -1 && holes[0][0].left != -1) {
			if(holes[0][0].up < holes[0][0].left)
				holes[0][0].left = -1;
			else
				holes[0][0].up = -1;
		}
		if(holes[0][holes[0].length-1].up != -1 && holes[0][holes[0].length-1].right != -1) {
			if(holes[0][holes[0].length-1].up < holes[0][holes[0].length-1].right)
				holes[0][holes[0].length-1].right = -1;
			else
				holes[0][holes[0].length-1].up = -1;
		}
		if(holes[holes.length -1][0].down != -1 && holes[holes.length -1][0].left != -1) {
			if(holes[holes.length -1][0].down < holes[holes.length -1][0].left)
				holes[holes.length -1][0].left = -1;
			else
				holes[holes.length -1][0].down = -1;
		}
		if(holes[holes.length -1][holes[0].length-1].down != -1 && holes[holes.length -1][holes[0].length-1].right != -1) {
			if(holes[holes.length -1][holes[0].length-1].down < holes[holes.length -1][holes[0].length-1].right)
				holes[holes.length -1][holes[0].length-1].right = -1;
			else
				holes[holes.length -1][holes[0].length-1].down = -1;
		}
	}
	
	//바깥하고 연결된 곳을 따로 리스트에 저장
	//바깥하고 연결된 곳을 하나씩 빼가며 연결된 곳으로 올라가면서 줄임.
	//구석 처리가 애매함.
	private void sinkWaterTank() {
		ArrayList<Temp> cellConnectedOutside = makeCellConnectedOutside();
		int size = cellConnectedOutside.size();
		
		for(int k = 0; k<size; k++) {
			ArrayList<int[]> temp = new ArrayList<int[]>();
			Temp t = cellConnectedOutside.get(k);
			temp.add(new int[] {t.row, t.col});
			boolean[][] check = new boolean[this.waterTank.length][this.waterTank[0].length];
			check[t.row][t.col] = true;
			
			while(!temp.isEmpty()) {
				int[] current = temp.get(0);
				temp.remove(0);
				int i = current[0];
				int j = current[1];
				int down = i+1;
				int up = i-1;
				int right = j+1;
				int left = j-1;
				
				if(this.holes[i][j].up != -1 && i > 0 && !check[up][j]) 
					if(this.waterTank[i][j] < this.waterTank[up][j]) {
						if(this.waterTank[i][j] >= this.holes[i][j].up) {
							this.waterTank[up][j] = this.waterTank[i][j];
							check[up][j] = true;
							temp.add(new int[] {up, j});
						}
						else if(this.waterTank[up][j] > this.holes[i][j].up) {
							this.waterTank[up][j] = this.holes[i][j].up;
							check[up][j] = true;
							temp.add(new int[] {up, j});
						}
					}
				
				if(this.holes[i][j].right != -1 && j < this.waterTank[0].length-1 && !check[i][right])
					if(this.waterTank[i][j] < this.waterTank[i][right]) {
						if(this.waterTank[i][j] >= this.holes[i][j].right) {
							this.waterTank[i][right] = this.waterTank[i][j];
							check[i][right] = true;
							temp.add(new int[] {i, right});
						}
						else if(this.waterTank[i][right] > this.holes[i][j].right) {
							this.waterTank[i][right] = this.holes[i][j].right;
							check[i][right] = true;
							temp.add(new int[] {i, right});
						}
					}
				
				if(this.holes[i][j].down != -1 && i < this.waterTank.length -1 &&!check[down][j]) 
					if(this.waterTank[i][j] < this.waterTank[down][j]) {
						if(this.waterTank[i][j] >= this.holes[i][j].down) {
							this.waterTank[down][j] = this.waterTank[i][j];
							check[down][j] = true;
							temp.add(new int[] {down, j});
						}
						else if(this.waterTank[down][j] > this.holes[i][j].down) {
							this.waterTank[down][j] = this.holes[i][j].down;
							check[down][j] = true;
							temp.add(new int[] {down, j});
						}
					}
					
				
				if(this.holes[i][j].left != -1 && j>0 && !check[i][left]) 
					if(this.waterTank[i][j] < this.waterTank[i][left]) {
						if(this.waterTank[i][j] >= this.holes[i][j].left) {
							this.waterTank[i][left] = this.waterTank[i][j];
							check[i][left] = true;
							temp.add(new int[] {i, left});
						}
						else if(this.waterTank[i][left] > this.holes[i][j].left) {
							this.waterTank[i][left] = this.holes[i][j].left;
							check[i][left] = true;
							temp.add(new int[] {i, left});
						}
					}
			}
		}
	}
	
	private ArrayList<Temp> makeCellConnectedOutside() {
		ArrayList<Temp> cellConnectedOutside = new ArrayList<Temp>();
		boolean[][] check = new boolean[this.waterTank.length][this.waterTank[0].length];
		
		//맨 윗줄
		for(int i = 0; i<this.waterTank[0].length; i++)
			if(!check[0][i] && doesConnectOutside(0, i)) {
				cellConnectedOutside.add(new Temp(0, i, waterTank[0][i]));
				check[0][i] = true;
			}
		
		//맨 아랫줄
		int lastRow = this.waterTank.length -1;
		for(int i = 0; i<this.waterTank[0].length; i++)
			if(!check[lastRow][i] && doesConnectOutside(lastRow, i)) {
				cellConnectedOutside.add(new Temp(lastRow, i, waterTank[lastRow][i]));
				check[lastRow][i] = true;
			}
		
		//맨 오른쪽 줄
		int lastCol = this.waterTank[0].length-1;
		for(int i = 1; i<lastRow; i++)
			if(!check[i][lastCol] && doesConnectOutside(i, lastCol)) {
				cellConnectedOutside.add(new Temp(i, lastCol, waterTank[i][lastCol]));
				check[i][lastCol] = true;
			}
		
		//맨 왼쪽 줄
		for(int i = 1; i<lastRow; i++)
			if(!check[i][0] && doesConnectOutside(i, 0)) {
				cellConnectedOutside.add(new Temp(i, 0, waterTank[i][0]));
				check[i][0] = true;
			}
		
		Collections.sort(cellConnectedOutside);
		
		return cellConnectedOutside;
	}

	private boolean doesConnectOutside(int i, int j) {
		if(i == 0) {
			if(j == 0) {
				if(this.holes[i][j].left != -1 || this.holes[i][j].up != -1) {
					this.waterTank[i][j] = this.holes[i][j].left != -1 ? this.holes[i][j].left : this.holes[i][j].up;
					return true;
				}
			}
			if(j == this.holes[i].length -1) {
				if(this.holes[i][j].right != -1 || this.holes[i][j].up != -1){
					this.waterTank[i][j] = this.holes[i][j].right != -1 ? this.holes[i][j].right : this.holes[i][j].up;
					return true;
				}
			}
			
			if(this.holes[i][j].up != -1){
				this.waterTank[i][j] = this.holes[i][j].up;
				return true;
			}
			
		}
		
		if(i == this.holes.length-1) {
			if(j == 0) {
				if(this.holes[i][j].left != -1 || this.holes[i][j].down != -1){
					this.waterTank[i][j] = this.holes[i][j].left != -1 ? this.holes[i][j].left : this.holes[i][j].down;
					return true;
				}
			}
			if(j == this.holes[i].length -1) {
				if(this.holes[i][j].right != -1 || this.holes[i][j].down != -1){
					this.waterTank[i][j] = this.holes[i][j].right != -1 ? this.holes[i][j].right : this.holes[i][j].down;
					return true;
				}
			}
			
			if(this.holes[i][j].down != -1){
				this.waterTank[i][j] = this.holes[i][j].down;
				return true;
			}
		}
		
		if(j == 0) {
			if(this.holes[i][j].left != -1){
				this.waterTank[i][j] = this.holes[i][j].left;
				return true;
			}
		}
		if(j == this.holes[i].length -1) {
			if(this.holes[i][j].right != -1){
				this.waterTank[i][j] = this.holes[i][j].right;
				return true;
			}
		}
		return false;
	}
}

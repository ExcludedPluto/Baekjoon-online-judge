
import java.io.BufferedReader;
import java.io.InputStreamReader;

//점들 입력 받고
//점들 버킷정렬
//각 색깔에 맞는 곳에 집어넣고
//앞뒤로만 검색하여 가장 짧은 거리를 더함.

public class ArrowDrawing {
	private int[][] dots;
	
	public ArrowDrawing() {
		getProperties();
		buketSortForDots();
		//print();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int numOfDot = 0;
		try {
			numOfDot = Integer.parseInt(br.readLine());
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		dots = new int[numOfDot][2];
		try {
			for(int i = 0; i<numOfDot; i++) {
				String[] str = br.readLine().split(" ");
				dots[i][0] = Integer.parseInt(str[0]);
				dots[i][1] = Integer.parseInt(str[1]);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void buketSortForDots() {
		int []buket = new int[100001];
		for(int i = 0; i<100001; i++)
			buket[i] = -1;
		
		for(int i = 0; i<dots.length; i++) {
			buket[dots[i][0]] = dots[i][1];
		}
		
		int dotsIndex = 0;
		for(int i = 0; i<100001; i++) {
			if(buket[i] != -1) {
				dots[dotsIndex][0] = i;
				dots[dotsIndex][1] = buket[i];
				dotsIndex++;
			}
		}
	}
	
	public int addAndGetAllArrow() {
		return sumEveryArrow(getDotsLinedByColor());
	}
	
	private int[][] getDotsLinedByColor() {
		int []colorIndex = new int[dots.length];
		for(int i = 0; i<colorIndex.length; i++)
			colorIndex[i] = 0;
		for(int i = 0; i<colorIndex.length; i++) {
			colorIndex[dots[i][1]-1]++;
		}
		
		int [][]dotsLinedByColor = new int[dots.length][];
		for(int i = 0; i<colorIndex.length; i++) {
			dotsLinedByColor[i] = new int[colorIndex[i]];
		}
		
		for(int i = 0; i<colorIndex.length; i++)
			colorIndex[i] = 0;
		for(int i = 0; i<dots.length; i++) {
			int currentColor = dots[i][1]-1;
			dotsLinedByColor[currentColor][colorIndex[currentColor]++] = dots[i][0];
		}
		
		return dotsLinedByColor;
	}
	
	private int sumEveryArrow(int [][]dotsLinedByColor) {
		int everyArrowSum = 0;
		
		for(int color = 0; color<dotsLinedByColor.length; color++) {
			if(dotsLinedByColor[color].length != 0) {
				everyArrowSum += (dotsLinedByColor[color][1] - dotsLinedByColor[color][0]);
				everyArrowSum += (dotsLinedByColor[color][dotsLinedByColor[color].length - 1] 
									- dotsLinedByColor[color][dotsLinedByColor[color].length - 2]);
			}
				
			for(int currentDot = 1; currentDot < dotsLinedByColor[color].length-1; currentDot++) {
				int forward = dotsLinedByColor[color][currentDot] -  dotsLinedByColor[color][currentDot-1];
				int backward = dotsLinedByColor[color][currentDot+1] -  dotsLinedByColor[color][currentDot];
				
				everyArrowSum += (forward < backward ? forward : backward);
			}
		}
		
		return everyArrowSum;
	}
	
	private void print() {
		for(int i = 0; i<dots.length; i++) {
			System.out.println(dots[i][0] + " " + dots[i][1]);
		}
	}
	
}

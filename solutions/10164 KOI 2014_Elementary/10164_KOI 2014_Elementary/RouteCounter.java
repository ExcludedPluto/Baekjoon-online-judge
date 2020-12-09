
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class RouteCounter {
	private int []circleLocation = new int[2];
	int []end = new int[2];
	
	public RouteCounter() {
		try {
			getProperties();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void getProperties() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String []str = new String[3];
		str = br.readLine().split(" ");
		
		int height = Integer.parseInt(str[0]);
		int width = Integer.parseInt(str[1]);
		end[0] = width;
		end[1] = height;
		
		int tempCircleLocation = Integer.parseInt(str[2]);
		circleLocation[0] = (tempCircleLocation % width);
		circleLocation[1] = (tempCircleLocation / width)+1;
		if(tempCircleLocation % width == 0 && circleLocation[0] + circleLocation[1] != 1) {
			circleLocation[0] = width;
			circleLocation[1]--;
		}
	}
	
	public int countRoute() {
		int []start = new int[2];
		start[0] = 1;
		start[1] = 1;
		
		
		if(circleLocation[0] == 0 && circleLocation[1] == 1) {
			return countRouteFromStartToEnd(start, end);
		}
		else {
			int countToCircle =  countRouteFromStartToEnd(start, circleLocation);
			int countToEnd = countRouteFromStartToEnd(circleLocation, end);
			
			return countToCircle*countToEnd;
		}
	}
	
	private int countRouteFromStartToEnd(int[] start, int[] end) {
		int tempHeight = end[1] - start[1] + 1;
		int tempWidth = end[0] - start[0] + 1;
		int [][]map = new int[tempHeight][tempWidth];
	
		for(int i = 0; i<tempHeight; i++) {
			for(int j = 0; j<tempWidth; j++) {
				map[i][j] = 0;
			}
		}
		for(int row = 0; row<tempHeight; row++)
			map[row][0] = 1;
		for(int col = 0; col<tempWidth; col++)
			map[0][col] = 1;
		
		
		for(int row = 0; row<tempHeight; row++) {
			for(int col = 0; col<tempWidth; col++) {
				if(row - 1 >= 0 && col -1 >=0)
					map[row][col] = map[row-1][col] + map[row][col-1];
			}
		}
		return map[tempHeight-1][tempWidth-1];	
	}
}

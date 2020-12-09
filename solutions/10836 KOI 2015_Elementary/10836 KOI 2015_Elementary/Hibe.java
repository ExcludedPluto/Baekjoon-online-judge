
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Hibe {
	private int width;
	private int days;
	private int[][] amountGrow;
	
	public Hibe() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			String[] str = br.readLine().split(" ");
			this.width = Integer.parseInt(str[0]);
			this.days = Integer.parseInt(str[1]);
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		this.amountGrow = new int[days][3];
		try {
			for(int i = 0; i<days; i++) {
				String[] str = br.readLine().split(" ");
				this.amountGrow[i][0] = Integer.parseInt(str[0]);
				this.amountGrow[i][1] = Integer.parseInt(str[1]);
				this.amountGrow[i][2] = Integer.parseInt(str[2]);
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public int[][] getHibeAfterDays() {
		int rowSize = 2*this.width -1;
		int[][] hibe = new int[this.width][this.width];
		int[] firstColAndRow = new int[2*this.width-1];
		for(int i = 0; i<firstColAndRow.length; i++)
			firstColAndRow[i] = 1;
		
		for(int[] oneDay : this.amountGrow) {
			int index = oneDay[0];
			int secondIndex = oneDay[0] + oneDay[1];
			
			while(index < secondIndex) {
				firstColAndRow[index++]++;
			}
			while(secondIndex < rowSize) {
				firstColAndRow[secondIndex++] += 2;
			}
		}
		
		int width = this.width-1;
		for(int i = 0; i<this.width; i++) 
			hibe[width-i][0] = firstColAndRow[i];
		for(int i = 0; i<width; i++)
			hibe[0][i+1] = firstColAndRow[i+this.width];
		
		for(int i = 1; i<this.width; i++) {
			for(int j = 1; j<this.width; j++)
				hibe[i][j] = hibe[0][j];
		}
		
		return hibe;
	}
	public int[][] getHibeAfterDays2() {
		int rowSize = 2*this.width -1;
		int[][] hibe = new int[this.width][this.width];
		int[] firstColAndRow = new int[rowSize];
		
		for(int[] row : this.amountGrow) {
			int one = row[0];
			int two = one + row[1];
			
			if(one < rowSize)
				firstColAndRow[one]++;
			if(two <rowSize)
				firstColAndRow[two]++;
		}
		
		for(int i = 1; i<firstColAndRow.length; i++)
			firstColAndRow[i] += firstColAndRow[i-1];
		for(int i = 0; i<firstColAndRow.length; i++)
			firstColAndRow[i]++;
		
		int width = this.width-1;
		for(int i = 0; i<this.width; i++) 
			hibe[width-i][0] = firstColAndRow[i];
		for(int i = 0; i<width; i++)
			hibe[0][i+1] = firstColAndRow[i+this.width];
		
		for(int i = 1; i<this.width; i++) {
			for(int j = 1; j<this.width; j++)
				hibe[i][j] = hibe[0][j];
		}
		
		return hibe;
	}
}

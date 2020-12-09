
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class PaperAreaGenerator {
	private int [][]area = new int[101][101];
	private int numOfPaper;
	private int [][]papers;
	
	public PaperAreaGenerator() {
		try {
			getProperties();
		} catch (NumberFormatException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void getProperties() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		numOfPaper = Integer.parseInt(br.readLine());
		
		papers = new int[numOfPaper][4];
		for(int i = 0; i<numOfPaper; i++) {
			String []str = new String[4];
			str = br.readLine().split(" ");
			papers[i][0] = Integer.parseInt(str[0]);
			papers[i][1] = Integer.parseInt(str[1]);
			papers[i][2] = Integer.parseInt(str[2]);
			papers[i][3] = Integer.parseInt(str[3]);
		}
		for(int i = 0; i<101; i++)
			for(int j = 0; j<101; j++)
				area[i][j] = -1;
	}
	public void getPapersArea() {
		putPaperByOrder();
		printPaperArea();
	}
	
	private void putPaperByOrder() {
		for(int paper = 0; paper<numOfPaper; paper++) {
			for(int height = 0; height<papers[paper][3]; height++) {
				for(int width = 0; width<papers[paper][2]; width++) {
					area[papers[paper][1] + height][papers[paper][0]+width] = paper;
				}
			}
		}
	}
	
	private void printPaperArea() { 
		for(int paper = 0; paper<numOfPaper; paper++) {
			int count = 0;
			for(int i = 0; i < 101; i++) {
				for(int j = 0; j<101; j++) {
					if(area[i][j] == paper)
						count++;
				}
			}
			System.out.println(count);
		}
	}
}

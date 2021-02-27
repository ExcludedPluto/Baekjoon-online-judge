
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class HiddenWayInLadder {
	int nOfParticipants;
	int nOfhorizon;
	int []resultOfLadderGame;
	int [][]ladder;
	
	public HiddenWayInLadder() {
		try {
			getValues();
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	private void getValues() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		nOfParticipants = Integer.parseInt(br.readLine());
		nOfhorizon = Integer.parseInt(br.readLine());
		
		resultOfLadderGame = new int[nOfParticipants];
		char[] tempStr = new char[nOfParticipants];
		tempStr = br.readLine().toCharArray();
		
		for(int i = 0; i<nOfParticipants; i++)
			resultOfLadderGame[i] = tempStr[i] - 64;
		
		char[] tempStrForladder = new char[nOfParticipants-1];
		ladder = new int[nOfhorizon][nOfParticipants-1];
		for(int i = 0; i<nOfhorizon; i++) {
			tempStrForladder = br.readLine().toCharArray();
			for(int j = 0; j<nOfParticipants-1; j++)
				if(tempStrForladder[j] == '*')
					ladder[i][j] = 0;
				else if(tempStrForladder[j] == '-')
					ladder[i][j] = 1;
				else
					ladder[i][j] = -1;
		}
		br.close();
	}
	
	
	public void searchHiddenWayInLadder() {
		int []aboveLineOfHiddenWay = new int[nOfParticipants];
		int []belowLineOfHiddenWay = new int[nOfParticipants];
		initAboveAndBelowLine(aboveLineOfHiddenWay, belowLineOfHiddenWay);
		
		getAboveAndBelowLine(aboveLineOfHiddenWay, belowLineOfHiddenWay);
		
		int []hiddenWay = new int[nOfParticipants-1];
		hiddenWay = getHiddenWay(aboveLineOfHiddenWay, belowLineOfHiddenWay);
		checkHiddenWayAndPrint(hiddenWay);
		
	}
	private void initAboveAndBelowLine(int []aboveLine, int []belowLine) {
		for(int i = 0; i<this.nOfParticipants; i++) {
			aboveLine[i] = i+1;
			belowLine[i] = resultOfLadderGame[i];
		}
	}
	private void getAboveAndBelowLine(int []aboveLine, int []belowLine) {
		int above = 0;
		int below = nOfhorizon-1;
		while(ladder[above][0] != -1) {
			sendLineToNext(aboveLine, ladder[above]);
			above++;
		}
		while(ladder[below][0] != -1) {
			sendLineToNext(belowLine, ladder[below]);
			below--;
		}
	}
	private void sendLineToNext(int []line, int []nextFloor) {
		int []tempLine = new int[nOfParticipants];
		for(int i = 0; i<nOfParticipants; i++) {
			if(i == 0) {
				if(nextFloor[i] == 1)
					tempLine[i+1] = line[i];
				else
					tempLine[i] = line[i];
			}
			else if(i == nOfParticipants-1) {
				if(nextFloor[i-1] == 1)
					tempLine[i-1] = line[i];
				else
					tempLine[i] = line[i];
			}
			else {
				if(nextFloor[i-1] == 1)
					tempLine[i-1] = line[i];
				else if(nextFloor[i] == 1)
					tempLine[i+1] = line[i];
				else
					tempLine[i] = line[i];
			}
		}
		for(int i = 0; i<this.nOfParticipants; i++)
			line[i] = tempLine[i];
	}
	private int[] getHiddenWay(int[] aboveLine, int[]belowLine) {
		int []hiddenWay = new int[this.nOfParticipants-1];
		for(int i = 0; i<this.nOfParticipants-1; i++) {
			hiddenWay[i] = -1;
		}
		
		for(int i = 0; i<this.nOfParticipants; i++) {
			if(i==0) {
				if(aboveLine[i] == belowLine[i]) {
					hiddenWay[i] = 0;
				}
				else if(aboveLine[i] == belowLine[i+1]) {
					hiddenWay[i] = 1;
				}
			}
			else if(i == this.nOfParticipants-1)
				continue;
			/*
			else if(i == this.nOfParticipants-1) {
				if(aboveLine[i] == belowLine[i])
					hiddenWay[i-1] = 0;
				else if(aboveLine[i] == belowLine[i-1])
					hiddenWay[i-1] = 1;
			}*/
			else {
				if(aboveLine[i] == belowLine[i]) {
					hiddenWay[i] = 0;
				}
				else if(aboveLine[i] == belowLine[i-1]) {
					hiddenWay[i] = 0;
				}
				else if(aboveLine[i] == belowLine[i+1]) {
					hiddenWay[i] = 1;
				}
			}
		}
		
		return hiddenWay;
	}
	private void checkHiddenWayAndPrint(int []hiddenWay) {
		for(int i = 0; i<this.nOfParticipants-1; i++)
			if(hiddenWay[i] == -1) {
				for(int j = 0; j<this.nOfParticipants-1; j++)
					System.out.print("x");
				return;
			}
		for(int i = 0; i<this.nOfParticipants-1; i++) {
			if(hiddenWay[i] == 0)
				System.out.print('*');
			else if(hiddenWay[i] == 1)
				System.out.print('-');
			else
				System.out.print('x');
		}
		return;
	}
	
	
}

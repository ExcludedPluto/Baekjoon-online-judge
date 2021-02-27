
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CardGame {
	private int numOfRound;
	private int [][]ACards;
	private int [][]BCards;
	
	public CardGame() {
		try {
			getProperties();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	private void getProperties() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		numOfRound = Integer.parseInt(br.readLine());
		
		ACards = new int[numOfRound][4];
		BCards = new int[numOfRound][4];
		for(int i = 0; i<numOfRound; i++)
			for(int j = 0; j<4; j++)
				ACards[i][j] = BCards[i][j] = 0;
		
		for(int i = 0; i<numOfRound; i++) {
			String []aCards = br.readLine().split(" ");
			String []bCards = br.readLine().split(" ");
			
			for(int j = 1; j <= Integer.parseInt(aCards[0]); j++) {
				ACards[i][Integer.parseInt(aCards[j]) - 1]++;
			}
			for(int j = 1; j <= Integer.parseInt(bCards[0]); j++) {
				BCards[i][Integer.parseInt(bCards[j]) - 1]++;
			}
		}
	}
	
	public String[] getRecordForGame() {
		String[] records = new String[numOfRound];
		
		for(int round = 0; round<numOfRound; round++) {
			if(ACards[round][3] > BCards[round][3] || ACards[round][3] < BCards[round][3]) {
				if(ACards[round][3] > BCards[round][3])
					records[round] = "A";
				else
					records[round] = "B";
					
			}
			else if(ACards[round][2] > BCards[round][2] || ACards[round][2] < BCards[round][2]) {
				if(ACards[round][2] > BCards[round][2])
					records[round] = "A";
				else
					records[round] = "B";
					
			}
			else if(ACards[round][1] > BCards[round][1] || ACards[round][1] < BCards[round][1]) {
				if(ACards[round][1] > BCards[round][1])
					records[round] = "A";
				else
					records[round] = "B";
					
			}
			else if(ACards[round][0] > BCards[round][0] || ACards[round][0] < BCards[round][0]) {
				if(ACards[round][0] > BCards[round][0])
					records[round] = "A";
				else
					records[round] = "B";
					
			}
			else
				records[round] = "D";
		}
		
		return records;
	}
}

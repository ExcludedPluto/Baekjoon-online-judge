
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class rankForCountry {
	int numOfCountries;
	int countryForReturn;
	int [][]medal;
	
	public rankForCountry() {
		getProperties();
	}
	
	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String []str = new String[2];
		try {
			str = br.readLine().split(" ");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		numOfCountries = Integer.parseInt(str[0]);
		countryForReturn = Integer.parseInt(str[1]) -1;
		
		medal = new int[numOfCountries][3];
		for(int i = 0; i<numOfCountries; i++) {
			String []str2 = new String[4];
			try {
				str2 = br.readLine().split(" ");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			int countryIndex = Integer.parseInt(str2[0]) - 1;
			medal[countryIndex][0] = Integer.parseInt(str2[1]);
			medal[countryIndex][1] = Integer.parseInt(str2[2]);
			medal[countryIndex][2] = Integer.parseInt(str2[3]);
		}
	}
	
	public void findACountryRank() {
		boolean []higherRankCountries = new boolean[numOfCountries];
		int numOfHigherRankCountries = 0;
		boolean []lowerRankCountries = new boolean[numOfCountries];
		for(int i = 0; i<numOfCountries; i++) {
			higherRankCountries[i] = false;
			lowerRankCountries[i] = false;
		}
		
		
		for(int i = 0; i<numOfCountries; i++) {
			if(medal[i][0] > medal[countryForReturn][0]) {
				higherRankCountries[i] = true;
				numOfHigherRankCountries++;
			}
			else if(medal[i][0] < medal[countryForReturn][0]) {
				lowerRankCountries[i] = true;
			}
		}
		
		for(int i = 0; i<numOfCountries; i++) {
			if(higherRankCountries[i] == true || lowerRankCountries[i] == true) {
				continue;
			}
			else {
				if(medal[i][1] > medal[countryForReturn][1]) {
					higherRankCountries[i] = true;
					numOfHigherRankCountries++;
				}
				else if(medal[i][1] < medal[countryForReturn][1]) {
					lowerRankCountries[i] = true;
				}
			}
		}
		
		for(int i = 0; i<numOfCountries; i++) {
			if(higherRankCountries[i] == true || lowerRankCountries[i] == true) {
				continue;
			}
			else {
				if(medal[i][2] > medal[countryForReturn][2]) {
					higherRankCountries[i] = true;
					numOfHigherRankCountries++;
				}
				else if(medal[i][2] < medal[countryForReturn][2]) {
					lowerRankCountries[i] = true;
				}
			}
		}
		
		System.out.println(numOfHigherRankCountries + 1);
	}
	
}

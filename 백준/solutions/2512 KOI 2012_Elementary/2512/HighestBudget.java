
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class HighestBudget {
	private int numOfStates;
	private int[] requstedBudget;
	private int budget;
	
	public HighestBudget() {
		try {
			getProperties();
		} catch (NumberFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	private void getProperties() throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		numOfStates = Integer.parseInt(br.readLine());
		
		String []str = new String[numOfStates];
		str = br.readLine().split(" ");
		requstedBudget = new int[numOfStates];
		for(int i = 0; i<numOfStates; i++) {
			requstedBudget[i] = Integer.parseInt(str[i]);
		}
		
		budget = Integer.parseInt(br.readLine());		
		
		
		System.out.println(this.numOfStates);
		for(int i:requstedBudget)
			System.out.print(i + " ");
		System.out.println();
		System.out.println(budget);
	}
	public void distributeBudget() {
		int allBudget = sumAllBudget();
		if(canDistributeAllTheyWant(allBudget)) {
			int maxBudget = findMaxBudget();
			System.out.println(maxBudget);
			return;
		}

		int upperLimitBudget = findUpperLimitBudget(allBudget);
		System.out.println(upperLimitBudget);
		
	}
	public int sumAllBudget() {
		int allBudget = 0;
		for(int i : requstedBudget)
			allBudget += i;
		return allBudget;
	}
	public boolean canDistributeAllTheyWant(int allBudget) {
		if(allBudget <= budget)
			return true;
		else
			return false;
	}
	public int findMaxBudget() {

		int max = 0;
		for(int i : requstedBudget)
			if(max < i)
				max = i;
		return max;
	}
	public int findUpperLimitBudget(int allBudget) {
		int upperLimitBudget = allBudget / numOfStates;
		int tempUpperLimitBudget = upperLimitBudget;
		boolean isFirstUP = true;
		
		while(true) {
			int distributedBudgetAtThisTime = 0;
			for(int i : requstedBudget) {
				if(i<=tempUpperLimitBudget)
					distributedBudgetAtThisTime += i;
				else
					distributedBudgetAtThisTime += tempUpperLimitBudget;
			}
			
			int leftBudget = budget - distributedBudgetAtThisTime;
			if(leftBudget == 0) {
				//이번차에 budget을 다 썼으므로 이번 tempUpperLimitBudget을 반환.
				upperLimitBudget = tempUpperLimitBudget;
				break;
			}
			else if(leftBudget < 0) {
				if(upperLimitBudget == tempUpperLimitBudget)
					isFirstUP = true;
				
				if(!isFirstUP)
					break;
				
				
				//tempUpperBudget을 적절히 설정하고 다음 반복을 돌림
				upperLimitBudget = tempUpperLimitBudget;
				tempUpperLimitBudget--;
			}
			else {
				if(upperLimitBudget == tempUpperLimitBudget)
					isFirstUP = false;
				
				if(isFirstUP) {
					upperLimitBudget--;
					break;
				}
				
				//tempUpperBudget을 적절히 설정하고 다음 반복을 돌림
				upperLimitBudget = tempUpperLimitBudget;
				tempUpperLimitBudget++;
				
			}
		}
		
		return upperLimitBudget;
	}
}

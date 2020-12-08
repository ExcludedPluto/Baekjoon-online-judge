

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.Math;

public class closestTwoLiquidToZero {
	int NOfLiquid;
	int []Liquids;
	int zerostValue =2000000000;
	int firstLiquidIndex, secondLiquidIndex;
	int firstPlusIndex = -1;
	
	public closestTwoLiquidToZero() {
		try {
			this.getNLiquid();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	private void getNLiquid() throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		NOfLiquid = Integer.parseInt(in.readLine());
		Liquids = new int[NOfLiquid];
		
		String []str = new String[NOfLiquid];
		str = in.readLine().split(" ");
		
		for(int i = 0; i<NOfLiquid; i++)
			Liquids[i] = Integer.parseInt(str[i]);
		
		in.close();
	}
	
	public void figureClosestTwoLiquid() {
		sumEveryTwoLiquid();
		printTwoLiquid();
	}
	private void sumEveryTwoLiquid() {
		findFirstPlus();
		sumLastTwoMinus();
		if(this.firstPlusIndex == NOfLiquid)
			return;
		if(this.firstPlusIndex < NOfLiquid - 1)
			sumFirstTwoPlus();
		if(this.firstPlusIndex == 0)
			return;
		
		for(int i = 0; i<firstPlusIndex; i++) {
			int tempAbsValue = Math.abs(Liquids[i]);
			int minValue = tempAbsValue - this.zerostValue + 1;
			int tempMaxLeftIndex = -1;
			int tempMinRightIndex = -1;
			for(int j = firstPlusIndex; j<NOfLiquid; j++) {
				if(Liquids[j] >= minValue && Liquids[j] <= tempAbsValue) {
					tempMaxLeftIndex = j;
				}
				else if(Liquids[j] > tempAbsValue) { 
					tempMinRightIndex = j;
					break;
				}
			}
			if(tempMaxLeftIndex != -1) {
				setZerostValueAndIndex(i, tempMaxLeftIndex);
				tempMinRightIndex = tempMaxLeftIndex + 1;
				if(tempMinRightIndex < NOfLiquid)
					if(isZerostValue(Liquids[i] + Liquids[tempMinRightIndex]))
						setZerostValueAndIndex(i, tempMinRightIndex);
				continue;
			}
			if(tempMinRightIndex != -1 && isZerostValue(Liquids[i] + Liquids[tempMinRightIndex]))
					setZerostValueAndIndex(i, tempMinRightIndex);
			if(this.zerostValue == 0)
				return;
		}
	}
	private void findFirstPlus() {
		for(int i = 0; i<this.NOfLiquid; i++)
			if(this.Liquids[i] > 0) {
				this.firstPlusIndex = i;
				return;
			}
		this.firstPlusIndex = NOfLiquid;
		
	}
	private void sumLastTwoMinus() {
		if(firstPlusIndex <= 1)
			return;
		else {
			this.firstLiquidIndex = firstPlusIndex -2;
			this.secondLiquidIndex = firstPlusIndex -1;
			this.zerostValue =  Math.abs(this.Liquids[this.firstLiquidIndex] + this.Liquids[this.secondLiquidIndex]);
		}
	}
	private void sumFirstTwoPlus() {
		int tempValue = this.Liquids[this.firstPlusIndex] + this.Liquids[this.firstPlusIndex+1];
		if(isZerostValue(tempValue)) {
			this.zerostValue = tempValue;
			this.firstLiquidIndex = this.firstPlusIndex;
			this.secondLiquidIndex = this.firstPlusIndex+1;
		}
	}
	private boolean isZerostValue(int value) {
		if(Math.abs(value) < this.zerostValue)
			return true;
		else
			return false;
	}
	private void setZerostValueAndIndex(int i, int j) {
		this.firstLiquidIndex = i;
		this.secondLiquidIndex = j;
		this.zerostValue = Math.abs(this.Liquids[i] + this.Liquids[j]);
	}
	private void printTwoLiquid() {
		System.out.println(Liquids[firstLiquidIndex] + " " + Liquids[secondLiquidIndex]);
	}

}

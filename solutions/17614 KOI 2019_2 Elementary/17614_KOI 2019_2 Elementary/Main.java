
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ThreeSixNineGame test = new ThreeSixNineGame();
		
		for(int i = 1; i <= 1000; i++) {
			if(test.getClappingNum(i) != test.getClappingNum2(i))
				System.out.println(i);
		}
	}

}

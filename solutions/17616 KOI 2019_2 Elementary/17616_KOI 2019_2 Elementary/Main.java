
public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		GradeGenerator test = new GradeGenerator();
		int[] maxAndMinGrade = test.calculateAndReturnMaxAndMinGrade();
		System.out.println(maxAndMinGrade[0] + " " + maxAndMinGrade[1]);
	}

}

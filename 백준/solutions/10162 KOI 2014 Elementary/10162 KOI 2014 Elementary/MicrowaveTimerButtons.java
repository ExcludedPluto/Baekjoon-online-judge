
public class MicrowaveTimerButtons {
	static private int AFiveMinite = 300;
	static private int BOneMinite = 60;
	static private int CTenSecends = 10;
	
	public void miniumPushButtons(int time) {
		int numOfAButton = time/this.AFiveMinite;
		int timeAfterA = time % this.AFiveMinite;
		
		int numOfBButton = timeAfterA / this.BOneMinite;
		int timeAfterB = timeAfterA % this.BOneMinite;
		
		int numOfCButton = timeAfterB / this.CTenSecends;
		int timeAfterC = timeAfterB % this.CTenSecends;
		
		if(timeAfterC != 0)
			System.out.println("-1");
		else
			System.out.println(numOfAButton + " " + numOfBButton + " " + numOfCButton);
	}
}

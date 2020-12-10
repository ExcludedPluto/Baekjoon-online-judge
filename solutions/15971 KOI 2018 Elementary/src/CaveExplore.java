
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.ArrayList;

public class CaveExplore {
	private int numOfRoom;
	private int locationOfARobot;
	private int locationOfBRobot;
	private Tunnel[] tunnel;
	
	public CaveExplore() {
		getProperties();
	}
	
	private class Tunnel {
		int firstNode;
		int secondNode;
		int length;
		
		public Tunnel () {
			this.firstNode = this.secondNode = this.length = 0;
		}
		public Tunnel(int firstNode, int secondNode, int length) {
			this.firstNode = firstNode;
			this.secondNode = secondNode;
			this.length = length;
		}
	}

	private class TunnelHasList extends Tunnel {
		int from;
		ArrayList<Integer> lengthList;
		
		public TunnelHasList(int firstNode, int secondNode, int length) {
			this.firstNode = firstNode;
			this.secondNode = secondNode;
			this.length = length;
			this.from = -1;
			this.lengthList = new ArrayList<Integer>();
		}
			
		public void addLengthList(ArrayList<Integer> lengths) {
			this.lengthList.addAll(lengths);
		}
		public void addSelfLengthList() {
			this.lengthList.add(this.length);
		}
		public ArrayList<Integer> getLengthList() {
			return (ArrayList<Integer>) this.lengthList.clone();
		}
	}

	private void getProperties() {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			String[] str = br.readLine().split(" ");
			numOfRoom = Integer.parseInt(str[0]);
			locationOfARobot = Integer.parseInt(str[1]);
			locationOfBRobot = Integer.parseInt(str[2]);
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		tunnel = new Tunnel[numOfRoom-1];
		try {
			for(int i = 0; i<tunnel.length; i++) {
				String[] str = br.readLine().split(" ");
				tunnel[i] = new Tunnel(Integer.parseInt(str[0]), Integer.parseInt(str[1]), Integer.parseInt(str[2]));
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public int getMinDistanceOfTwoRobot() {
		int [][] tunnelConnected = makeAndReturnTunnelConnected();	//�� ��� 0~N-1�� ����� ����� �ε�����
		
		LinkedList<TunnelHasList> queue = new LinkedList<TunnelHasList>();
		//ù��° �κ��� �ִ� ��忡 ����� ��θ� ť�� ����.
		for(int i = 0; i < tunnelConnected[locationOfARobot-1].length; i++) {
			Tunnel temp = tunnel[tunnelConnected[locationOfARobot-1][i]];
			TunnelHasList temp2 = new TunnelHasList(temp.firstNode, temp.secondNode, temp.length);
			temp2.from = locationOfARobot;
			queue.add(temp2);
		}
		
		//�� ��°���� ��带 ť���� ������, ��忡 �ι�° �κ��� �ִ��� �˻�
		//������ tunnel�� length�� ���� stack�� ����� length�� ��� �˻��Ͽ� ���� �� ���� �����ϰ� �������� ���� ���� �� minDistance�� �ְ� ��ȯ
		//������ from�� �ٸ� ��忡 ����� ��θ� ť�� �ְ�, ���� �� ���� tunnel�� stack�� length�� ���� stack�� ���� ��ο� �ְ� ������.
		ArrayList<Integer> lengths = new ArrayList<Integer>();
		while(!queue.isEmpty()) {
			TunnelHasList tempFromQueue = queue.getFirst();
			queue.removeFirst(); 
			
			tempFromQueue.addSelfLengthList();
			if(tempFromQueue.firstNode == locationOfBRobot || tempFromQueue.secondNode == locationOfBRobot) {
				lengths = tempFromQueue.getLengthList();
				break;
			}
			else {
				int index = tempFromQueue.firstNode != tempFromQueue.from ? tempFromQueue.firstNode-1 : tempFromQueue.secondNode-1;
				int from = tempFromQueue.firstNode != tempFromQueue.from ? tempFromQueue.firstNode : tempFromQueue.secondNode;
				
				for(int i = 0; i < tunnelConnected[index].length; i++) {
					TunnelHasList temp = new TunnelHasList(tunnel[tunnelConnected[index][i]].firstNode,
												tunnel[tunnelConnected[index][i]].secondNode, tunnel[tunnelConnected[index][i]].length);
					if(temp.firstNode == tempFromQueue.from || temp.secondNode == tempFromQueue.from)
						continue;
						
					temp.from = from;
					temp.addLengthList(tempFromQueue.lengthList);
					queue.add(temp);
				}
			}
		}
		
		
	
		//�� ���ϵ� ���� ū �� ������ ����.
		int max = 0;
		int minDistance = 0;
		for(int i : lengths) {
			minDistance += i;
			max = i > max ? i : max;
		}
		return minDistance - max;
	}
	
	private int[][] makeAndReturnTunnelConnected() {
		int []tunnelIndex = new int[this.numOfRoom];
		for(int i = 0; i<tunnelIndex.length; i++)
			tunnelIndex[0] = 0;
		for(int i = 0; i<tunnel.length; i++) {
			tunnelIndex[tunnel[i].firstNode-1]++;
			tunnelIndex[tunnel[i].secondNode-1]++;
		}
		
		
		
		int [][]tunnelConnected = new int[this.numOfRoom][];
		for(int i = 0; i<tunnelConnected.length; i++)
			tunnelConnected[i] = new int[tunnelIndex[i]];
		
		for(int i = 0; i<tunnelIndex.length; i++)
			tunnelIndex[i] = 0;
		for(int i = 0; i<tunnel.length; i++) {
			int firstNodeIndex = tunnel[i].firstNode - 1;
			int secondNodeIndex = tunnel[i].secondNode -1;
			tunnelConnected[firstNodeIndex][tunnelIndex[firstNodeIndex]++] = i;
			tunnelConnected[secondNodeIndex][tunnelIndex[secondNodeIndex]++] = i;
		}
		
		return tunnelConnected;
	}
}

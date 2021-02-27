
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
		int [][] tunnelConnected = makeAndReturnTunnelConnected();	//각 노드 0~N-1에 연결된 통로의 인덱스를
		
		LinkedList<TunnelHasList> queue = new LinkedList<TunnelHasList>();
		//첫번째 로봇이 있는 노드에 연결된 통로를 큐에 넣음.
		for(int i = 0; i < tunnelConnected[locationOfARobot-1].length; i++) {
			Tunnel temp = tunnel[tunnelConnected[locationOfARobot-1][i]];
			TunnelHasList temp2 = new TunnelHasList(temp.firstNode, temp.secondNode, temp.length);
			temp2.from = locationOfARobot;
			queue.add(temp2);
		}
		
		//두 번째부터 노드를 큐에서 꺼내고, 노드에 두번째 로봇이 있는지 검사
		//있으면 tunnel의 length과 현재 stack에 저장된 length를 모두 검사하여 가장 긴 것을 제외하고 나머지는 전부 더한 뒤 minDistance에 넣고 반환
		//없으면 from과 다른 노드에 연결된 통로를 큐에 넣고, 넣을 때 현재 tunnel의 stack에 length를 더한 stack을 다음 통로에 넣고 보낸다.
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
		
		
	
		//다 더하되 가장 큰 건 끝나고 빼자.
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

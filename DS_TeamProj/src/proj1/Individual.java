package proj1;

import java.util.*;

public class Individual implements java.io.Serializable {
	private int nrow;
	private int ncol;

	private int count = 0;// itemlayout의 값으로 정해진 item(즉, 위치가 완전히 결정된 item)이 몇 개 있는지 세는
							// 용도(itemExist[count]에 저장)
	float[][] data; // 연관성을 확인하기 위한 225*225 데이터
	float[][] dataCenter; // 중간([7][7])에 무슨 값이 들어가야할 지 계산할 때 필요한 데이터

	// Cache
	public Individual(ValueTable vt) {

		this.data = vt.getTable();

		this.dataCenter = vt.getTable();
		this.nrow = vt.nrow;
		this.ncol = vt.ncol;

	}

	private int[] itemExist = new int[15 * 15]; // item 중에 결정된 것을 이 곳에 저장
	private int[][] itemlayout = new int[15][15]; // 실제 item들의 배치를 이 곳에 저장

	/* Getters and setters */
	// Use this if you want to create individuals with different gene lengths

	// 실행하기 위한 메소드
	public void run() {

		// data2에 data 값 복사
		float[][] data2 = new float[15 * 15][15 * 15];
		for (int i = 0; i < 15 * 15; i++) {
			for (int j = 0; j < 15 * 15; j++) {
				data2[i][j] = data[i][j];
			}
		}

		// center()를 이용하여 [7][7]의 값 정하고 가운데 위치하고 있는 3*3의 itemlayout만 일단 정해줌
		int center = center();
		int numberOfTimes = 3;
		itemlayout[(this.nrow) / 2][(this.ncol) / 2] = center;
		// 가운데 14

		itemlayout[(this.nrow) / 2 - 1][(this.ncol) / 2] = this.maxOne(center);
		itemlayout[(this.nrow) / 2][(this.ncol) / 2 + 1] = this.maxOne(center);
		itemlayout[(this.nrow) / 2 + 1][(this.ncol) / 2] = this.maxOne(center);
		itemlayout[(this.nrow) / 2][(this.ncol) / 2 - 1] = this.maxOne(center);
		// 십자가 	41
		// 	55	14	60
		// 		213

		itemlayout[(this.nrow) / 2 - 1][(this.ncol) / 2 - 1] = this.maxTwo(
				itemlayout[(this.nrow) / 2][(this.ncol) / 2 - 1], itemlayout[(this.nrow) / 2 - 1][(this.ncol) / 2]);
		itemlayout[(this.nrow) / 2 - 1][(this.ncol) / 2 + 1] = this.maxTwo(
				itemlayout[(this.nrow) / 2 - 1][(this.ncol) / 2], itemlayout[(this.nrow) / 2][(this.ncol) / 2 + 1]);
		itemlayout[(this.nrow) / 2 + 1][(this.ncol) / 2 + 1] = this.maxTwo(
				itemlayout[(this.nrow) / 2][(this.ncol) / 2 + 1], itemlayout[(this.nrow) / 2 + 1][(this.ncol) / 2]);
		itemlayout[(this.nrow) / 2 + 1][(this.ncol) / 2 - 1] = this.maxTwo(
				itemlayout[(this.nrow) / 2][(this.ncol) / 2 - 1], itemlayout[(this.nrow) / 2 + 1][(this.ncol) / 2]);
		// 3*3 완성 	9	41	17
		// 			55	14	60
		// 			112 213 147

		// 나머지 완성
		for (int i = 0; i < this.nrow / 2 - 1; i++) {
			// a,b,c,d를 maxOne(n)을 이용하여 구하는 과정
			// 		a
			// 		9	41	17	b
			// 		55	14	60
			// 	d	112	213	147
			// 				c
			itemlayout[5 - i][6 - i] = this.maxOne(itemlayout[6 - i][6 - i]);
			itemlayout[6 - i][9 + i] = this.maxOne(itemlayout[6 - i][8 + i]);
			itemlayout[9 + i][8 + i] = this.maxOne(itemlayout[8 + i][8 + i]);
			itemlayout[8 + i][5 - i] = this.maxOne(itemlayout[8 + i][6 - i]);

			for (int j = 0; j < numberOfTimes; j++) {
				// a,...,l을 maxTwo(n1, n2)를 이용해 구하는 과정
				// 	l	189	a	b	c
				// 	k	9	4	17	144
				// 	j	55	14	60	d
				// 	119	112	213	147	e
				// 	i	h	g	80	f
				itemlayout[5 - i][7 - i + j] = this.maxTwo(itemlayout[5 - i][6 - i + j], itemlayout[6 - i][7 - i + j]);
				itemlayout[7 - i + j][9 + i] = this.maxTwo(itemlayout[6 - i + j][9 + i], itemlayout[7 - i + j][8 + i]);
				itemlayout[9 + i][7 + i - j] = this.maxTwo(itemlayout[9 + i][8 + i - j], itemlayout[8 + i][7 + i - j]);
				itemlayout[7 + i - j][5 - i] = this.maxTwo(itemlayout[8 + i - j][5 - i], itemlayout[7 + i - j][6 - i]);

			}
			numberOfTimes = numberOfTimes + 2;//1회 시행할 때마다 j값이 2씩 증가
		}
		/* 위치 바꿨을 때 값이 얼마나 많이 바뀌나 알아보기
		int x=itemlayout[1][14];
		itemlayout[1][14]=itemlayout[10][5];
		itemlayout[10][5]=x;
		int y=itemlayout[6][9];
		itemlayout[6][9]=itemlayout[11][6];
		itemlayout[11][6]=y;
		int z=itemlayout[7][7];
		itemlayout[7][7]=itemlayout[3][5];
		itemlayout[3][5]=z;
		int a=itemlayout[8][8];
		itemlayout[8][8]=itemlayout[12][12];
		itemlayout[12][12]=a;
		*/
		
		// itemlayout 출력
		for (int i = 0; i < 15; i++) {
			System.out.print("[");
			for (int j = 0; j < 15; j++) {
				System.out.printf(itemlayout[i][j] + "	");
			}
			System.out.println("]");
		}

		System.out.println("Fittest value: " + this.getObjectiveValue(data2));

	}

	// 중앙값 구하는 메소드
	public int center() {

		float max1 = 0, max2 = 0, max3 = 0, max4 = 0;
		int maxIndex = 0;
		float maxSum[] = new float[15 * 15];// 각 행마다의 max1, max2, max3, max4의 합 저장
		float max = 0;

		for (int i = 0; i < nrow; i++) {
			// 행에서 가장 큰 값 max1에 저장
			for (int j = 0; j < ncol; j++) {
				if (dataCenter[i][j] >= max1) {
					max1 = dataCenter[i][j];
					maxIndex = j;
				}
			}
			data[i][maxIndex] = 0;// i행의 가장 큰 값의 데이터 삭제(삭제하지 않으면 두번째로 큰 값을 구할 때 다시 이 값이 저장되므로)
			// 행에서 두번째로 큰 값 max2에 저장
			for (int j = 0; j < ncol; j++) {
				if (dataCenter[i][j] >= max2) {
					max2 = dataCenter[i][j];
					maxIndex = j;
				}
			}
			data[i][maxIndex] = 0;
			for (int j = 0; j < ncol; j++) {
				if (dataCenter[i][j] >= max3) {
					max3 = dataCenter[i][j];
					maxIndex = j;
				}
			}
			data[i][maxIndex] = 0;
			for (int j = 0; j < ncol; j++) {
				if (dataCenter[i][j] >= max4) {
					max4 = dataCenter[i][j];
					maxIndex = j;
				}
			}
			data[i][maxIndex] = 0;
			maxSum[i] = max1 + max2 + max3 + max4;
		}
		// maxSum[i]를 비교해서 가장 큰 값을 maxIndex에 저장
		for (int i = 0; i < nrow; i++) {
			if (maxSum[i] >= max) {
				max = maxSum[i];
				maxIndex = i;
			}
		}
		itemExist[0] = maxIndex;// 첫번째로 위치가 결정된 item을 itemExist[0]에 저장
		return maxIndex;
	}

	// n과 가장 연관성이 높은 것 찾는 메소드
	public int maxOne(int n) {
		float max = data[n][0];
		int maxIndex = 0;
		// n에 해당하는 item과 가장 연관성이 큰 item을 maxIndex에 저장
		for (int i = 0; i < data[n].length; i++) {
			if (data[n][i] >= max) {
				max = data[n][i];
				maxIndex = i;
			}
		}
		count++;
		itemExist[count] = maxIndex; // 위치가 결정된 item을 itemExist에 저장(count를 이용해서 위치가 결정될 때마다 1씩 증가하도록 설정)

		// 위치가 결정된 item끼리의 연관성 data는 삭제해줌(그래야 그 다음 로직에서 위치가 결정된 item이 다시 사용될 일이 없다)
		for (int i = 0; i < count; i++) {
			data[itemExist[i]][maxIndex] = 0;
			data[maxIndex][itemExist[i]] = 0;
		}

		return maxIndex;
	}

	// n1, n2와 가장 연관성이 높은 것 찾기
	public int maxTwo(int n1, int n2) {

		// data에서 n1행과 n2행을 합하여 sumOfTwo에 저장
		float[] sumOfTwo = new float[15 * 15];
		for (int i = 0; i < data[n1].length; i++) {
			sumOfTwo[i] = data[n1][i] + data[n2][i];
		}

		float max = sumOfTwo[0];
		int maxIndex = 0;
		// sumOfTwo에서 가장 큰 값에 대응되는 item을 maxIndex에 저장
		for (int i = 0; i < data[n1].length; i++) {
			if (sumOfTwo[i] >= max) {
				max = sumOfTwo[i];
				maxIndex = i;
			}
		}

		count++;
		itemExist[count] = maxIndex; // 위치가 결정된 item을 itemExist에 저장

		// 위치가 결정된 item끼리의 연관성 data는 삭제해줌(그래야 그 다음 로직에서 위치가 결정된 item이 다시 사용될 일이 없다)
		for (int i = 0; i < count; i++) {
			data[itemExist[i]][maxIndex] = 0;
			data[maxIndex][itemExist[i]] = 0;
		}

		return maxIndex;
	}

	public int getValue(int row, int col) {
		return itemlayout[row][col];
	}

	public ArrayList<Integer> getGeneArray() {
		ArrayList<Integer> array = new ArrayList<Integer>();
		for (int i = 0; i < this.rsize(); i++) {
			for (int j = 0; j < this.csize(); j++) {
				array.add(this.getValue(i, j));
			}
		}
		return array;
	}

	/* Public methods */
	public int rsize() {
		return nrow;
	}

	public int csize() {
		return ncol;
	}

	public int psize() {
		return nrow * ncol;
	}

	public void setSize(int nrow, int ncol) {
		this.nrow = nrow;
		this.ncol = ncol;
	}

	@Override
	public String toString() {
		String itemlayouttring = "";
		for (int i = 0; i < rsize(); i++) {
			for (int j = 0; j < csize(); j++) {
				itemlayouttring += getValue(i, j);
				itemlayouttring += " ";
			}
			itemlayouttring += "\n";
		}
		return itemlayouttring;
	}

	public float getObjectiveValue(float[][] data) {
		float fitness = 0;
		int nrow = this.rsize();
		int ncol = this.csize();
		System.out.println("nrow:" + nrow + ", ncol:" + ncol);

		for (int i = 1; i < nrow; i++) {
			for (int j = 0; j < ncol; j++) {
				fitness += data[this.getValue(i - 1, j)][this.getValue(i, j)];
			}
		}

		for (int i = 0; i < nrow; i++) {
			for (int j = 1; j < ncol; j++) {
				// System.out.println("nrow:" + nrow + ", ncol:" + ncol + ", i:" + i + ",j:" +
				// j);

				fitness += data[this.getValue(i, j - 1)][this.getValue(i, j)];
			}
		}

		return fitness;
	}

	public void setValue(int row, int col, int value) {
		itemlayout[row][col] = value;
	}

}

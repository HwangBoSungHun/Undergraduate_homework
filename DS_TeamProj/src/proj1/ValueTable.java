package proj1;

import java.util.Random;
public class ValueTable {
	float[][] table;
	int nrow, ncol;
	Random rand = new Random();
	
	public ValueTable(int nrow, int ncol) {
		this.nrow = nrow;
		this.ncol = ncol;
		table = new float[nrow*ncol][nrow*ncol];
	}
	
	public ValueTable(float[][] table) {		
		this.nrow = (int)Math.sqrt(table.length);
		this.ncol = (int)Math.sqrt(table[0].length);
		this.table = table;
		System.out.println("[ValueTable] nrow: " + nrow +", ncol:" + ncol);
	}

	
	public float[][] getTable() {
		return table;
	}


	public float getValue(int index1, int index2) {
		return table[index1][index2];
	}
	
	
	@Override
	public String toString() {
		String geneString = "";
		for (int i = 0; i < nrow*ncol; i++) {
			for (int j = 0; j < nrow*ncol; j++) {
				geneString += getValue(i,j);
				geneString += " ";
			}
			geneString += "\n";
		}
		return geneString;
	}
}

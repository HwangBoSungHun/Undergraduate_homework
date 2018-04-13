import proj1.*;

import java.util.Arrays;

public class TestDriverReadTable2 
{
	public static void main(String[] args) 
	{
		
		float[][] tableinfo = MyTextDataReader2.readFloatValues("table15by15.txt");
		for (int i =0 ; i<tableinfo.length; i++)
		{
			float[] subRow = tableinfo[i];

		}
		
		ValueTable table = new ValueTable(tableinfo);

		Individual individual = new Individual(table);
		
		individual.run();
		
		
		/*
Fittest
1 2 3 
0 4 5 
8 6 7 

Fittest value
134.27852
		*/


		//Read saved myIndividualSol in a file
//		FileInputStream fis = null;
//		ObjectInputStream ois = null;
//		Individual myIndividualSol = null;
//		try{
//
//			// create streams
//			fis = new FileInputStream("myTeam0Sol.dat");
//			ois = new ObjectInputStream(fis);
//
//			// read the object
//			myIndividualSol = (Individual)ois.readObject();
//
//			System.out.println("my solution is restored");
//
//		}catch(Exception e){
//			e.printStackTrace();
//
//		}finally{
//			// close the streams
//			if(fis != null) try{fis.close();}catch(IOException e){}
//			if(ois != null) try{ois.close();}catch(IOException e){}
//		}
//
//		System.out.println("myIndividualSol: ");
//		System.out.println("" + myIndividualSol);
//
//		float myScore = myIndividualSol.getObjectiveValue(table);
//		System.out.println("myScore: " + myScore);


	}
}
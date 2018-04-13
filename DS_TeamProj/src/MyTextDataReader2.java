import java.util.Arrays;
import java.util.ArrayList;
import java.io.*;


public class  MyTextDataReader2
{
	static int INITIAL_CAPACITY = 3;

	public static void main(String[] args) 
	{
		float[][] vals = readFloatValues("table15by15.txt");
		for (int j=0; j < vals.length ; j++ )
		{
			System.out.println("" + Arrays.toString(vals[j]));
		}

	}



  public static float[][] readFloatValues(String fileName) {
	  ArrayList<String> mylines = new ArrayList<String>();
	  int[] MyData = new int[INITIAL_CAPACITY];
	  int HowManyLines = 0;
	  float[][] inputData = null;
    try{	
      FileInputStream fstream = new FileInputStream(fileName);
      BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
      String strLine;
      
      //Read File Line By Line
      while ((strLine = br.readLine()) != null) {
		  mylines.add(strLine);
		  //System.out.println(""+strLine);
		  HowManyLines++;
      }
      //System.out.println("\n HowManyLines: "+HowManyLines);
	  //String[] varnames = getStringFromOneLine(mylines.get(0));
	  //int HowManyVars = varnames.length;
	  int HowManyVars = getFloatFromOneLine(mylines.get(0)).length;
	  //System.out.println("\n HowManyVars: "+HowManyVars);
	  inputData = new float[HowManyLines][HowManyVars];
	  
	  for (int k=0; k < HowManyLines ; k++ )
	  {
		  //System.out.println("\n mylines.get("+k+"): "+mylines.get(k));
		  //getDoubleFromOneLine(mylines.get(k))
		  //System.out.println("" + Arrays.toString(getDoubleFromOneLine(mylines.get(k))) );
		  inputData[k] = getFloatFromOneLine(mylines.get(k));
	  }

      //Close the input stream
      fstream.close();
    } catch (Exception e){//Catch exception if any
      System.err.println("Error: " + e.getMessage());
	  e.printStackTrace();
    }

	//return Arrays.copyOf(MyData, HowMany);
	return inputData;
  }


    public static float[] getFloatFromOneLine(String myLine) {
        //String myLine = "3 8 10   60  12 18";
        String myDelimiter = "[\\s]+";
        //System.out.println("myDelimiter:" + myDelimiter);
        String[] myTokens = myLine.split(myDelimiter);
		float[] curValues = new float[myTokens.length];
        for (int k = 0; k < myTokens.length; k++) {
            //System.out.println("" + myTokens[k]);
			curValues[k] = Float.parseFloat(myTokens[k]);
        }
		return curValues;
    }

    public static String[] getStringFromOneLine(String myLine) {
        //String myLine = "3 8 10   60  12 18";
        String myDelimiter = "[\\s]+";
        //System.out.println("myDelimiter:" + myDelimiter);
        String[] myTokens = myLine.split(myDelimiter);
		return myTokens;
    }

}

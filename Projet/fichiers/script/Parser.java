import java.io.*;
import java.net.*;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;




class Parser{
    public static double avgTime;
    public static double avg;

    static private String name = "test.data";

    static double averageRow(int index) throws IOException{
        BufferedReader br = new BufferedReader(new FileReader(name));
        int tmpTime = 0;
	try {

	    for(int i = 0; i<10; i++){
		StringBuilder sb = new StringBuilder();
		String line = br.readLine();
		
		String delims = "[ ]+";
		String[] tokens = line.split(delims);
				
		//System.out.println(Integer.parseInt(tokens[1]));

		tmpTime += Integer.parseInt(tokens[0]);
	    }
	    avgTime = tmpTime/100.0;

        } finally {
            br.close();
        }
	return avgTime;
    }


    public static void main(String args[]) throws IOException{
	averageRow(0);
	System.out.println("Moyenne:"+ avgTime);
    }
}

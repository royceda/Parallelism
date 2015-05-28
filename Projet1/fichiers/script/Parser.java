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
        double tmpTime = 0;
	double tmp = 0;
	try {
	    String line;
	    while((line = br.readLine()) != null){
		//System.out.println(line);
		line = line.replaceAll("\\s+"," ");
		//System.out.println(line);
		String[] tokens = line.split(" ");
				
		//System.out.println(tokens[0]);
		//System.out.println(tokens[1]);
		//System.out.println(tokens[2]);
		//System.out.println(tokens[3]);
		tmpTime += Double.valueOf(tokens[2]);
		tmp += Double.valueOf(tokens[3]);
		System.out.println("tmp: "+tmp);
		System.out.println("tmp: "+tmpTime);
	    }
	    avgTime = tmpTime/100.0;
	    avg = tmp /100.0;

        } finally {
            br.close();
        }
	return avgTime;
    }


    public static void main(String args[]) throws IOException{
	averageRow(0);
	if (args.length == 0)
	    System.out.println(avgTime +" "+ avg);
	if (args.length == 1)
	    System.out.println(args[0]+" "+avgTime +" "+ avg);
    }
}

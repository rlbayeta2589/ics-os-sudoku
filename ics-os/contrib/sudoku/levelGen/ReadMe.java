import java.util.*;
import java.io.*;

public class ReadMe{
	public static void main(String[] args) {
		int in =1;

		File file = new File("../hard/hard"+args[0]+".txt");			//read input file
		try{
			Scanner scan = new Scanner(file);
				
			System.out.print("\t\t\t\tassignValues(board,\n");


			while(scan.hasNextLine()){

			if(in ==1 || in==4 || in ==7){
				System.out.print("\t\t\t\t\t");
			}
				String num = scan.nextLine();

				for(int i=0; i < num.length() ; i++){
					System.out.print(num.charAt(i)+",");
				}
				
			if(in++%3==0){
				System.out.println();
			}else {
				System.out.print(" ");
			}


			}
			System.out.println("\t\t\t\t);");
		}catch(Exception e){
			System.out.println("\nError Reading File Content!");
		}

	}
}
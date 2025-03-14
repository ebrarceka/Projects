import java.util.Scanner;

public class StringAnalyzer {

	public static void main(String[] args) {
		// Problem : Operations on a given string using methods.
		//Ebrar Çelikkaya, 150123067
		
		//creating a string to condition our loop,
		String mainString =""; 
		
		while (!(mainString.equalsIgnoreCase("exit")||mainString.equalsIgnoreCase("quit"))) {// as long as input is anything other than these strings , our loop will iterate.
		System.out.print("Welcome to our String Analyzer Program.\r\n"
				+ "1. Count number of chars\r\n"
				+ "2. Print the words in a sentence\r\n"
				+ "3. Delete substring\r\n"
				+ "4. Replace substring\r\n"
				+ "5. Sort characters\r\n"
				+ "6. Hash code of a string\r\n"
				+ "Please enter your menu choice:\n");
	Scanner scan = new Scanner (System.in);
	 mainString = scan.nextLine();
	
		switch (mainString) {
		
		case "1": // invokes number of characters in a string method 
			
			 System.out.println("Enter an input string:");
		String str = scan.nextLine();
		    
		     System.out.print("Enter an input char:");
		String charString = scan.nextLine();
		char ch = charString.charAt(0);
		     
		     System.out.print("The number of "+ ch+" characters in "+ str+ " string is "+ numOfChars(str,ch));
		     System.out.println(); break;
		
		case"2": // invokes printing the words in a sentence method
			
			System.out.println("Enter an input string:");
	     str = scan.nextLine();
			
		    System.out.print("The output is : " );
	     printWords(str);
		  
	        System.out.println();break;
			
		case "3": // invokes deleting a given substring method
			
			System.out.println("Enter an input string:");
	     str = scan.nextLine();
		    
	        System.out.println("Enter a substring:");
		 String subStr= scan.nextLine();
		    
		    System.out.println("Enter a type(0 or 1):");
		 int type = scan.nextInt();
		   
		    System.out.println( delete(str, subStr ,type)); break;
		   
		case "4": //invoking replacing method
		
			System.out.println("Enter an input string:");
		  str = scan.nextLine();
		    
		    System.out.println("Enter the first substring:");
		  subStr= scan.nextLine();
		     
		    System.out.println("Enter the second substring:");
		  String subStr1 = scan.nextLine();
		     
		    System.out.println(replace(str,subStr,subStr1)); break;
		     
		case "5": //invoking sorter methods (and my respect to whoever invented arrays...)
			
			System.out.println("Enter an input string:");
		  str = scan.nextLine();
		    
		    System.out.println("Enter a type(0 or 1):");
		  type = scan.nextInt();
		    
		    System.out.println(sortChars(str,type)); break;
		    
		    
		case "6": //invoking hashcode method
			
			System.out.println("Enter an input string:");
		  str = scan.nextLine();
		   
		    System.out.println("Enter a value for b:");
		  int b = scan.nextInt();
		    
		    System.out.println("The hashcode of your string is : " + hashCode(str,b)); break;
		 
		default : //program terminating message
		if( mainString.equalsIgnoreCase("exit")||mainString.equalsIgnoreCase("quit"))
			System.out.println("Program ends , adios.");
	}
		}
	
		}
	     
	//first method
	public static int numOfChars(String str , char ch){ 
		
		int count = 0; // keeping the number of character ch
		
		   for (int i =0 ; i < str.length(); i++){
	  
			   if(ch == str.charAt(i))
		
				   count++;
		    }
		
		   return count ; 

	}
    //second method
	public static void printWords ( String str){

		for (int i =0; i<str.length(); i++){
			//printing the letters & digits , moving the cursor to the next line for other characters
		   if (str.charAt(i)<='Z' && str.charAt(i)>='A')
		System.out.print(str.charAt(i)); 
		
		   else if (str.charAt(i)<='z' && str.charAt(i)>='a')
		System.out.print(str.charAt(i)); 
		
		   else if (str.charAt(i)<='9' && str.charAt(i)>='0')
		System.out.print(str.charAt(i)); 
		
		   else 
		System.out.println();


		}

	}
    //third method
	public static String delete (String str , String subStr, int type) {

			String newString =""; //we'll return this string 
			
			double [] indexKeeper=new double[str.length()] ; //we 'mark' the index of the first char. of subStr via this array we made.
			
			if (type==0) {
		    
				int i;
			
				for ( i=0 ; i<=str.length()-subStr.length();i++) {
				
					String a = str.substring(i,i+subStr.length());
				
				if(a.equals(subStr)) 
					  break; // we only need the index of the first character of subStr for type 0 , so we immediately exit the loop when we find it 
			}
			 indexKeeper[i]=i+1;
			   
		   for( i =0 ; i<str.length();i++){
				
			   if(indexKeeper[i]==i+1) { //we find our marks, delete required length.
				
				   for(int j=0 ; j<subStr.length();j++)
					newString+="";
				   
			     	i=i+subStr.length()-1; // we move the i value as much as the subStr length , so we don't make duplicated deletion.
				}
				else {

					newString+=str.charAt(i);
				}
			}
			
		}
		
		if(type==1) {// same procedure with type 0 except for break command since we need all the first indexes of subStr.
			
			 for (int i=0 ; i<=str.length()-subStr.length();i++) {
				
				 String a = str.substring(i,i+subStr.length());
				
				 if(a.equals(subStr)) {
			   
					 indexKeeper[i]=i+1; 
				}
				
			}
		   for(int i =0 ; i<str.length();i++){
				
			   if(indexKeeper[i]==i+1) {
				
				   for(int j=0 ; j<subStr.length();j++)
					newString+="";
				
				   i=i+subStr.length()-1;
				}
				else {
					newString+=str.charAt(i);
				}
		   }
			
		}
	   return newString;
	}
	//fourth method
	public static String replace(String str, String subStr1 , String subStr2) {
			
		String replacedString =""; // return string
				
		  double [] indexKeeper=new double[str.length()] ; // same logic as method 3 , we mark the indexes.
				for (int i=0 ; i<=str.length()-subStr1.length();i++) {
					
					String a = str.substring(i,i+subStr1.length());
					
					if(a.equals(subStr1)) {
				   
						indexKeeper[i]=i+1;
					}
					
				}
			   for(int i =0 ; i<str.length();i++){
					if(indexKeeper[i]==i+1) {
					
						for(int j=0 ; j<subStr2.length();j++)
						replacedString+=subStr2.charAt(j);
					
						i=i+Math.max(subStr1.length(), subStr2.length())-1; //moving the i value accordingly.
					}
					else {
						replacedString+= str.charAt(i);
					}
				}
				return replacedString;
	}
	//fifth method	
	public static String sortChars (String str, int type) {
		
		String sortedString ="";
		
		if(type==0) {
			
			char[]stringToSort = new char[str.length()]; 
			    
			    for(int i =0 ; i<str.length();i++)
			    	stringToSort[i]= str.charAt(i); //turning our string to a char array,
			
			
			for (int i =0 ; i<str.length(); i++) {
			
				int sorter =i; // this variable will do the sorting from charAt(i) to the first index.
				
				char y = stringToSort[i]; //we'll change the i with sorter later on, so we need a variable.
				
				while ((sorter>0) && (stringToSort[sorter-1]>y)) { //carrying the biggest value to the end of array by arranging till [i] each iteration.
					stringToSort[sorter]= stringToSort[sorter-1];
					sorter--;
				}
				stringToSort[sorter]=y;
				
			}

			for( int i=0;i<str.length();i++)
		    	sortedString+=stringToSort[i]; // building our new string
			}
			
			
			if(type==1) {
			
		    String lowerCases = "";	
			String upperCases ="";
			String digits= "";
			String otherChars="";
			
		for (int i = 0; i<str.length();i++) {
			
			char ch = str.charAt(i); // assigning the value to a char just to keep the expressions short
			//sorting by the character type , uppercase , lowercase , digits and the others
			if(Character.isLetter(ch)) {
				
				if(ch<='Z' && ch>='A')
		         	upperCases+=ch;
				 
				if(ch<='z' && ch>='a')
					lowerCases+=ch;
			}
			
			if(Character.isDigit(ch)) {
				digits+=ch;
			}
			else if(!(Character.isDigit(ch)||Character.isLetter(ch)))
				otherChars+=ch;
			
		}
		lowerCases = sortChars(lowerCases,0); // using the type 0 of this method , we sort these char types separately 
		upperCases = sortChars(upperCases,0);
		digits = sortChars(digits,0);
		otherChars = sortChars(otherChars,0);
		
		sortedString = lowerCases + upperCases + digits + otherChars; //building our final string
		
			}
			return sortedString;

   }
   // sixth method
	public static int hashCode(String str , int number) {
			
		int num= 0;// an intermediate value , we will add this to result in every iteration.
			
		int result= 0 ; // the final hashcode value we want to return.
			
		      for (int i=str.length()-1,j = 0;i>=0 && j<str.length();i--,j++) { // these local variables are only used to apply formula, hence the names i and j.
				
					num = str.charAt(j)*(int)(Math.pow(number ,i)); // the formula 
				  
				 result +=num;
			  }
				
			return result;
			
			
  }
		}
			
		
			 


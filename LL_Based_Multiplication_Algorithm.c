#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

			 /* Implementation of an LL based multiplication algorithm,
				150123067 Ebrar Çelikkaya*/
 
typedef struct data {
 	int num ;
    int isFP; /*isFP is a marker of the start of decimal parts, */
 	struct data* next ;
 	
 } Data;
 
 Data* addNode (Data** head , int value, int isFP); /*adds the values to the end of given link list.*/
 Data* multiply ( Data** multiplier , Data ** multiplicand ,FILE* fOut); /*multiplies two numbers stored in linked lists digit by digit
 																		 ,returns the first node of the result.*/
 void printList(Data** head, FILE* fOut); /*prints the given linked list to both console and an output file*/
 int isNum ( char ch); /*checks whether the given character is a number*/
 Data *reverseList ( Data** head);/*reverses the given list , returns the head node*/
 void adjustFP(Data**multiplicand , Data**multiplier, Data **result); /*inserts the floating point based on multiplicand & multiplier*/



 Data* addNode (Data** head , int value, int isFP){
 		
		 Data *newNode  = (Data*)malloc(sizeof(Data));

 		if(newNode ==NULL){
 		puts("no space available.");
 		return ;
 		}

 	newNode->num = value;
    newNode->next= NULL; 
	newNode ->isFP=isFP;
	

	 	newNode->next= *head;
	 	*head=newNode; /*storing the digits in a stack-like way for convenience, it will make the multiplying process more comprehesinble*/

    
     return *head;
 }

	
Data* multiply(Data** multiplier, Data** multiplicand, FILE* fOut) {
    Data* result = NULL; 
    Data* multiplierPtr = *multiplier;
    Data** tempResult = &result;

  
    while (multiplierPtr != NULL) {
       
	    int carry = 0;
        Data* multiplicandPtr = *multiplicand;
        Data* currentResult = *tempResult;


        while (multiplicandPtr != NULL) {
           
		    int product = multiplierPtr->num * multiplicandPtr->num + carry;  /* works the same way with the multiplication on a paper , adding the carry*/

            if (currentResult == NULL) {
              
                currentResult = (Data*)malloc(sizeof(Data));
                currentResult->num = 0;
                currentResult->next = NULL;
                *tempResult = currentResult;  /* Link tempResult to the new node.the connection between currentResult,tempResult and result pointer
				                              should never be broken since they all point to the result linked list.*/
            }

            
            currentResult->num += product; /* add product to the currentResult  */

          
            carry = currentResult->num / 10;  /* update carry for the next iteration */
            currentResult->num %= 10;         /*the one digit node we need to keep*/


            if (currentResult->next == NULL && (multiplicandPtr->next != NULL || carry > 0)) {/*we need to handle the possible carry once , since the highest value 
            																				  that can be obtained by multiplying single-digit numbers -and adding the highest carry
																							   is a two-digit value*/
                
                Data* newNode = (Data*)malloc(sizeof(Data));
                newNode->num = carry;  
                newNode->next = NULL;
                currentResult->next = newNode;
               
                carry = 0;  /*carry is handled. */
            }

            currentResult = currentResult->next;
            multiplicandPtr = multiplicandPtr->next;
        
        
        
    }

        /*tempResult plays the constant one propagation role, so it needs to be updated as t = t->next (if next is null , a new node should be added)*/
        if ((*tempResult)->next == NULL) {
            
            Data* newNode = (Data*)malloc(sizeof(Data));
            newNode->num = 0;
            newNode->next = NULL;
            (*tempResult)->next = newNode;
        }

        
        tempResult = &(*tempResult)->next;
        multiplierPtr = multiplierPtr->next;
    }
    
    return result;
}



void adjustFP(Data**multiplicand , Data**multiplier, Data **result){
 /*mathematically , the sum of how many digits multiplicand and multiplier have after the decimal point determines the place of 
 decimal point in result.instead of summing up , we iterate through both of them along with result till we see the decimal point .*/

 Data *temp = (*result)->next; /*the algorithm puts the isFP flag to the next digit after the point. so this extra move is needed to print it out correctly.*/
 Data *tempMcand=*multiplicand;
 Data *tempMplier = *multiplier;
 
  while (tempMcand!=NULL){ /*iterates till it sees the FP mark in multiplicand */
  	if(!tempMcand->isFP){
  		(temp) =(temp)->next; 
	  }
  	else {
  		break;
	  }
  	tempMcand=tempMcand->next;
  	
  }/*same process for multiplier,continues iterating through result.*/
   while ((tempMplier)!=NULL){ 
  	if(!(tempMplier)->isFP){
  		(temp) =(temp)->next;
	  }
  	else {
  		break;
	  }
  	tempMplier=tempMplier->next;
  	
  }
  
  (temp)->isFP =1; /*puts the floating point flag.*/
  
}


 void printList(Data** head, FILE* fOut) {
 	
 	Data * temp = reverseList(head); /*for convenience , all the storing and decimal point manipulation processes are run through reversed versions of mp.cand and mp.lier. 
 									 so we reverse them before printing them out .*/
 
   while ( temp !=NULL){
   	 
	  if(!temp->isFP){
   		printf("%d",temp->num);
   	    fprintf(fOut,"%d",temp->num);
	   }
	  else {
	   	printf(".%d",temp->num);
   	    fprintf(fOut,".%d",temp->num);
	   	
	   }
	   
   	temp = temp->next;
   	
   	
   }
   printf("\n");
   fprintf(fOut,"\n");
       
    }
   

 
 
 
 
 int isNum ( char ch){ 
 	
 	return ( ch<='9'&& ch>='0');
 }
 
 
 
 
 Data *reverseList ( Data** head){ 
 	 
 	 Data *newList =NULL;
 	 Data *temp = *head;
 	 
 	while ( temp !=NULL){ 
 		 addNode(&newList,temp->num,temp->isFP);
 		 temp = temp->next;

	 }
 	return newList;
 	
 	
 }
 
 
 
 
 
 int main (void){
 	
 	clock_t start, end;
 	start = clock();

 	
 	
 	int isMultiplier =0; /* this will be used to switch the storing from multiplicand (head1) to multiplier( head2) */
 	int isFP=0;  /* this is a mark for placing the decimal point.*/
 	char ch ;
 	
 	Data *head1 =NULL;
 	Data *head2 =NULL;
    Data **temp = &head1; /* a temporary head to keep the storing process continuous.*/
    
 	FILE *fPtr = fopen("150123067_prj1_input.txt","r");
 	FILE *fOut = fopen("150123067_prj1_output.txt","w");
 	
 	if(fOut ==NULL || fPtr ==NULL ){
 		puts(" Output file can't be generated / Input file can't be accessed.'");
	 }
 	if (fOut !=NULL){
 		puts ("Output file is generated.");
	 }
	
	 
 	while ((ch = fgetc(fPtr))!= EOF){
 		 
 		 if(ch== '\n'|| ch==' '){ /* means that multiplicand is stored fully*/
 		 	
 		 	if(!isMultiplier){	
			  
				isMultiplier =1;
			 	isFP=0;
		
 		 		temp = &head2;
				
			  }
		  	}
 			
 			else if(ch == '.'){
 				isFP = 1;
 		
			 }
			 
			  
			if (isNum(ch)&&!isFP){
			 	addNode(temp,ch-'0',0);
			
			 }
			 else if(isNum(ch)&&isFP){
			 	addNode(temp,ch-'0',1); 
			 	isFP=0; /*after a point is inserted , we reset the FP marker to 0 so we can keep scanning all possible points.*/
			 	
			 }
			 

          
		 
	 }
 


 printList (&head1,fOut); 
 printList (&head2,fOut);
 
 
 Data *result = multiply( &head1, &head2,fOut );

  adjustFP(&head1, &head2, &result);
 
  printf("ans=\n");
  fprintf(fOut,"ans=\n");

 printList(&result,fOut);
 

 
end =clock();
  
 double exeTime = ((double)(end-start))/CLOCKS_PER_SEC; 
 
 fprintf(fOut,"Execution Time : %.9f", exeTime);
 
 	fclose(fOut);
 	fclose(fPtr);
 
 
 }
 
 

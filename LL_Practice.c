//Ebrar Çelikkaya 150123067 Assignment 4 , Problem 1
//Building two linked lists based on a keyword and a count , in lexicographical and descending order respectively.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct strct {
    char str[25];
    int count;
    struct strct *nextAlpha;
    struct strct *nextCount;
} String;

typedef String* StringPtr;

int isLXCBefore(char *str1, char *str2) { // This method checks whether the first word comes before the second alphabetically.
    return strcmp(str1, str2) <0; // strcmp computes char1-char2 char. by char. , useful for this occasion
}

void inc (StringPtr *headAlpha, StringPtr *headCount, char* key) {
    StringPtr currentPtr = *headAlpha;
    StringPtr prevPtr = NULL;
    
    // search for the key in the alphabetically linked list
    while (currentPtr != NULL) {
        if (strcmp(currentPtr->str, key) == 0) {
            currentPtr->count++;
             // now that its count is incremented , we need to update its place in counter.
             //step 1. cut the linkage
            StringPtr cCurrentPtr = *headCount;
            StringPtr cPrevPtr = NULL;
            while (cCurrentPtr != NULL) {
                if (cCurrentPtr == currentPtr) {
                    if (cPrevPtr != NULL) {
                        cPrevPtr->nextCount = cCurrentPtr->nextCount;
                    } else {//if we're removing the only element of list,
                        *headCount = cCurrentPtr->nextCount;
                    } //currentPtr is not linked anymore , but keeps its data.
                    break;
                }
                cPrevPtr = cCurrentPtr;
                cCurrentPtr = cCurrentPtr->nextCount;
            }
            
            // step 2. reinsert currentPtr to the list.
            cCurrentPtr = *headCount;
            cPrevPtr = NULL;
            while (cCurrentPtr != NULL && cCurrentPtr->count > currentPtr->count) {
                cPrevPtr = cCurrentPtr;
                cCurrentPtr = cCurrentPtr->nextCount;
            }
            if (cPrevPtr == NULL) {// if the element is first,
                currentPtr->nextCount = *headCount;
                *headCount = currentPtr;
            } else {
                currentPtr->nextCount = cPrevPtr->nextCount;
                cPrevPtr->nextCount = currentPtr;
            }
            return; 
        }
        prevPtr = currentPtr;
        currentPtr = currentPtr->nextAlpha;
    }

 // if we never returned to the caller , element does not exist. we need to add it and set the count to 1.
    StringPtr newPtr = (StringPtr) malloc(sizeof(String));
    if (newPtr != NULL) {
        strcpy(newPtr->str, key);
        newPtr->count = 1;
      
        if (prevPtr == NULL) { // if the list is empty,
            newPtr->nextAlpha = *headAlpha;
            *headAlpha = newPtr; 
        } else { 
            currentPtr = *headAlpha; //traverse to find its place in lexicographic list
            prevPtr = NULL;
            while (currentPtr != NULL && !isLXCBefore(key, currentPtr->str)) {
                prevPtr = currentPtr;
                currentPtr = currentPtr->nextAlpha;
            }
            if (prevPtr == NULL) {//means current is null from the start , so the list is either empty or were adding to the headside,
                 newPtr->nextAlpha = *headAlpha;
                *headAlpha = newPtr; //*headAlpha is a fixed address we get from the caller. this way we connect them as **headAlpha->newPtr->*headAlpha.
            } else {//insertion to middle / end.
                newPtr->nextAlpha = prevPtr->nextAlpha;
                prevPtr->nextAlpha = newPtr;
            }
        }
        
        // checking new pointer in to the counter linked list.
        StringPtr cCurrentPtr = *headCount;
        StringPtr cPrevPtr = NULL;
        
        while (cCurrentPtr != NULL && cCurrentPtr->count > newPtr->count) {
            cPrevPtr = cCurrentPtr;
            cCurrentPtr = cCurrentPtr->nextCount;
        }
        
        if (cPrevPtr == NULL) {
        	newPtr->nextCount= *headCount;
            *headCount = newPtr; //this assignment order enables us adding the new items to list correcly.
            
        } else {
            newPtr->nextCount = cPrevPtr->nextCount;
            cPrevPtr->nextCount = newPtr;
        }
    } else {
        puts("Memory allocation failed.");
    }
}


void dec(StringPtr *headAlpha, StringPtr *headCount, char* key){
	 StringPtr currentPtr = *headAlpha;
     StringPtr prevPtr = NULL;
    
    // search for the key in the alphabetically linked list
    while (currentPtr != NULL) {
        if (strcmp(currentPtr->str, key) == 0) {
            currentPtr->count--;
            if(currentPtr->count==0){
            	break;
			}
			  // similar to inc, we have to update its place in count list(if not count==0). first we cut the link,
            StringPtr cCurrentPtr = *headCount;
            StringPtr cPrevPtr = NULL;
            while (cCurrentPtr != NULL) {
                if (cCurrentPtr == currentPtr) {
                    if (cPrevPtr != NULL) {
                        cPrevPtr->nextCount = cCurrentPtr->nextCount;
                    } else {
                        *headCount = cCurrentPtr->nextCount;
                    }
                    break;
                }
                cPrevPtr = cCurrentPtr;
                cCurrentPtr = cCurrentPtr->nextCount;
            }
            
            // & we fix the link accordingly.
            cCurrentPtr = *headCount;
            cPrevPtr = NULL;
            while (cCurrentPtr != NULL && cCurrentPtr->count > currentPtr->count) {
                cPrevPtr = cCurrentPtr;
                cCurrentPtr = cCurrentPtr->nextCount;
            }
            if (cPrevPtr == NULL) {
                currentPtr->nextCount = *headCount;
                *headCount = currentPtr;
            } else {
                currentPtr->nextCount = cPrevPtr->nextCount;
                cPrevPtr->nextCount = currentPtr;
            }
            return; 
        }
        prevPtr = currentPtr;
        currentPtr = currentPtr->nextAlpha;
    }

	//if we found the key && its counter is set to zero , we need to remove it.
 if (currentPtr != NULL ) {
       
        if (prevPtr == NULL) {//first element ,
            *headAlpha = currentPtr->nextAlpha;
            
        } else {// middle /end,
            prevPtr->nextAlpha = currentPtr->nextAlpha;
            
        }

        // adjusting the count list,
      StringPtr cCurrentPtr = *headCount;
        StringPtr cPrevPtr = NULL;

        while (cCurrentPtr != NULL) {
            if (cCurrentPtr == currentPtr) {
                if (cPrevPtr == NULL) {
                	
                    *headCount = cCurrentPtr->nextCount;
                } else {
                    cPrevPtr->nextCount = cCurrentPtr->nextCount;
                }
                break;
            }
            cPrevPtr = cCurrentPtr;
            cCurrentPtr = cCurrentPtr->nextCount;
        }

        free(currentPtr); 
     

}

}

char * getMinKey (StringPtr head){//in a decreasing-order list, simply returns the last element if exists.
	StringPtr currentPtr = head ;
	StringPtr prevPtr =NULL;
	
	while(currentPtr !=NULL ){//iterate to the last element.
		prevPtr =currentPtr;
		currentPtr=currentPtr->nextCount;
	}
	if(prevPtr ==NULL){// the list is empty.
		return "";
	}
	else {
		return prevPtr->str;
	}
}

char*getMaxKey(StringPtr head){//in a decreasing-order list , returns the first element if exists.
	if(head !=NULL){
		return head->str;
	}
	else{
		return "";
	}
	
}

char* printList(StringPtr head , int type){//prints the list in the requested type.
	StringPtr currentPtr = head;

	switch(type){
		case 1 : // lexicographical order
		puts("\nThe list in alphabetical order :");
		while(currentPtr !=NULL){
			
			printf("%s(%d)-->",currentPtr->str, currentPtr->count);
	
			currentPtr = currentPtr->nextAlpha;
			
		}
		puts ("NULL\n");
		break;
		case 2: // count order
			puts("\nThe list in descending order :");
				while(currentPtr !=NULL){
			printf("%s(%d)-->",currentPtr->str, currentPtr->count);
		
			currentPtr = currentPtr->nextCount;
			
		}
		puts ("NULL\n");
			break;
			
	}
	
	
	
}

int main(void) {
    StringPtr headAlpha = NULL;
    StringPtr headCount = NULL;
    char str[25];

   
    FILE *fPtr = fopen("input.txt", "r");
    if (fPtr == NULL) {
        puts("File cannot be opened.");
        return 1;//unexpected return
    }

   
    while (fscanf(fPtr, "%24s", str) == 1) {  // fscanf returns the number of words scanned successfully. to scan word by word , we use ==1.
    
        if (strcmp(str, "inc") == 0) {//when the first word is inc ,
            if (fscanf(fPtr, "%24s", str) == 1) {  //we scan the second & send it to related method.
                inc(&headAlpha, &headCount, str);
       
     }
     //similar logic implemented for the rest of keywords.
     
        } else if (strcmp(str, "dec") == 0) {
            if (fscanf(fPtr, "%24s", str) == 1) { 
                dec(&headAlpha, &headCount, str);
            } 
            
        } else if (strcmp(str, "getMaxKey") == 0) {
            printf("%s\n", getMaxKey(headCount));
            
            
        } else if (strcmp(str, "getMinKey") == 0) {
            printf("%s\n", getMinKey(headCount));
            
            
        } else if (strcmp(str, "printList") == 0) {
            if (fscanf(fPtr, "%24s", str) == 1) {
                int type = atoi(str);
                if (type == 1) {
                    printList(headAlpha, 1);
                } else if (type == 2) {
                    printList(headCount, 2);
                } 
            } 
        } 
		
		else {
            puts("error.");
        }
    }

    fclose(fPtr); //closes the file.

}




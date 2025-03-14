#include <stdio.h>

//Ebrar Çelikkaya , 150123067 , finding the longest increasing path in a 2d array with DFS search 

void readArray(int row, int column, int arr[row][column]) {// a basic for-loop to scan the matrix
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

void findLongestPath(int row, int column, int arr[row][column], int *maxLength, int longestPath[]) {

    int length=1;// the temporary length. every cell is esentially a path of length 1 , hence the initialization with 1.
    int path[row * column];// temporary path array that we keep the current path of numbers
    
    int i, j;
    for (i = 0; i < row; i++) {//checking every possible path for every cell.
        for (j = 0; j < column; j++) {
        	path[0]=arr[i][j];//every cell is the first member of its increasing path.
            forward(i, j, row, column, arr ,length, maxLength, path,longestPath);//forward is a recursive function that goes forward in all possible paths from a cell.
        }
    }
    
    
}


void forward(int currentRow, int currentCol, int row, int column, int arr[row][column], int length, int *maxLength, int path[], int longestPath[row * column]) {
    //the operations we need to exert on each cell. this method works through all the possible paths since its recursed everytime a neighbouring cell is greater than the current cell.
	
    int num = arr[currentRow][currentCol]; 

    if (length > *maxLength) {//if the length of the current path is greater than the max value we keep , we update it here.
        *maxLength = length;
        int k;
        for (k = 0; k < length; k++) {// copies the elements of temporary array to our final array , the longest path.
            longestPath[k] = path[k];
        }
    }

    if (currentRow + 1 < row && arr[currentRow + 1][currentCol] > num) {// adding the cell under the current one to our path, if it exists & greater than current.other ifs check the other three possibilities.
        path[length] = arr[currentRow + 1][currentCol];
        forward(currentRow + 1, currentCol, row, column, arr, length + 1, maxLength, path, longestPath);
    }
    if (currentRow - 1 >= 0 && arr[currentRow - 1][currentCol] > num ) {
        path[length] = arr[currentRow - 1][currentCol];
        forward(currentRow - 1, currentCol, row, column, arr, length + 1, maxLength, path, longestPath);
    }
    if (currentCol + 1 < column && arr[currentRow][currentCol + 1] > num ) {
        path[length] = arr[currentRow][currentCol + 1];
        forward(currentRow, currentCol + 1, row, column, arr, length + 1, maxLength, path,  longestPath);
    }
    if (currentCol - 1 >= 0 && arr[currentRow][currentCol - 1] > num ) {
        path[length] = arr[currentRow][currentCol - 1];
        forward(currentRow, currentCol - 1, row, column, arr, length + 1, maxLength, path, longestPath);
    
	}
   
    
}


void printLongestPath(int maxLength, int longestPath[maxLength]) {// a basic array-printer with a fancy name
    int i;
    printf("The longest consecutive path is [");
   
    for (i = 0; i < maxLength; i++) {
        printf("%d ", longestPath[i]);
    }
    printf("] , visiting %d cells.", maxLength);
}


int main(void) {
    int row, column;

    printf("Enter row-column lengths: ");
    scanf("%d %d", &row, &column);

    int arr[row][column];
    int maxLength = 0; 
    int longestPath[row * column];

    printf("Enter the array:\n");
    readArray(row, column, arr);// void.

    findLongestPath(row, column, arr, &maxLength, longestPath);//updates the maxLenght value , fills in the longestPath

    printLongestPath(maxLength, longestPath);

}


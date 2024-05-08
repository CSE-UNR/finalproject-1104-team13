#include <stdio.h> 
#include <stdbool.h> 

#define MAX_WIDTH 100 
#define MAX_HEIGHT 100 

int workingImage[MAX_HEIGHT][MAX_WIDTH];
char image[MAX_HEIGHT][MAX_WIDTH]; // Image data 
char brightnessChars[] = {' ', '.', 'o', 'O', '0'}; // Mapping brightness values to characters 

void loadImage(char *filename, int *rows, int *cols) { 
	FILE *file = fopen(filename, "r"); 
	if (file == NULL) { 
		printf("Error opening file\n"); 
		return; 
	} 
	int i = 0, n = 0;
	char temp;
	while(fscanf(file, "%c", &temp) == 1)
		if(temp == '\0'){
		}
		else{
			image[n][i] = temp;
			i++;	
		}	
	
	
	printf("Sanity Check: %s", image[0]);
	
	
	
	fclose(file); 
	printf("Image loaded successfully.\n"); 
} 

void displayImage(char image[MAX_HEIGHT][MAX_WIDTH]) { 
	int c = 0, r = 0, n = 0;
	for(int i = 0; image[n][i] != '\0'; i++){
		if(image[n][i] == '\n'){
			r++;
		}
		else{
			c++;
		}
		printf("rows: %i\n col: %i\n", r, c/r);
	}
}

void cropImage() {
	int rows, cols, startX, startY, endX, endY;
	printf("Enter top-left corner (row, col): ");
	scanf("%d %d", &startX, &startY);
	printf("Enter bottom-right corner (row, col): ");
	scanf("%d %d", &endX, &endY);
	
	if (startX < 0 || startY < 0 || endX >= rows || endY >= cols || startX > endX || startY > endY) {
		printf("Invalid crop dimensions.\n");
		return;
	}
	
	int newRows = endX - startX + 1;
	int newCols = endY - startY + 1;
	int croppedImage[MAX_HEIGHT][MAX_WIDTH];
	
	for (int i = startX; i <= endX; i++) {
		for (int j = startY; j <= endY; j++) {
			croppedImage[i - startX][j - startY] = image[i][j];
		}
	}
	
	for (int i = 0; i < newRows; i++) {
		for (int j = 0; j < newCols; j++) {
			image[i][j] = croppedImage[i][j];
		}
	}
	
	rows = newRows;
	cols = newCols;
	printf("Image cropped.\n");
}

void editImage(int rows, int cols) { 
	int choice; printf("1. Dim Image\n2. Brighten Image\n3. Crop Image\n4. Save Image\n"); 
	printf("Enter your choice for editing: "); 
	scanf("%d", &choice); 
	
	switch (choice) { 
		case 1: //Dim
			for (int i = 0; i < rows; i++) { 
				for (int j = 0; j < cols; j++) { 
					if (image[i][j] > 0) image[i][j]--; 
				} 
			} 
			printf("Image dimmed.\n"); 
			break; 
		case 2: // Brighten 
			for (int i = 0; i < rows; i++) { 
				for (int j = 0; j < cols; j++) { 
					if (image[i][j] < 4) image[i][j]++; 
				} 
			} 
			printf("Image brightened.\n"); 
			break; 
		case 3:
			cropImage(rows, cols);
			break;
		case 4: // Save the image 
			printf("Enter filename to save the image: "); 
			char filename[256]; 
			scanf("%s", filename); 
			FILE *file = fopen(filename, "w"); 
			fprintf(file, "%d %d\n", rows, cols); 
			for (int i = 0; i < rows; i++) { 
				for (int j = 0; j < cols; j++) { 
					fprintf(file, "%d ", image[i][j]); 
				} 
				fprintf(file, "\n"); 
			} 
			fclose(file); 
			printf("Image saved to %s\n", filename); 
			break; 
		default: 
			printf("Invalid choice.\n"); 
			break; 
	} 
} 

int main() { 
	
	int rows = 0, cols = 0; 
	int choice; 
	char filename[256]; 
	
	while (true) { 
		printf("1. Load New Image\n2. Display Current Image\n3. Edit Current Image\n4. Exit\n"); 		
		printf("Enter your choice: "); 
		scanf("%d", &choice); 
		
		switch (choice) { 
			case 1: 
				printf("Enter filename to load: "); 
				scanf("%s", filename); 
				loadImage(filename, &rows, &cols); 
				break; 
			case 2: 
				if (image[0][0] == ' ') { 
					printf("No image loaded. Please load an image first.\n"); 
				} else { 
					displayImage(image); 
				} 
				break; 
			case 3: 
				if (rows == 0 || cols == 0) { 
					printf("No image loaded. Please load an image first.\n"); 
				} else { 
					editImage(rows, cols); 
				} 
				break; 
			case 4: 
				printf("Exiting program.\n"); 
				return 0; 
			default: 
				printf("Invalid choice.\n"); 
				break; 
		} 
	} 
}


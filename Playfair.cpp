#include <ctype.h>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;


char arr[5][5];

int has_duplication(char letter) {
	int i, j;
	int size = sizeof(arr) / sizeof(arr[0]);
	int result = 0;
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 5; j++) {
			result = (int)letter ^ (int)arr[i][j];
			if(result == 0) return 1;
		}
	}
	return 0;
}


int main() {
	int i, j;
	
	char letters[] = {'K', 'E', 'Y', 'W', 'O', 'R', 'D', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' ,'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	char key[] = {'K', 'E', 'Y', 'W', 'O', 'R', 'D'};
	
	vector<char> plain; 
	vector<char> cipher_text;
	char c;
	char pre_char;
	printf("Enter plain text to encrypt: \n");
	while(c = getchar()) {
		if(c == '\n' || c == '\0') break;
		c = toupper(c);
		if(c != ' ') {  // we do not consider spaces
		if(c == 'J') c = 'I';
		    if(pre_char == c) {
				plain.push_back('X');
				plain.push_back(c);
			} else {
				plain.push_back(c);
			}
			pre_char = c;	
		}
	}
	// if length of key array is odd, we add 'X' to the end of key
	if(plain.size() % 2 == 1) {
		plain.push_back('X');
	}
	
	// filling array with key and letters of alphabet
	int m = 0;
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 5; j++) {
			while(has_duplication(letters[m])) {
				m ++;
			}	
			arr[i][j] = letters[m];		
		}
	}
	
	// encrytion
	int n = 0;
	int first_i, first_j, second_i, second_j;
	while(n < plain.size()) {
		for(i = 0; i < 5; i++) {
			for(j = 0; j < 5; j++) {
				if(arr[i][j] == plain.at(n)) {
					first_i = i;
					first_j = j;
				}
				if(arr[i][j] == plain.at(n + 1)) {
					second_i = i;
					second_j = j;
				}
			}
		}
		// if both two letters are in the same row 
		if(first_i == second_i) {
			cipher_text.push_back(arr[first_i][(first_j + 1) % 5]);
			cipher_text.push_back(arr[second_i][(second_j + 1) % 5]);
		}
		
		// if both two letters are in the same column
		else if(first_j == second_j) {
			cipher_text.push_back(arr[(first_i + 1) % 5][first_j]);
			cipher_text.push_back(arr[(second_i + 1) % 5][second_j]);
		}		
		// otherwise we consider the rectangle that they form
		else {
			cipher_text.push_back(arr[first_i][second_j]);
			cipher_text.push_back(arr[second_i][first_j]);
		}	
		n += 2;
	}
	
	
	// result	: ecnrypted message
	printf("Encrypted message: \n");
	std::copy(cipher_text.begin(), cipher_text.end(), std::ostream_iterator<char>(std::cout, " "));
    printf("\n");
	
	
	
	// demonstration
	printf("Playcipher Matrix: \n");
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 5; j++) {
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}
}

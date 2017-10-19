/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2AHIF
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Pyramid of Numbers
 * Author:			Manuel Kommenda
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int, char multiply_or_divide, int counter);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
	printf("Pyramid of Numbers\n\n");
	char input[MAX_DIGITS];
	printf("Please enter one number: ");
	scanf("%s", input);
	int length = strlen(input);
	if(length > MAX_DIGITS){
		printf("Error code -1\n");
		return 0;
	}

	struct BigInt input_number = {length};
 	int actual = strtobig_int(input, length, &input_number);

	if(actual != length){
		printf("Error code -2\n");
		return 0;
	}

	for (int i = 2; i <= 9; i++) {
		length = MAX_DIGITS;
		int result_length = length;
		if (!(i == 2)) {
			print_big_int(&input_number, 'm', 0);
		}
		else{
			printf("%s", input);
		}

		printf(" * %d = ",i);
		if (input_number.the_int[0] * i >= 10 && result_length == length ) {
			result_length++;
		}
		struct BigInt result = {result_length};
		multiply(&input_number, i, &result);
		print_big_int(&result, 'm', 0);
		copy_big_int(&result, &input_number);
		printf("\n");

		if (i == 9) {
			print_big_int(&input_number, 'm', 0);
		}
	}

	int counter = 1;

	for (int i = 2; i <= 9; i++) {
		length = MAX_DIGITS;
		int result_length = length;
		if (!(i == 2)) {
			print_big_int(&input_number, 'd', counter - 1);
		}

		printf(" / %d = ",i);
		if (input_number.the_int[0] * i >= 10 && result_length == length ) {
			result_length++;
		}
		struct BigInt result = {result_length};
		divide(&input_number, i, &result);
		print_big_int(&result, 'd', counter);
		copy_big_int(&result, &input_number);
		printf("\n");

		counter++;
	}

	return 0;
}

int strtobig_int(const char *str, int length, struct BigInt *big_int){

	for (size_t i = 0; i < length; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			big_int->the_int[i] = str[i] - '0';
		}
		else{
			return i;
		}
	}
	return length;

}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result){
	int to_transfer_int = 0;

	for (int i = big_int->digits_count - 1; i >= 0; i--) {
		int result = big_int->the_int[i] * factor + to_transfer_int;
		to_transfer_int = result / 10;
		big_result->the_int[big_result->digits_count - (big_int->digits_count - i)] = result - 10 * to_transfer_int;

		if (0 < to_transfer_int) {
			big_result->the_int[0] = to_transfer_int;
		}

	}

}

void copy_big_int(const struct BigInt *from, struct BigInt *to){

	if (from->digits_count > to->digits_count) {
		to->digits_count = from->digits_count;
	}

	for (int i = from->digits_count -1; i >= 0; i--) {
		to->the_int[i] = from->the_int[i];
	}
}

void print_big_int(const struct BigInt *big_int, char multiply_or_divide, int counter){
	int is_zero = 0;

	if (multiply_or_divide == 'd') {
			for (int i = 0; i < MAX_DIGITS - counter; i++) {
				if (!(big_int->the_int[i] == 0 && is_zero == 0)) {
								printf("%d", big_int->the_int[i]);
								is_zero = 1;
				}
			}
	}
	else{
	for (int i = 0; i < MAX_DIGITS; i++) {
		if (!(big_int->the_int[i] == 0 && is_zero == 0)) {
						printf("%d", big_int->the_int[i]);
						is_zero = 1;
				}
			}
		}
}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result){
	int overflow = 0;
	int counter = 0;

	for (int i = 0; i < big_int->digits_count; i++) {
		int number = big_int->the_int[i] + 10 * overflow;
		if (number >= divisor) {
			big_result->the_int[i - counter] = number / divisor;
			overflow = number % divisor;
		}
		else{
			overflow = big_int->the_int[i];
			if (i == 0) {
				counter++;
				big_result->digits_count--;
			}
			else{
				big_result->the_int[i-counter] = 0;
			}
		}

	}
}

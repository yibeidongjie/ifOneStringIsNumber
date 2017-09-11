/* 练习：判断字符串是否表示数值。
要求：支持："123E4", "123e-6", "+123", "-123", "1.23", ".23", "1.", ".23E+4"
结果：实现了功能，解题思路一般，代码不够简洁，有待优化。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#include <stdbool.h>  // _bool 

#define BOOL int
#define TRUE 1
#define FALSE 0

#define NUM_STRING_MAX 40
#define LEN_STRING_MAX 20

static BOOL inputIsNumber(char *str);

static void test();
static void printResult(BOOL isNumber);

int main()
{
	test();
	//system("pause");
	return 0;
}

static void test()
{
	BOOL isNumber = FALSE;
	
	// 测试案例方式
		// 测试案例
		char strTest[NUM_STRING_MAX][LEN_STRING_MAX] = {"000000000", "555555555", "999999999", 
		"123456789", "+123456789", "-123456789",
		"123.456789", "+123.456789", "-123.456789",
		"123.456E789", "+123.456e789", "-123.456e789",
		"123.456E+789", "+123.456E+789", "123.456e-789",
		"123.", ".456", ".456E789", ".456E789",
		"123A", "123a456", "123.456Ea", "123.456e", ".456E", "123E", "123.E", "123.f", ".E", "asdf", ".456e", ""
		}; int numStrTest = 31;	
		
		// 测试
		printf("   node     The input string  \tisNumber?\n");
		int i = 0;
		for(i = 0; i < numStrTest; i++) {
			printf("##%3d : %20s\t", i, strTest[i]);
			isNumber = inputIsNumber(&strTest[i][0]);
			printResult(isNumber);
		}

	// 交互方式
		/* char str[100];
		while(TRUE) {
			printf("Please input a string\n");
			gets(str);	
			isNumber = inputIsNumber(str);
			printResult(isNumber);
			printf("\n");
		} */
}

static void printResult(BOOL isNumber)
{
	if(isNumber) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	return ;
}

static BOOL inputIsNumber(char *str)
{
	BOOL isNumber = FALSE;
	
	if(str == NULL) { return FALSE; }
	if(str[0] == '\0') { return FALSE; }
	
	if(str[0] == '+' || str[0] == '-') {
		str++;
	}
	
	BOOL StatusInteger = FALSE;
	BOOL StatusDecinal = FALSE;
	BOOL StatusExponent = FALSE;
	
	int iShiftOfStr = 0;
	// 扫描整数部分
	if(str[0] == '.') {
		StatusInteger = TRUE;
		iShiftOfStr = 1;
		if(str[1] == '\0') {
			return FALSE;
		}
	} else {
		int i = 0;
		BOOL loopContinue = TRUE;
		while(loopContinue) {
			if(str[i] <= '9' && str[i] >= '0') {
				StatusInteger = TRUE;
				i++;
			} else if(StatusInteger && str[i] == '\0') {
				return TRUE;
			} else if(StatusInteger && str[i] == '.') {
				i++;
				loopContinue = FALSE;
			} else if(StatusInteger && (str[i] == 'E' || str[i] == 'e')) {
				i++;
				StatusDecinal = TRUE;
				loopContinue = FALSE;
			} else {
				return FALSE;
			}
		}
		iShiftOfStr = i;
	}
	
	// 扫描小数部分
	if(!StatusDecinal) {
		if(str[iShiftOfStr] == '\0') { return TRUE;}
		int i = iShiftOfStr;
		BOOL loopContinue = TRUE;
		while(loopContinue) {
			if(str[i] == 'E' || str[i] == 'e') {
				i++;
				loopContinue = FALSE;
			} else if(str[i] <= '9' && str[i] >= '0') {
				i++;
				StatusDecinal = TRUE;
			} else if(StatusDecinal && str[i] == '\0') {
				return TRUE;
			} else {
				return FALSE;
			}			
		}		
		iShiftOfStr = i;
	}
	
	// 扫描指数部分
	if(str[iShiftOfStr] == '\0') {
		return FALSE;
	} else {
		int i = iShiftOfStr;
		if(str[i] == '+' || str[i] == '-') {
			i++;
		}		
		BOOL loopContinue = TRUE;
		while(loopContinue) {
			if(str[i] <= '9' && str[i] >= '0') {
				i++;
				StatusExponent = TRUE;
			} else if(StatusExponent && str[i] == '\0') {
				return TRUE;
			} else {
				return FALSE;
			}
		}
	}

	//return TRUE;
}




















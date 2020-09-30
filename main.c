#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum BASE_TYPES{
	BASE_BINARY = 2,
	BASE_OCTAL = 8,
	BASE_DECIMAL = 10,
	BASE_HEX = 16,
	BASE_BYTE = 256
}BaseTypes;

unsigned char utils_convertDecToBase(unsigned char* byteFmt, unsigned long num, BaseTypes base);
unsigned long utils_convertBaseToDec(unsigned char* byteFmt, BaseTypes base);

int main(void){
	
//	unsigned long int num = 16777215; // 2 bytes - 16^4 = 65.535 | 3 bytes - 16^6 = 16.777.215 | 16^5 = 1.048.575
	
	unsigned long int num = 65537;
	unsigned char byte[5];
	
	utils_convertDecToBase(byte, num, BASE_BYTE);
	
	printf("\r\r\n\n%x. %x . %x. %x = %d\r\r\n\n",byte[0], byte[1], byte[2], byte[3], num);

	printf("\r\n\r\nNum: %d", utils_convertBaseToDec(byte, BASE_BYTE));
	
	return 0;
}

/**
 * @method: - Converte um numero Decimal em uma base desejada.
 * 			- o byte 0, sempre e o menos significativo.
 *		
 * @param: *array bytes - aponta para variavel que ira receber a informacao.
 * @param: Numero a ser convertido.
 * @param: BaseTypes - Lista de base para conversao.
 * 
 * @return: Erro = EXIT_FAILURE | Ok = EXIT_SUCCESS
 **/
unsigned char utils_convertDecToBase(unsigned char*byteFmt, unsigned long num, BaseTypes base){
	
	const unsigned char CNT_FORCE_BREAK = 10; // tentativas maximas
	unsigned char result=EXIT_FAILURE;
	int idx=0;
	
	memset(byteFmt, 0, sizeof(byteFmt)/sizeof(byteFmt[0])); //  limpa o buff
	
	// foi utilizado o For como "timeout"
	for(idx=0; idx<CNT_FORCE_BREAK; idx++){		
		if(num>=base){
			byteFmt[idx] = num%base;
			num /= base;
		}else{
			result=EXIT_SUCCESS;
			byteFmt[idx]=num;
			break;
		}		
	}
	return result;
}

/**
 * @method: - Utiliza o metodo convencional de conversao de base
 *			- Converte qualquer base em Dec...
 * 
 * @param: *array bytes - aponta para variavel que contem a informacao em base.
 * @param: BaseTypes - Lista de base para conversao.
 * 
 * @return: numero convertido para base.
 **/
unsigned long utils_convertBaseToDec(unsigned char* byteFmt, BaseTypes base){
	
	unsigned long idx=0;
	unsigned long num=0;
	unsigned long len=0; 
	len = sizeof(byteFmt)/sizeof(byteFmt[0]);
	for (idx=0; idx<len; idx++){
		num += (byteFmt[idx] * pow(base, idx));
	}
//	printf("\r\r\n\nNum = %d", num);	
	return num;
}


// Como executar no terminal:
// gcc -Wall -O3 nomesobrenome_123456789012_exemplo.c -o nomesobrenome_123456789012_exemplo
// ./nomesobrenome_123456789012_exemplo entrada saida

// Numeros padronizados
#include <stdint.h>
// Biblioteca padrao
#include <stdlib.h>
// Entrada/saida padrao
#include <stdio.h>

// Funcao principal
int main(int argc, char* argv[]) {
	// Exibindo a quantidade de argumentos
	printf("Quantidade de argumentos (argc): %i\n", argc);
	// Iterando sobre o(s) argumento(s) do programa
	for(uint32_t i = 0; i < argc; i++) {
		// Mostrando o argumento i
		printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
	}
	// Abrindo os arquivos com as permissoes corretas
	//FILE* input = fopen(argv[1], "r");
	//FILE* output = fopen(argv[2], "w");
	// 32 registradores inicializados com zero
	uint32_t R[32] = { 0 };
	// Memoria com 32 KiB inicializada com zero
	uint8_t* MEM8 = (uint8_t*)(calloc(32, 1024));
	uint32_t* MEM32 = (uint32_t*)(calloc(8, 1024));
	// Depois de carregamento do arquivo 1_intro.hex, o vetor de memoria contem o conteudo abaixo:
	//0xDC000007
	MEM8[0] = 0xDC; MEM8[1] = 0x00; MEM8[2] = 0x00; MEM8[3] = 0x07;
	MEM32[0] = 0xDC000007;
	// 0x00000000
	MEM8[4] = 0x00; MEM8[5] = 0x00; MEM8[6] = 0x00; MEM8[7] = 0x00;
	MEM32[1] = 0x00000000;
	// 0x00000000
	MEM8[8] = 0x00; MEM8[9] = 0x00; MEM8[10] = 0x00; MEM8[11] = 0x00;
	MEM32[2] = 0x00000000;
	// 0x00000000
	MEM8[12] = 0x00; MEM8[13] = 0x00; MEM8[14] = 0x00; MEM8[15] = 0x00;
	MEM32[3] = 0x00000000;
	// 0x00000000
	MEM8[16] = 0x00; MEM8[17] = 0x00; MEM8[18] = 0x00; MEM8[19] = 0x00;
	MEM32[4] = 0x00000000;
	// 0x00000000
	MEM8[20] = 0x00; MEM8[21] = 0x00; MEM8[22] = 0x00; MEM8[23] = 0x00;
	MEM32[5] = 0x00000000;
	// 0x00000000
	MEM8[24] = 0x00; MEM8[25] = 0x00; MEM8[26] = 0x00; MEM8[27] = 0x00;
	MEM32[6] = 0x00000000;
	// 0x00000000
	MEM8[28] = 0x00; MEM8[29] = 0x00; MEM8[30] = 0x00; MEM8[31] = 0x00;
	MEM32[7] = 0x00000000;
	// 0x00203039
	MEM8[32] = 0x00; MEM8[33] = 0x20; MEM8[34] = 0x30; MEM8[35] = 0x39;
	MEM32[8] = 0x00203039;
	// 0x61200003
	MEM8[36] = 0x61; MEM8[37] = 0x20; MEM8[38] = 0x00; MEM8[39] = 0x03;
	MEM32[9] = 0x61200003;
	// 0x69400008
	MEM8[40] = 0x69; MEM8[41] = 0x40; MEM8[42] = 0x00; MEM8[43] = 0x08;
	MEM32[10] = 0x69400008;
	// 0xFC000000
	MEM8[44] = 0xFC; MEM8[45] = 0x00; MEM8[46] = 0x00; MEM8[47] = 0x00;
	MEM32[11] = 0xFC000000;
	// Imprimindo o conteudo das memorias em bytes
	printf("\nMEM8:\n");
	for(uint8_t i = 0; i < 48; i = i + 4) {
		// Impressao lado a lado
		printf("0x%08X: 0x%02X 0x%02X 0x%02X 0x%02X\n", i, MEM8[i], MEM8[i + 1], MEM8[i + 2], MEM8[i + 3]);
	}
	printf("\nMEM32:\n");
	for(uint8_t i = 0; i < 12; i = i + 1) {
		// Impressao lado a lado
		printf("0x%08X: 0x%08X (0x%02X 0x%02X 0x%02X 0x%02X)\n", i << 2, MEM32[i], ((uint8_t*)(MEM32))[(i << 2) + 3], ((uint8_t*)(MEM32))[(i << 2) + 2], ((uint8_t*)(MEM32))[(i << 2) + 1], ((uint8_t*)(MEM32))[(i << 2) + 0]);
	}
	// Separador da saida esperada
	printf("\nSaida esperada\n\n      |       \n      V       \n\n");
	// Exibindo a inicializacao da execucao
	printf("[START OF SIMULATION]\n");
	// Setando a condicao de execucao para verdadeiro
	uint8_t executa = 1;
	// Enquanto executa for verdadeiro
	while(executa) {
		// Cadeia de caracteres da instrucao
		char instrucao[30] = { 0 };
		// Declarando operandos
		uint8_t z = 0, x = 0, i = 0;
		uint32_t pc = 0, xyl = 0;
		// Carregando a instrucao de 32 bits (4 bytes) da memoria indexada pelo PC (R29) no registrador IR (R28)
		// E feita a leitura redundante com MEM8 e MEM32 para mostrar formas equivalentes de acesso
		// Se X (MEM8) for igual a Y (MEM32), entao X e Y sao iguais a X | Y (redundancia)
		R[28] = ((MEM8[R[29] + 0] << 24) | (MEM8[R[29] + 1] << 16) | (MEM8[R[29] + 2] << 8) | (MEM8[R[29] + 3] << 0)) | MEM32[R[29] >> 2];
		// Obtendo o codigo da operacao (6 bits mais significativos)
		uint8_t opcode = (R[28] & (0b111111 << 26)) >> 26;
		// Decodificando a instrucao buscada na memoria
		switch(opcode) {
			// mov
			case 0b000000:
				// Obtendo operandos
				z = (R[28] & (0b11111 << 21)) >> 21;
				xyl = R[28] & 0x1FFFFF;
				// Execucao do comportamento
				R[z] = xyl;
				// Formatacao da instrucao
				sprintf(instrucao, "mov r%u,%u", z, xyl);
				// Formatacao de saida em tela (deve mudar para o arquivo de saida)
				printf("0x%08X:\t%-25s\tR%u=0x%08X\n", R[29], instrucao, z, xyl);
				break;
			// l8
			case 0b011000:
				// Otendo operandos
				z = (R[28] & (0b11111 << 21)) >> 21;
				x = (R[28] & (0b11111 << 16)) >> 16;
				i = R[28] & 0xFFFF;
				// Execucao do comportamento com MEM8 e MEM32
				R[z] = MEM8[R[x] + i] | (((uint8_t*)(MEM32))[(R[x] + i) >> 2]);
				// Formatacao da instrucao
				sprintf(instrucao, "l8 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
				// Formatacao de saida em tela (deve mudar para o arquivo de saida)
				printf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%02X\n", R[29], instrucao, z, R[x] + i, R[z]);
				break;
			// l32
			case 0b011010:
				// Otendo operandos
				z = (R[28] & (0b11111 << 21)) >> 21;
				x = (R[28] & (0b11111 << 16)) >> 16;
				i = R[28] & 0xFFFF;
				// Execucao do comportamento com MEM8 e MEM32
				R[z] = ((MEM8[((R[x] + i) << 2) + 0] << 24) | (MEM8[((R[x] + i) << 2) + 1] << 16) | (MEM8[((R[x] + i) << 2) + 2] << 8) | (MEM8[((R[x] + i) << 2) + 3] << 0)) | MEM32[R[x] + i];
				// Formatacao da instrucao
				sprintf(instrucao, "l32 r%u,[r%u%s%i]", z, x, (i >= 0) ? ("+") : (""), i);
				// Formatacao de saida em tela (deve mudar para o arquivo de saida)
				printf("0x%08X:\t%-25s\tR%u=MEM[0x%08X]=0x%08X\n", R[29], instrucao, z, (R[x] + i) << 2, R[z]);
				break;
			// bun
			case 0b110111:
				// Armazenando o PC antigo
				pc = R[29];
				// Execucao do comportamento
				R[29] = R[29] + ((R[28] & 0x3FFFFFF) << 2);
				// Formatacao da instrucao
				sprintf(instrucao, "bun %i", R[28] & 0x3FFFFFF);
				// Formatacao de saida em tela (deve mudar para o arquivo de saida)
				printf("0x%08X:\t%-25s\tPC=0x%08X\n", pc, instrucao, R[29] + 4);
				break;
			// int
			case 0b111111:
				// Parar a execucao
				executa = 0;
				// Formatacao da instrucao
				sprintf(instrucao, "int 0");
				// Formatacao de saida em tela (deve mudar para o arquivo de saida)
				printf("0x%08X:\t%-25s\tCR=0x00000000,PC=0x00000000\n", R[29], instrucao);
				break;
			// Instrucao desconhecida
			default:
				// Exibindo mensagem de erro
				printf("Instrucao desconhecida!\n");
				// Parar a execucao
				executa = 0;
		}
		// PC = PC + 4 (proxima instrucao)
		R[29] = R[29] + 4;
	}
	// Exibindo a finalizacao da execucao
	printf("[END OF SIMULATION]\n");
	// Fechando os arquivos
	//fclose(input);
	//fclose(output);
	// Finalizando programa
	return 0;
}

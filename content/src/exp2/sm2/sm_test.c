#include <stdio.h>
#include "sm2alg.h"

int main(int argc, char* argv[])
{
	printf("SM2_enc_selftest:%d\n",SM2_enc_selftest());
    printf("SM2_sign_selftest:%d\n", SM2_sign_selftest());
    printf("SM2_standard_keyex_selftest:%d\n", SM2_standard_keyex_selftest());
	return 0;
}

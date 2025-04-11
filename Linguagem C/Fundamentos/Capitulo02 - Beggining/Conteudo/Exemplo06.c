#include <stdio.h>

int main(void){
    char confirm;
    int fisrt_number, second_number;
    
    printf("Vc deseja realizar uma soma? ");
    scanf("%c", &confirm);

    if (confirm == 's'){
        printf("Digite os dois numeros: ");
        scanf("%d%d", &fisrt_number, &second_number);
        printf("O resultado de %d + %d = %d", fisrt_number, second_number, fisrt_number + second_number);
    }
    else{
        printf("Poxa vida :(");
    }
}
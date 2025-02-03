/*                                         Anotações gerais sobre vetores                             */

#include <stdio.h>
// Metodo que descobre o tamanho de um vetor deseconhecido
// #define len(arr) (int)(sizeof(arr) / sizeof((arr)[0]))

/* Nele pegamos o tamanho que o vetor ocupa na memória como um todo e dividimos pelo tamanho que o valor 0
deste vetor ocupa na memória, desta forma obtemos o resultado sendo ele o tamanho completo do vetor*/

/*Uma alternativa a este código é utilizando uma constante simbolica onde atribuo ao tamanho do meu
vetor e assim facilito as coisas, se eu fizer a subistituição irá funcionar da mesma forma.*/
#define DIM 20 // >> Esta seria a variável constante, no qual durante o código será subistituida pelo seu valor.
// Eu consigo descobrir o valor do último indice do vetor pegando DIM e subitraindo 1  

// Outra forma de criar uma variável constante é utilizando o próprio C

// const int DIM = 20; 

/* Soq eu não poderei utilizar dentro de um elemento de vetor esta variável constante
e ele ocupa um endereço de memória */

int main(void){
    // int valor[8]; // Inicializando vetor com trash 
    int valor[DIM] = {0}; // Zerando todas as cargas iniciais 
    int result = 0;

    /*                                           NOTAS 
    > Para a definição de um vetor precisamos de atribuir um tipo ao vetor e a quantitade de slots do vetor.
      Este tipo, são as informações que estarão armazenadas no vetor em si.

    > Um resalte importante é que informações inuteis presentes na memória do computador, quando não
      tratadas ficam salvas no meu vetor  chamamos isso de trash ou lixo, que nada mais são que informações
      que outrora estavam armazenadas na memória RAM do computador. Uma solução para este problema é definir 
      o vetor com o valor os seus primeiros slots com 0, ou qualquer outro valor desta forma o compilador
      ira definir automaticamente todos os outros slots para 0 também. 
    
      Código alternativo, lembrando que para começarmos a inserir valores dentro de um vetor é necessário a 
      utilização de chaves, e cada item dentro dessas chaves representa um slot no vetor.

      int valor[8] = {0}; 

    > Para acessar valores dentro de um vetor, basta acessar um indice de dentro dele
      podendo assim, realizar qualquer operação dentro deste indice (slot) 
    
    */

    valor[0] = 22; // Acessando o valor do indice 0 no vetor valor e atribuindo o valor 22 a ele.
    valor[3] = 9; // Acessando o valor do indice 3 no vetor valor e atribuindo o valor 9 a ele.

    // É possível realizar operações aritimeticas com base no valor dos slots
    result = valor[0] - valor[3];
    valor[DIM - 1] = result; // O valor armazendado no ultimo indice será: 22 - 9 ou seja: 13
    

    for (int i = 0; i < DIM; ++i){
        printf("\nValor %2d -- %2d", i, valor[i]);
        if ((valor[i] == 22 && i == 0) || (valor[i] == 9 && i == 3)) printf(" <-- Valor inserido");
        if ((valor[i] == result && i == (DIM - 1))) printf(" <-- Op. aritimetica");
    }
}
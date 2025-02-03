# Demais informações sobre strings
Strings são um conjunto de caracteres marcados em seu final por um delimitador conhecido como `\0`. Sendo assim, a forma correta de se declarar uma string é utilizando um vetor unidimencional, com o caractere delimitador em seu final. Strings são representadas entre aspas duplas ou `" "`, em C não conseguimos manipular uma string por padrão, como concatenar informações ou então atribuir elas a uma variável, por isso há a necessidade de usar funções especificas para realizar esses procedimentos.

|Codigo|Função|Retorno|Exemplo|
|-|-|-|-|
|`strcountc(char *s, char ch)`|Devolve o número de ocorrencias do caractere ch na string s|int|Ex. 01|
|`strcountd(char *s)`|Devolve o número de dígitos na string s|int|Ex. 02|
|`indchr(char *s)`|Devolve o índice da primeira ocorrência do caractere ch na string s|int|Ex. 03|
|`strpal(char *s)`|Veriica se a string é um palíndromo|int|Ex. 04|
|`strrev(char *s)`|Inverte a string s e devolve-a invertida|char|Ex. 05|
|`strcmp(char *s1, char*s2)`|Compara as strings s1 e s2 alfabeticamente|int|Ex. 06|
|`strpad(char *s)`|Coloca um espaço em branco após cada um dos caracteres da string s|char|Ex. 07|
|`strdelc(char *s, char ch)`|Apaga todas as ocorrências do caracatere ch na string s|char|Ex. 08|


## Exemplos
---
Exemplo 01 - Devolve o número de ocorrencias do caractere ch na string s

```C
    int strcountc(char *s, char ch){
        int i, conta;
        for (i = conta = 0; s[i] != '\0'; i++){
            if (s[i] == ch) {
                conta++;
            }
        return conta;
        }
    }
```
---
Exemplo 02 - Devolve o número de dígitos na string s
```C
    #include <ctype.h> //para que possamos utilizar a função isdigit

    int strcountd(char *s){
        int i, conta;
        for (i = conta = 0; s[i] != '\0'; i++){
            if (isdigit(s[i])) {
                conta++;
            }
        return conta;
        }
    }
```

---
Exemplo 03 - Devolve o índice da primeira ocorrência do caractere ch na string s
```C
    int indchr(char *s, char ch){
        int i=0;
        while (s[i] != ch ** s[i] != '\0') i++;
    }
```

---
Exemplo 04 - Veriica se a string é um palíndromo
```C
    int strpal(char *s){
        int i, j;
        for (i = 0, j = strlen(s) - 1; i < j; i++, j--){
            if (s[i] != s[j]){
                return 0;
            }
        }
    return 1;    
    }
```
Exemplo 05 - Inverte a string s e devolve-a invertida
```C
    char *strrev(char *s){
        int i, len;
        char aux;

        for (i = 0, len = strlen(s) - 1; i < len; i++, len--){
            aux = s[i];
            s[i] = s[len];
            s[len] = aux;
        }

        return s;
    }
```
---
Exemplo 06 - Compara as strings s1 e s2 alfabeticamente
```C
    int strcmp(char *s1, char *s2){
        int i = 0;
        while (s1[i] == s2[i] && s1[i] != '\0') i++;
        return (s1[i] - s2[i]);
    }
```
---
Exemplo 07 - Coloca um espaço em branco após cada um dos caracteres da string s
```C
    char *strpad(char *s){
        int i = strlen(s);
        s[2 * i] = s[i];

        for (i--; i >= 0; i--){
            s[2 * i] = s[i];
            s[2 * i + 1] = ' ';
        }

        return s;
    }
```
---
Exemplo 08 - Apaga todas as ocorrências do caracatere ch na string s
```C
    char * strdelc(char * s, char ch){
        int i,j;
        for (i = j = 0; s[i] != '\0'; i++){
            if (s[i] != ch){
                s[j++] = s[i];
            }
        }
        s[j] = '\0';
        return s;
    }
```
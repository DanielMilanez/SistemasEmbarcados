Quando trabalhamos no desenvolvimento de projetos e queremos salvar nossas variáveis e nossos conteudos de vetores e etc.. Podemos recorrer aos arquivos para realizar esses procedimentos, e para isso nos recorremos a arquivos binários.

***Quando um ponteiro poderá apontar para diversos tipos, podemos declara-lo como o tipo void*** 

Para escrevermos informações precisamos utilizar funções expecificas para acesso direto aos elementos. `fread` `fwrite`

```C
    int fwrite(const void *ptr, int size, int n, FILE *arq);
```

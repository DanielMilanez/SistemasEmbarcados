A linguagem C possui funções para a manipulação de arquivos, onde podemos armazenar dados de nosso programa de forma definitiva, ao invés de perde-los ao final da execução. Com eles podemos também ler dados de arquivos e adapta-los em nossos programas.

Do ponto de vista da linguagem, um arquivo é um conjunto sequencial de bytes "um linguição de bytes" como diria Fabio Akkita, essa sequencia pode ser chamada de `stream`.

A abertrua de um arquivo é realizada atra´ves de um ponteiro para o arquivo e este ponteiro tera o tipo `FILE`.

```C
    FILE *nome; 
    FILE *fopen(const char *filename, const char *mode); // Abrir um arquivo
```

Existem diferentes tipos de modos para abertura de arquivos, onde que cada um deles será efetuada um processo.
|modo|significado|
|--|--|
|r|Abre um arquivo-texto para leitura (read)|
|w|Cria um arquivo-texto para escrita (write)|
|a|Acrescenta dados a um arquivo-texto (append)|
|rb|Abre um arquivo binário para leitura (read binary)|
|r+|Abre um arquivo-texto para leitura/escrita|
|w+|Cria um arquivo-texto para leitura/escrita|
|a+|Acrescenta ou cria um arquivo-texto para leitura/escrita|
|r+b|Abre um arquivo binário para leitura/escrita|
|w+b|Cria um arquivo binário para leitura/escrita|
|a+b|Acrescenta a um arquivo binário para leitura/escrita|

Antes do fechamento do arquivo, todos os dados são devidamente gravados. Após, é necessário liberarmos a memória alocada pela função fopen. Para isso, utilizamos a função fclose. `int fclose(FILE *arq);`.


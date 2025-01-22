O objetivo desta atividade é gerar um código capaz de realizar a criptografia de uma serie de informações de entrada do usuário, lembrando que essas entradas estarão sendo valores em hexadecimal.

Enunciado:

/*
    Um processador deve receber diversos bytes e realizar uma conversão criptografada dos mesmos.
    A criptografia será somar 5 aos elementos pares do vetor e subtrair 3 dos elementos ímpares.

    Exemplo: você entra com os bytes 0xA0, 0x73, 0x25, 0xD3, 0xCA, 0xFE. A função os
    converterá para 0xA5, 0x70, 0x2A, 0xD0, 0xCF, 0xFB. Trabalhe com números em hexadecimal

    Após, desenvolva também uma função para descriptografar estes bytes.
*/

Resolução:

Apenas uma dúvida gerada durante a resolução:
- [X] Descobrir uma forma de trabalhar com valores hexadecimais nas variáveis.
  
  Solução >> É possivel trabalhar com valores hexadecimais diretamente em variáveis do próprio código, a conversão fica então por responsabilidade do compilador.
 

Minha solução foi então utilizar o salvamento em vetores para valores decimais e a exibição para o usuário em valores hexadecimais.
Por fim faço a exebição dos valores sem a necessidade de uma função de descriptografia
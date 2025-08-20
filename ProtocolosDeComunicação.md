## 📡 Protocolos de comunicação

Neste documento encontram-se meus estudos a respeito de protocolos de comunicação. A principio iremos discutir sobre o protocolo *ONE-WIRE*, *UART* e *USART*, e depois iremos progredir para 
*I2C*, *SPI*.


### One Wire

O protocolo de comunicação *One-Wire* é uma tecnologia serial que utiliza apenas um único fio de dados (além do GND) para comunicação entre dispositivos. Foi desenvolvido pela *Dallas Semiconductor*(hoje *Maxim Integrated*) e existe desde os anos 1980.

*Ao utilizar este protocolo a comunicação fica restrita em ~16 kbps (modo normal) ou até 125 kbps em overdrive*

O One-Wire não utiliza um sinal de clock separado. Em vez disso, baseia-se na largura de pulso (ou seja, na duração dos níveis lógicos no fio de dados) para sincronizar e transmitir os bits.

Existem algumas características importantes para que haja uma plena comunicação entre os dispositivos.

|Caracteristica|Descrição|
|--|--|
|Número de fios| 2 (Dados e GND)|
|Topologia suportada|Barramento|
|Distância típica|Até 100m (precisa de pull-up)|
|Velocidade de comunicação|Baixa, restrita em ~16 kbps ou até 125 kbps em overdrive|
|Alimentação parasita|Existem alguns dispositivos que podem ser alimentados pelo próprio fio de dados, sem usar o vcc separadamente|
|Endereçamento|Cada dispositivo possui um endereço único de 64bits gravados de fábirca|

> NOTA: a alimentação parasita funciona porque o pino de dados pode fornecer corrente limitada, mas isso exige um capacitor de desacoplamento no dispositivo.

O **One-Wire** é um protocolo ***half-duplex*** (os dados trafegam em um sentido de cada vez). Ele é ideal para aplicações com poucos pinos disponíveis ou quando a quantidade de conexões deve ser minimizada.

### Como ele funciona?

Como mencionado, o protocolo utiliza a largura do pulso (tempo de sinal em nível baixo ou alto) para representar os bits transmitidos, já que não há um sinal de clock dedicado.

1. Reset e presença: 

    Quando o protocolo se inicia o mestre (microcontrolador) puxa a linha de dados para baixo. E isso faz com que os periféricos respondam com um *pulso de presença*, indicando que estão conectados e prontos.

1. Transmissão de bits:

    Enfim ocorre a transmissão de bits, a comunicação é feita bit a bit, com "slots" temporais definidos.

    - Ao escrever um bit o mestre puxa a linha para LOW por um tempo curto (1) ou longo (0) 

    - Ao realizar a leitrua o mestre puxa a linha para LOW brevemente, depois a "solta", após um breve momento, o slave começa a transmitir os dados, podendo ser tempos lognos ou curtos.

Como foi mencionado cada dispositivo one-wire tem um identificador único de 64 bits.

[8 bits - código da família] + [48 bits - número de série] + [8 bits - CRC]

>CRC (Cyclic Redundancy Check) é um algoritmo de verificação de integridade de dados. Ele calcula um valor (redundância) a partir do conteúdo transmitido e o anexa à mensagem. O receptor refaz o cálculo e compara os valores para detectar possíveis erros de transmissão.

### Exemplo de componente

O DS28E18 é uma ***ponte de comunicação*** que permite o controle de dispositivos I²C ou SPI utilizando o protocolo One-Wire.

Ele permite que um microcontrolador se comunique com periféricos I²C/SPI usando apenas o fio One-Wire. Isso reduz drasticamente o número de fios em sistemas distribuídos ou remotos.

- Pode fornecer até 10 mA de corrente para alimentar os periféricos conectados.

- Suporta comunicação I²C/SPI com clock entre 1 MHz e 2.3 MHz.

- Possui 512 bytes de SRAM, usados para armazenar comandos I²C ou SPI.

- Um sequenciador interno executa os comandos da memória e responde via One-Wire.

- O resultado pode ser lido com um comando subsequente do mestre.

- A ponte de comunicação vem em um pequeno encapsulamento, e opera a 3.3V em condições ambientes.

Internamente existe um *Sequenciador de comandos*, cujo o qual processa os dados do buffer e os armazena no endereço especificado da SRAM (128 bytes por vez) e retorna um CRC16 (CRC de 16 bits)

O DS28E18 possui um buffer de 512 bytes na SRAM o que permite que seja possivel carregar inúmeros comandos I2C ou então SPI. Assim, quando for carregado o controlador envia uma ordem para executar a sequência armazenada, fornecer energia e coletar dados de periféricos conectados via I2C ou SPI. Um comando one wire subsequente lê os dados coletados do sensor.

Existem ao todo três tipos de comandos
- Comandos de função ROM one-wire
- Comandos de função do dispositivo DS28E18
- Comandos do sequenciador DS28E18

Ao enviar um comando para o periferico o mesmo envia este comando via barramento I2C ou SPI e retorna a linha one-wire um NACK ou ACK dependendo se a comunicação foi sucedida ou não.

O protocolo One-Wire é simples, eficiente e extremamente útil em aplicações com limitações de hardware, como sensores distribuídos. Dispositivos como o DS18B20 (temperatura) e DS28E18 (ponte I²C/SPI) demonstram a versatilidade dessa tecnologia

## Protocolo UART e USART

### UART

O **_UART_** é um protocolo de comunicação serial assíncrono. Significa que não existe clock, muitos dispositivos usam UART internamente, como módulos Bluetooth clássico, GPS e a comunicação RS-232; já o USB usa outro protocolo, mas pode ser convertido em UART com chips específicos.

No UART, não há sinal de clock compartilhado entre os dispositivos. Em vez disso os dois lados devem estar configurados com a mesma taxa de transmissão, BAUD RATE, e seguem uma convenção de início e fim de frames (quadros).

Cada byte de dados enviado pela UART é envolvido por bits de controle. O SPI é um protocolo de ponto a ponto, ou seja, não existe a noção de mestre e escravo, apenas transmissor e receptor.

Tanto o UART e o USART de forma nativa, não permitem multi-slave e multi-mestre, por isso não é necessário o adicional de endereçamento, em seu byte de dados. É possível desenvolver uma forma de multi-slave mas é necessário outros protocolos e também uma lógica adicional. 

```sql
Idle(1) | Start(0) | d0 d1 d2 d3 d4 d5 d6 d7 | Stop(1)
```

<div align="center">
    1 start bit + 8 data bits + 1 stop bit = 10 bits por byte
    <br>
    <br>
</div>

|Campo|Descrição|
|--|--|
|Start bit| Indica o início da transmissão. A linha vai de nivel alto (idle) para nível baixo|
|Data bits|Normalmente 7, 8 ou 9 bits. Contém os dados a serem transmitidos|
|Paridade|Bit de verificação de erro (par ou ímpar). Usado para detectar falhas simples|
|Stop bit|1 ou 2 bits em nível alto, indicando o fim da transmissão|

O seu funcionamento gira em torno de:
1. O transmissor coloca os dados na linha serial (bit a bit).
1. O receptor monitora a linha e detecta a borda de descida (start bit)
1. Ambos os lados contam os tempos com base na ***baud rate*** combinada 
1. O receptor lê os bits de dados nos tempos esperados e valida com o(s) stop bit(s)

Diferente do One-Wire, a UART é normalmente full-duplex, a transmissão e recepção de dados é feita simultaneamente, pois usa dois fios de dados.

|Fio|Função|
|--|--|
|TX|Transmitir dados|
|RX|Receber Dados|

O fio TX de um dispositivo deve ser conectado ao RX do outro, e vice-versa.

### USART

Pode-se dizer que o USART é uma versão mais completa do protocolo UART. O diferencial é que pode operar em modo síncrono, mas isso exige uma linha extra para transmitir o clock.

Ter o clock elimina ambiguidades de sincronização, permite taxas de transferência maiores que o modo assíncrono, porém exige um fio extra.

```makefile
CLK:  _-_-_-_-_-_-_-_-_-_-_-_-_-_  
DATA: d0 d1 d2 d3 d4 d5 d6 d7
```

## Protocolo SPI

O **SPI** (Serial Peripheral Interface) é um protocolo de comunicação serial síncrono, desenvolvido originalmente pela Motorola. Ele é amplamente utilizado em microcontroladores, sensores, memórias e displays devido à sua alta velocidade de transmissão e simplicidade de implementação.

- Síncrono: usa um sinal de clock compartilhado entre mestre e escravo
- Full-duplex: Permite a transmissão e recepção de maneira simultanea.
- Velocidade: Pode chegar facilmente a dezenas de megabits por segundo (até centenas de Mbps em versões modernas)

Permite uma comunicação múltipla para vários dispositivos no barramento, utilizando o CS (ou SS) chip select para selecionar qual escravo receberá os dados enviados, sem necessidade de endereçamento. Porém não permite multi-mestre.

|Fio|Nome|Função|
|--|--|--|
|MOSI|Master out slave in|Dados do mestre para o escravo|
|MISO|Master in slave out|Dados do escravo para o mestre|
|SCLK|Serial clock|Clock gerado pelo mestre|
|SS (ou CS)|Slave Select (ou Chip Select)|Seleciona qual escravo está ativo|

>PS.: Cada escravo precisa de um pino CS dedicado, a não ser que se use lógica adicional (como decodificadores).

O SPI possui 4 modos de operação baseados em duas configurações
- CPOL (Clock polarity): define se o clock inativo fica em nível alto ou baixo.
- CPHA (Clock phase) define em qual borda do clock os dados são amostrados (subida ou descida).

Isso permite compatibilidade com diferentes dispositivos.

```makefile
CLK :  _-_-_-_-_-_-_-_-_-_  
MOSI: |d0|d1|d2|d3|d4|d5|d6|d7|  
MISO: |q0|q1|q2|q3|q4|q5|q6|q7|
```

## Protocolo I²C

O **_I²C_** (Inter-Integrated Circuit, também chamado de IIC) é um protocolo de comunicação serial síncrono criado pela Philips na década de 80. Ele foi projetado para ser simples, barato em número de fios e eficiente em curtas distâncias, especialmente dentro de placas de circuito.

Sua topologia permite uma comunicação em um barramento assim como os outros protocólos ele permite multi-mestre e multi-escravo. Porém sua velocidade é inferior comparado ao SPI. Suas velocidades limitam-se a: 

- 100 kbps (Standard Mode)
- 400 kbps (fast mode)
- 1 Mbps (Fast mode plus)
- 3.4 Mbps (Hight-Speed mode)

O protocolo I²C utiliza o conceito de endereçamento tal qual o protocolo One-Wire e  


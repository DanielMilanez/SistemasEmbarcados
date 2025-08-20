## 📡 Protocolos de comunicação

Neste documento encontram-se meus estudos a respeito de protocolos de comunicação. A principio iremos discutir sobre o protocolo *ONE-WIRE*, *UART* e *USART*, e depois iremos progredir para 
*I2C*, *SPI*.


### One Wire

O protocolo de comunicação *One-Wire* é uma tecnologia serial que utiliza apenas um único fio de dados (além do GND) para comunicação entre dispositivos. Foi desenvolvido pela *Dallas Semiconductor*(hoje *Maxim Integrated*) e existe desde os anos 1980.

*Ao utilizar este protocolo a comunicação fica restrita em ~16 kbps (modo normal) ou até 125 kbps em overdrive*

O One-Wire não utiliza um sinal de clock separado. Em vez disso, baseia-se na largura de pulso (ou seja, na duração dos níveis lógicos no fio de dados) para sincronizar e transmitir os bits.

Existem algumas caracteristicas importantes para que haja uma plena comunicação entre os dispositivos.

|Caracteristica|Descrição|
|--|--|
|Número de fios| 2 (Dados e GND)|
|Topologia suportada|Barramento|
|Distância típica|Até 100m (precisa de pull-up)|
|Velocidade de comunicação|Baixa, restrita em ~16 kbps ou até 125 kbps em overdrive|
|Alimentação parasita|Existem alguns dispositivos que podem ser alimentados pelo prórpio fio de dados, sem usar o vcc separadamente|
|Endereçamento|Cada dispositivo possui um endereço único de 64bits gravados de fábirca|

O **One-Wire** é um protocolo ***half-duplex*** (os dados trafegam em um sentido de cada vez). Ele é ideal para aplicações com poucos pinos disponíveis ou quando a quantidade de conexões deve ser minimizada.

### Como ele funciona?

Como mencionado, o protocolo utiliza a largura do pulso (tempo de sinal em nível baixo ou alto) para representar os bits transmitidos, já que não há um sinal de clock dedicado.

1. Reset e presença: 

    Quando o protocolo se iniciia o mestre (microcontrolador) puxa a linha de dados para baixo. E isso faz com que os perifericos respondam com um *pulso de presença*, indicando que estão conectados e prontos.

1. Transmissão de bits:

    Enfim ocorre a transmissão de bits, a comunicação é feita bit a bit, com "slots" temporais definidos.

    - Ao esrever um bit o mestre puxa a linha para LOW por um tempo curto (1) ou longo (0) 

    - Ao realizar a leitrua o mestre puxa a linha para LOW brevemente, depois a "solta", apos um breve momento, o slave começa a transmitir os dados, podendo ser tempos lognos ou curtos.

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

O DS28E18 possui um buffer de 512 bytes na SRAM o que permite que seja possivel carregar inúmeros comandos I2C ou então SPI. Assim, quando for carregado o conrolador envia uma ordem para executar a sequência armazenada, fornecer energia e coletar dados de periféricos conectados via I2C ou SPI. Um comando one wire subsequente lê os dados coletados do sensor.

Existem ao todo três tipos de comandos
- Comandos de função ROM one-wire
- Comandos de função do dispositivo DS28E18
- Comandos do sequenciador DS28E18

Ao enviar um comando para o periferico o mesmo envia este comando via barramento I2C ou SPI e retorna a linha one-wire um NACK ou ACK dependendo se a comunicação foi sucedida ou não.

O protocolo One-Wire é simples, eficiente e extremamente útil em aplicações com limitações de hardware, como sensores distribuídos. Dispositivos como o DS18B20 (temperatura) e DS28E18 (ponte I²C/SPI) demonstram a versatilidade dessa tecnologia

## Protocolo UART e USART

O UART é um protocolo de comunicação serial assíncrono. RS-232 TTL serial, Bluetooth serial, USB-to-serial se comunicam dessa forma, sem mencionar outros exemplos.

No UART, não há sinal de clock compartilhado entre os dispositivos. Em vez disso os dois lados devem estar configurados com a mesma taxa de transimissão, BAUD RATE, e seguem uma convenção de inicício e fim de cliclos.

Cada byte de dados enviado pela UART é envolvido por bits de controle. O formato típico de transmissão é 

1 start bit + 8 data bits + 1 stop bit = 10 bits por byte

|Campo|Descrição|
|--|--|
|Start bit| Indica o início da transmissão. A linha vai de nivel alto (idle) para nível baixo|
|Data bits|Normalmente 7, 8 ou 9 bits. Contém os dados a serem transmitidos|
|Paridade|Bit de verificação de error (par ou ímpar). Usado para detectar falhas simples|
|Stop bit|1 ou 2 bits em nível alto, indicando o fim da transmissão|

O seu funcionamento gira em torno de
1. O mestre coloca os dados na linha serial (bit a bit).
1. O receptor monitora a linha e detecta a borda de descida (start bit)
1. Ambos os lados contam os tempos com base na ***baud rate*** combinada 
1. O receptor lê os bits de dados nos tempos esperados e valida com o(s) stop bit(s)

Diferente do One-Wire, a UARt é normalmente full-duplex, a transmissão e recepção de dados é feita simultaneamente, pois usa dois fios de dados."

|Fio|Função|
|--|--|
|TX|Transmitir dados|
|RX|Receber Dados|

O fio TX do mestre é conectado no RX do escravo e o TX do escravo é conectado no RX do mestre.




# Guia para Programar ESP32 em MicroPython

---

## 1. Baixar o firmware (.bin) do MicroPython para ESP32

Primeira coisa que precisamos fazer é baixar os drivers respectivos para programarmos em MicroPython. Para isso, instale o arquivo `.bin` do site oficial do MicroPython para ESP32.

No meu caso, estou utilizando uma **ESP32-S3-WROOM-1-N16R8**. Basta acessar o site:

[https://micropython.org/download/#esp32](https://micropython.org/download/#esp32)

Pressione `CTRL + F` e digite por **WROOM** para encontrar a placa. Caso não a encontre, pesquise pelo nome exato que está escrito na sua placa e, se precisar, pergunte a uma IA para fornecer o driver para esse modelo.

---

## 2. Instalar o esptool e preparar a placa

Acesse o terminal do seu computador e instale a biblioteca esptool com o seguinte comando:

```bash
pip install esptool
```
Depois, abra o Gerenciador de Dispositivos no Windows e verifique qual porta COM o ESP32 está conectado (no meu caso, é a COM7).

## 3. Apagar a memória flash do ESP32
No terminal, execute o comando para apagar a memória da placa:

```bash
python -m esptool --port COM7 erase_flash
```
Esse comando limpará a memória do ESP32, permitindo a instalação do firmware.

## 4. Gravar o firmware MicroPython no ESP32

Para instalar o arquivo .bin na placa, execute:

```bash
python -m esptool --port COM7 write_flash 0x1000 ESP32_GENERIC-20250911-v1.26.1.bin
```

Obs: Substitua o nome do arquivo .bin pelo arquivo que você baixou correspondente ao seu modelo de placa, por exemplo:
ESP32-S3-N8R2-MPY.bin

## 5. Instalar a extensão PyMakr no VS Code

Para facilitar o envio e gerenciamento dos seus códigos MicroPython, instale a extensão ***PyMakr*** no VS Code. Ao instala-lo 

### Resumo dos comandos
```bash
pip install esptool
python -m esptool --port COM7 erase_flash
python -m esptool --port COM7 write_flash 0x1000 ESP32-S3-N8R2-MPY.bin
```

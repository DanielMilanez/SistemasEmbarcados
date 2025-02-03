void printb(unsigned char reg){
    for (int i = 7; i >= 0; --i){
        (reg >> i) & 1 ? putchar('1') : putchar('0');
    }
}
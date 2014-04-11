DES
============

This is an implementation in C of DES (Data Encryption Standard).

This is to be used only for 64 bits **exactly**. For shorter/longer files, use a [mode of operation][1] on this DES cipher.

[DES][2] is a broken cypher and this work is intended for educational purpose.

[1]: http://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
[2]: http://en.wikipedia.org/wiki/Data_Encryption_Standard

Author
------

* David Wong
* Hugo Bonnin
* Jacques Monin

Files
----

* **DES.c** and **DES.h** contain the functions used in the DES algorithm.

* **main.c** builds the algorithm and allows you to encrypt/decrypt an input file.

Use make to build desbox.

    $ make
    
    $ desbox --help

* **genkey.c** is a key generator that prevents weak keys. Use it if you don't have any key to use.

Use make to build the keygen.

    $ make genkey

    $ ./genkey

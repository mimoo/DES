DES
============

This is an implementation in C of DES (Data Encryption Standard).  

[DES][1] is broken cypher and this work is for education purpose.

[1]: http://en.wikipedia.org/wiki/Data_Encryption_Standard


Author
------

* David Wong
* Hugo Bonnin
* Jacques Monin

Files
----

**DES.c** and **DES.h** contain the functions used in the DES algorithm.

**main.c** builds the algorithm and allows you to encrypt/decrypt an input file.

use make to build desbox.

    $ make
    
    $ desbox --help
    
for more info

**genkey.c** is a key generator that prevents weak keys. Use it if you don't have any key to use.
Use make to build it and launch it without arguments.

    $ make genkey

    $ ./genkey

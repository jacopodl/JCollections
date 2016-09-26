![Language C](https://img.shields.io/badge/Language-C-orange.svg)
![LGPLv3 License](https://img.shields.io/badge/license-LGPL3-blue.svg)
![](https://img.shields.io/badge/version-2.0.0-green.svg)
![](https://travis-ci.org/jacopodl/JCollections.svg?branch=master)

JCollections
============
JCollections are free and open source libraries for the C language that provide implementations of the most common data structures.

*Getting the code*
------------------
Check out the latest version with:
    
    $ git clone http://github.com/jacopodl/jcollections
or download .zip from [here](https://github.com/jacopodl/JCollections/archive/master.zip).

*Building library:*
-------------------
JCollections uses cmake for automate the build process, you can build library in this way:

    $ cd jcollections
    $ cmake CMakeLists.txt
    $ make
If the build finishes without errors, the compiled library will be located in the bin directory and related headers file will be located in include directory.
*Tests*
-------
If you want to test the newly compiled library, you can run the following command:

    $ make test
    
Using JCollections
------------------
To use this library in your project you must simply include jcollections.h
```c
    #include "jcollections.h"
```

License
-------
GNU LGPL V 3.0 http://www.gnu.org/licenses/

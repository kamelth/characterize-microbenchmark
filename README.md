# To build .c and run in one command
```bash
gcc -o main main.c && ./main
```

# TO run benchmark on vvadd
```bash
./build/vvadd -i naive
```

# TO run benchmark on naive mmult
```bash
./build/mmult -i naive -m 50 -n 50 -p 50
```

# TO run benchmark on blocking opt mmult
```bash
./build/mmult -i opt -m 50 -n 50 -p 50 -b 128
```


Test Cases

Case 1: Small Square Matrices
	•	Test Parameters:
	•	m = 100, n = 100, p = 100

    Naive:                   1222646 ns - 0.0012 second
    Block: 
        •	b        =    2 :  1441667 ns - 0.0014 second
        •	b        =    4 :   972499 ns - 0.0009 second
        •	b        =    8 :   777961 ns - 0.0007 second
        •	b        =   16 :   757123 ns - 0.0007 second
        •	b        =   32 :   898935 ns - 0.0008 second
        •	b        =   64 :  1103474 ns - 0.0011 second
        •	b        =  128 :  1301837 ns - 0.0013 second
        •	b        =  256 :  1305477 ns - 0.0013 second
        •	b        =  512 :  1304746 ns - 0.0013 second
        •	b        = 1024 :  1324966 ns - 0.0013 second
        •	b        = 2048 :  1304781 ns - 0.0013 second
        •	b        = 4096 :  1303826 ns - 0.0013 second
        •	b        = 8192 :  1303826 ns - 0.0013 second




Case 2: Medium Square Matrices
	•	Test Parameters:
	•	m = 500, n = 500, p = 500

    Naive:                 248797574 ns - 0.2487 second
    Block: 
        •	b        =    2 :   214294843 ns - 0.2142 second
        •	b        =    4 :   128104149 ns - 0.1281 second
        •	b        =    8 :   101232312 ns - 0.1012 second
        •	b        =   16 :    97986893 ns - 0.0979 second
        •	b        =   32 :   114954918 ns - 0.1149 second
        •	b        =   64 :   156692887 ns - 0.1566 second
        •	b        =  128 :   173407331 ns - 0.1734 second
        •	b        =  256 :   237455468 ns - 0.2374 second
        •	b        =  512 :   258524774 ns - 0.2585 second
        •	b        = 1024 :   259142737 ns - 0.2591 second
        •	b        = 2048 :   258458005 ns - 0.2584 second
        •	b        = 4096 :   267117649 ns - 0.2671 second
        •	b        = 8192 :   258701981 ns - 0.2587 second


Case 4: Large Matrices
	•	Test Parameters:
	•	m = 2500, n = 3000, p = 2100

    Naive:                34075741500   ns - 34.07 second
    Block: 
        •	b        =    2 :     ns -  second
        •	b        =    4 :     ns -  second
        •	b        =    8 :     ns -  second
        •	b        =   16 :      ns -   second
        •	b        =   32 :     ns -   second
        •	b        =   64 :     ns -  second
        •	b        =  128 :     ns -   second
        •	b        =  256 :     ns -   second
        •	b        =  512 :     ns -   second
        •	b        = 1024 :     ns -  second
        •	b        = 2048 :     ns -   second
        •	b        = 4096 :     ns -   second
        •	b        = 8192 :     ns -   second
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
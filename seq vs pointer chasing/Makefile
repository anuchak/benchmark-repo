clean:
	rm main main2 main3

all_seq:
	g++-11 -O2 -ftree-vectorize -fopt-info-vec-all -o main main.cpp

all_ptr_chase:
	g++-11 -O2 -ftree-vectorize -fopt-info-vec-all -o main2 main2.cpp

all_block_ptr_chase:
	g++-11 -O2 -ftree-vectorize -fopt-info-vec-all -o main3 main3.cpp

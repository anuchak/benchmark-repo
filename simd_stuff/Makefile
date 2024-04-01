clean:
	rm main1 main2 main3

all: main1 main2 main3

main1:
	g++-11 -O3 -ftree-vectorize -fopt-info-vec-all -msse -o main1 main1.cpp

main2:
	g++-11 -O3 -ftree-vectorize -fopt-info-vec-all -mavx -o main2 main2.cpp

main3:
	g++-11 -O3 -ftree-vectorize -fopt-info-vec-all -mavx512f -o main3 main3.cpp



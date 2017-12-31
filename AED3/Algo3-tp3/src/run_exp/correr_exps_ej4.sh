cd ..

make clean
make

./tp3 4 -expRandom 30 > ../exp/Entradas/ej4/ej4_entrada_30_config1.txt
./tp3 4 -exp 120 < ../exp/Entradas/ej4/ej4_entrada_30_config1.txt > ../exp/Salidas/ej4/ej4_exp1.txt
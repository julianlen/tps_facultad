make clean
make

./tp3 1 -exp 30 <../exp/entrada_exp1.txt >../exp/salida_exp1_ej1.data
#./tp3 1 -exp 28 <../exp/entrada_exp2_ej1.txt >../exp/salida_exp2_ej1.data
./tp3 1 -expRandom 100 >../exp/entrada_exp3_ej1.txt
./tp3 1 -exp 100 <../exp/entrada_exp3_ej1.txt >../exp/salida_exp3_ej1.data

for i in {0..22}; do  echo  $i  $( fac.sh $i ) $(fac.sh $((2*i)))  |  dc -e '?sSsFsN25klS4lN^lF2^*2lN*1-*lN2*3+4lN1+^2***r/_48r/f'; done | sed 's/^-/_/' | tac  | tr "\n" " " | dc -e '25k?3v3*4/+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p+p'

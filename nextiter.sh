#!/bin/bash
#echo 13 18 5 |
awk '{print $1,$3*$3*$1+$2*$2,$2*$3*2}' | factor | awk '(NR==1){a=$1}(NR==2){for (i=2;i<=NF;i++){t[i-2]=$i;q++}}(NR==3){for (i=2;i<=NF;i++){n[i-2]=$i;r++}}END{for(k=0;k<q;k++){for(l=0;l<r;l++){if(n[l]==t[k]){n[l]=1;t[k]=1}}}s=1;for(k=0;k<q;k++){s*=t[k]}u=1;for(l=0;l<r;l++){u*=n[l]}; print a,s,u,s*s-a*u*u}' | tr ":" " "

# w=-2;t=154;; n=23.;a=45.

#;@out; p [0:20] 0lt -1 , (t+x*t/n)**2 - (n+x)**2*a - 1 -a*w ,t**2+x**2*t**2/n**2+2*t**2/n*x  - a*n**2 - a*x**2 -2*a*x*n -1-a*w, (t**2/n**2-a)*x**2+(2*t**2/n-2*a*n)*x+(t**2-a*n**2-1-a*w); k=(t**2/n**2-a);l=(2*t**2/n-2*a*n);m=(t**2-a*n**2-1-a*w);print (-l+sqrt(l**2-4*k*m))/2/k , (-l-sqrt(l**2-4*k*m))/2/k


# (t+x*t/n)**2 - (n+x)**2*a - 1 -a*w  = 0 

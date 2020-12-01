
Radc=6e3 %
Cadc=4e-12
fadc=21e6
N=12
k=15
Rain=((k-0.5)/(fadc*Cadc*log(2^(N+2))))-Radc; % Rain=11.4k impedenza del canale AD. 

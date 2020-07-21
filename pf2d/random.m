close all;

Gam = 0.5;
dGause = 0.001
for i=1:1000
    noi = Gam*(dGause*randn);
    
    x(i) = noi;
end

for i=1:1000
    noi = Gam*(dGause*randn);
    
    y(i) = noi;
end

plot(x,y,'r.');
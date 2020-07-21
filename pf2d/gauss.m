close all;

sigma = 0.5;

for n=1:2000
%    k(n) = -1 + 0.01*n;
    k(n) = randn;
    
    nx(n) = 1/sqrt(pi*sigma*sigma)*exp(-(k(n)*k(n))/(sigma*sigma));
end

for n=1:2000
%    k(n) = -1 + 0.01*n;
    k(n) = randn;
    
    ny(n) = 1/sqrt(pi*sigma*sigma)*exp(-(k(n)*k(n))/(sigma*sigma));
end


plot(nx,ny,'r.');


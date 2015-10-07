x = [12 8 1 -4 6 -7];
N = length(x);
X = zeros(N,1);

for k = 0:N-1
    for n = 0:N-1
        X(k+1) = X(k+1) + x(n+1)*exp(-j*pi/2*n*k);
    end
end

X

function g = grad(X,y,theta)
g = zeros(length(theta),1);

m = length(y);
n = length(theta);

for i=1:n
	sum = 0;
for j=1:m
	temp = y(j)*(1-sigmoid(X(j,:)*theta))*X(j,i) - (1-y(j))*sigmoid(X(j,:)*theta)*X(j,i);
    sum = sum + temp;
    end
    g(i) = sum;
    end;
function h = hessian(X,y,theta)


m = length(y);
n = length(theta);

h= zeros(n, n);

for i=1:n
	for j=1:n
		sum = 0;
	for z=1:m
		temp = -sigmoid(X(z,:)*theta) * (1 - sigmoid(X(z,:)*theta)) * X(z,i) * X(z,j);
	    sum = sum + temp;
	    end
	    h(i,j) = sum;
	    end
	    end;
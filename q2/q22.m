r = randi([1,1000],1,4);
mu = zeros(4,157);

for i=1:4
mu(i,:) = X(r(i),:);
end

c = zeros(m,1);
s = zeros(30,1);
ratios = zeros(30,1);

%repeat until convergence
for z=1:30
	z
for i=1:m
	temp = zeros(4,1);
	for j=1:4
		temp(j) = norm(X(i,:) - mu(j,:))^2;
	end
	[dummy, c(i)] = min(temp);
	%temp
	%c(i)
	%pause;
end

sum_s = 0;
for i=1:m
sum_s = sum_s + norm(X(i,:) - mu(c(i),:))^2;
end
s(z) = sum_s;

for i=1:4
	temp = X(i==c,:);
	no = size(temp,1);
	mu(i,:) = sum(temp)/no;
end

predicted = zeros(4,1);
for j=1:4
	predicted(j) = mode(y(j==c,:));
end


errors = zeros(4,1);
for j=1:4

t = (predicted(j) == y(j==c,:));
errors(j) = size(t,1) - sum(t);

end

ratios(z) = sum(errors)/m;

end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% first run readdata, it will store X(1000 x 157),
% pixels(1 x 157) and y(1000 x 1) as global variables
% then run visualize - give X's index as the only
% argument. Then run q2.
% c will have the clusters having values 1,2,3,4
% k means run for 30 iterations
% ratios has the ratios of mis classified to total
% s is S given in ass2 pdf
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


global X; global pixels; global y;
m = size(X,1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% picking 4 random indices from 1 to 1000
r = randi([1,1000],1,4);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mu = zeros(4,157);

for i=1:4
mu(i,:) = X(r(i),:);
end

c = zeros(m,1);
s = zeros(30,1);
ratios = zeros(30,1);
%repeat until convergence
for z=1:30
	for i=1:m
		temp = zeros(4,1);
		for j=1:4
			temp(j) = norm(X(i,:) - mu(j,:))^2;
		end
		[dummy, c(i)] = min(temp);
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


plot(ratios);
xlabel('iteration');
ylabel('error');
title('error vs number of iterations');
figure()
plot(s);
xlabel('iteration');
ylabel('s');
title('s vs number of iterations');








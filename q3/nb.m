load('data/q3-all.mat');
shuffledArray = data.raw(randperm(size(data.raw,1)),:);
m = size(shuffledArray,1);

train = shuffledArray(1:m/3,1:19);
y_train = shuffledArray(1:m/3,20);
train_raw = shuffledArray(1:2*m/3,1:20);
m_train = size(train,1);

test = shuffledArray((2*m/3+1:end),1:19);
y_test = shuffledArray((2*m/3+1:end),20);


fractions = [0.01 0.02 0.03 0.05 0.1 0.3 0.5 0.7 0.9 1];
accuracies = zeros(length(fractions),1);
m_test = size(test,1);

plotdata = zeros(10,2);

for f=1:length(fractions)
avgaccuracy = 0;
for ff=1:5
train_raw = train_raw(randperm(size(train_raw,1)),:);
m = size(train_raw,1);
train = train_raw(1:floor(fractions(f)*m),1:19);
y_train = train_raw(1:floor(fractions(f)*m),20);
m_train = size(train,1);


% prior of 0 and 1
prior = [sum(y_train) length(y_train)-sum(y_train)];
prior = prior./length(y_train);

%conditional is a matrix of size 5 x 2
conditional = zeros(5,2);

%extracting examples with label as 0 - class 1
class0 = train((y_train==1),:);

class1 = train((y_train==0),:);

for i=1:5
	for j=1:size(class0,1)
		for k=1:19
			if(class0(j,k) == i)
				conditional(i,1) = conditional(i,1) + 1;
			end
		end
	end
end

for i=1:5
	for j=1:size(class0,1)
		for k=1:19
			if(class0(j,k) == i)
				conditional(i,2) = conditional(i,2) + 1;
			end
		end
	end
end

for i=1:size(conditional,1)
for j=1:size(conditional,2)
	conditional(i,j) = conditional(i,j)+1;
end
end

%n is the total number of "words"
n0 = size(class0,1) * size(class0,2);
n1 = size(class1,1) * size(class1,2);

for i=1:5
	conditional(i,1) = conditional(i,1)/(n0+5);
	conditional(i,2) = conditional(i,2)/(n1+5);

end

%%%%%%now testing

pred = zeros(size(test,1),1);
for z=1:length(test)
est0 = log(prior(1));
est1 = log(prior(2));
for i=1:5
	est0 = est0+log(conditional(test(z,i),1));
	est1 = est1+log(conditional(test(z,i),2));

end

if(est0<est1)
	pred(z) = 1;

end


end
avgaccuracy = avgaccuracy+sum(pred==y_test)/length(y_test)*100;
end
plotdata(f,1) = fractions(f);
plotdata(f,2) = avgaccuracy/5;

end

plot(plotdata(:,1),plotdata(:,2));
xlabel('fraction of data used');
ylabel('accuracy');
title('Learning curve');



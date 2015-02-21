load('data/q3-sub.mat');
X = data.X;
y = data.Y;
m = length(y);

shuffledArray = data.raw(randperm(size(data.raw,1)),:);
train = shuffledArray((1:2*m/3),1:6);
y_train = shuffledArray((1:2*m/3),7);
train_raw = shuffledArray(1:2*m/3,1:7);

test = shuffledArray((2*m/3+1:end),1:6);
y_test = shuffledArray((2*m/3+1:end),7);
fractions = [0.01 0.02 0.03 0.05 0.1 0.3 0.5 0.7 0.9 1];
accuracies = zeros(length(fractions),1);
m_test = size(test,1);
test = [ones(m_test,1) test];

plotdata = zeros(10,2);

for f=1:length(fractions)

	fractions(f)
train_raw = train_raw(randperm(size(train_raw,1)),:);
m = size(train_raw,1);
train = train_raw(1:floor(fractions(f)*m),1:6);
y_train = train_raw(1:floor(fractions(f)*m),7);


%adding the intercept term
m_train = size(train,1);
train = [ones(m_train,1) train];
theta = zeros(size(train,2),1);

n = length(theta);


%------------------------- training ---------------------------
oldtheta = 100.*ones(n,1);
epsilon = 0.00001;

while(norm(theta - oldtheta)>epsilon)
	oldtheta = theta;
	theta = theta - pinv(hessian(train,y_train,theta))*grad(train,y_train,theta);
end;

%disp(' resulting cofficients are..');
theta;


%-------------------------------------------------------

%------------------------- testing ---------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

temp = test * theta ;
%temp = train * theta;
pos = find(temp >= 0.5);
neg = find(temp < 0.5);
p = zeros(m_test,1);
%p = zeros(m_train,1);
p(pos)=1;
p(neg)=0;
accuracy = 100*sum(p==y_test)/size(test,1)
%accuracy = 100*sum(p==y_train)/size(train,1)
accuracies(f)=accuracy;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%-------------------------------------------------------

plotdata(f,1) = fractions(f);
plotdata(f,2) = accuracy;
end

plot(plotdata(:,1),plotdata(:,2))
xlabel('fraction of data used');
ylabel('accuracy');
title('Learning curve');







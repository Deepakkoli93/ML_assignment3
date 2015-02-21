cc=hsv(3);
hold off;
train = load('q1atrain.txt');
test = load('q1atest.txt');
validation = load('q1avalidation.txt');

h1=plot(train(:,1),train(:,2),'color',cc(1,:));
hold on;
h2=plot(validation(:,1),validation(:,2),'color',cc(2,:));
h3=plot(test(:,1),test(:,2),'color',cc(3,:));
legend([h1 h2 h3],{'training','validation','test'});

train = load('q1btrain.txt');
test = load('q1btest.txt');
validation = load('q1bvalidation.txt');
title('one step lookahead');
figure();
h1=plot(train(:,1),train(:,2),'color',cc(1,:));
hold on;
h2=plot(validation(:,1),validation(:,2),'color',cc(2,:));
h3=plot(test(:,1),test(:,2),'color',cc(3,:));
legend([h1 h2 h3],{'training','validation','test'});
title('using information gain');


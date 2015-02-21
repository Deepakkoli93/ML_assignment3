%%%%%part b implementing PCA
global avgmat;
unrolledavgmat = double(reshape(avgmat,361,1));
sigma = zeros(361,361);
m = 2429;
for i=1:m
	num = num2str(i);
	while(length(num) < 5)
		num = strcat('0',num);
	end
	x_i = reshape(double(imread(strcat('data/face',num,'.pgm'))),361,1);
	sigma = sigma + (x_i-unrolledavgmat)*transpose(x_i-unrolledavgmat);
end

sigma = sigma./m;

[u dummy1 dummy2] = svd(sigma); 
ureduced = u(:,1:50);

top5 = [];

%now scaling top 5 eigenfaces
for i=1:5
temp = ureduced(:,i);
oldmin = min(temp);
oldmax = max(temp);
oldrange = oldmax - oldmin;
newmin = 0;
newmax = 255;
newrange = newmax-newmin;

scale = (temp-oldmin)./oldrange;
temp = (newrange*scale)+newmin;
top5 = [top5 temp];
end

disp('displaying the top 5 eigenfaces');
for i=1:5
	figure();
	imshow(reshape(uint8(top5(:,i)),19,19));
end

fid = fopen('projected.txt','w');


for i=1:m
	num = num2str(i);
	while(length(num) < 5)
		num = strcat('0',num);
	end
	x_i = reshape(double(imread(strcat('data/face',num,'.pgm'))),361,1);
	proj_i = ureduced' * x_i;
	for j=1:length(proj_i)
	fprintf(fid,'%f ',proj_i(j));
	end
	fprintf(fid,'\n');
	
end

























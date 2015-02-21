% part a, average face and display it

global avgmat;
avgmat = zeros(19,19);
for i=1:2429
	num = num2str(i);
	while(length(num) < 5)
		num = strcat('0',num);
	end
	%strcat('face',num)
	avgmat = avgmat + double(imread(strcat('data/face',num,'.pgm')));
end
avgmat = avgmat./2429;
avgmat = uint8(avgmat);
imshow(avgmat);

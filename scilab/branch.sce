branch = csvRead("../branch.csv");

data_size = size(branch, '*');

win = window('hm', data_size);
branch_fft = fft(branch .* win);

f_data = (1:data_size/2) / data_size;

clf;
plot(f_data, abs(branch_fft(1:size(f_data,'*'))));

branch = csvRead("../branch.csv");

data_size = size(branch, '*');

win = window('hm', data_size);
branch_fft = fft(branch .* win);

f_data = data_size ./ (1:data_size/2);

clf;
plot(f_data, abs(branch_fft(size(f_data,'*'):-1:1)));

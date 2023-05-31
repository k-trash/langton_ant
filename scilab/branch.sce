branch = csvRead("../branch.csv");
branch_fft = fft(branch);

data_size = size(branch, '*');
f_data = (1:data_size/2) / data_size;

clf;
plot(f_data, abs(branch_fft(1:size(f_data,'*'))));

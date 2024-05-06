


clear nuc
nuc = serialport("/dev/tty.usbmodem14203", 230400);

buffer_len = 10000;
plot_len = 1000;
lim3Dplot = 2;
T = 10e-3;


niter = 0;
acc_buffer = zeros(3,buffer_len);
gyro_buffer = zeros(3,buffer_len);

phi_acc_est_buffer = NaN(1,buffer_len);
theta_acc_est_buffer = NaN(1,buffer_len);
phi_est_buffer = NaN(1,buffer_len);
theta_est_buffer = NaN(1,buffer_len);

accact = zeros(3,1);
gyroact = zeros(3,1);

cf_alpha = 0.9;


figure(1)
tiledlayout(2,1)
nexttile
hold on
for i = 1:3
    accplot(i) = plot(1:plot_len, acc_buffer(i,1:plot_len));
end
legend(["X" "Y" "Z"])
hold off
nexttile
hold on

for i = 1:3
    gyroplot(i) = plot(1:plot_len, gyro_buffer(i,1:plot_len));
end
legend(["X" "Y" "Z"])
hold off




tic
while(1)
    
    %% accel(6)gyro(6)mag(6)temp(2) - 20 bytes
    
    while((read(nuc, 1, "uint8")))
    end
    fprintf("dt = %.5f\n", toc*1000);
    tic
   %%Parsing
    data = read(nuc, 20, "uint8"); 
    data;
    read_time = toc*1000;

    for i = 1:3
        accact(i) = typecast(uint16(data(2*i-1)*2^8 + data(2*i)), 'int16');
    end
    for i = 1:3
        gyroact(i) = typecast(uint16(data(2*i-1+6)*2^8 + data(2*i+6)), 'int16');
    end

    accact_double = double(accact)./16384;
    gyroact_double = double(gyroact)./131;

    

    
    %%Buffer update
    acc_buffer = circshift(acc_buffer, 1,2);
    acc_buffer(:,1) = accact_double;

    gyro_buffer = circshift(gyro_buffer, 1,2);
    gyro_buffer(:,1) = gyro_buffer(:,2) + T*gyroact_double;

    
    
    %% Plot update
    for i = 1:3
        accplot(i).YData = acc_buffer(i,1:plot_len);
    end
    for i = 1:3
        gyroplot(i).YData = gyro_buffer(i,1:plot_len);
    end
    phiplot.YData = phi_acc_est_buffer(1:plot_len);
    thetaplot.YData = theta_acc_est_buffer(1:plot_len);
    
    cfphiplot.YData = phi_est_buffer(1:plot_len);
    cfthetaplot.YData = theta_est_buffer(1:plot_len);

    
    total_time = toc*1000;
    fprintf("read: %.2f, total: %.2f, comp: %.2f\n", read_time, total_time,total_time-read_time)
    niter = niter+1
end

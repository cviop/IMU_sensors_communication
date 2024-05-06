


clear nuc
nuc = serialport("/dev/tty.usbmodem14203", 230400);

buffer_len = 10000;
plot_len = 1000;
lim3Dplot = 2;
T = 10e-3;


niter = 0;
acc_buffer = NaN(3,buffer_len);
gyro_buffer = NaN(3,buffer_len);

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

figure(2)
phiplot = plot(1:plot_len, phi_acc_est_buffer(1:plot_len), LineStyle="--");
hold on
thetaplot = plot(1:plot_len, theta_acc_est_buffer(1:plot_len), LineStyle="--");
cfphiplot = plot(1:plot_len, phi_est_buffer(1:plot_len), LineWidth=1);
cfthetaplot = plot(1:plot_len, theta_est_buffer(1:plot_len), LineWidth=1);
legend(["phi_acc" "theta acc" "phi" "theta"])
ylim([-pi/2 pi/2])
hold off

phi_est = 0;
theta_est = 0;



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

    phi_acc_est = real(atan(accact_double(2)./accact_double(3)));
    theta_acc_est = real(asin(accact_double(1)));

    rotmat = [1 sin(phi_acc_est(1))*tan(theta_acc_est(1)) cos(phi_acc_est(1))*tan(theta_acc_est(1)); 0 cos(phi_acc_est(1)) -sin(phi_acc_est(1))];

    ang_dot_est = rotmat*[gyroact_double(1) gyroact_double(2) gyroact_double(3)]';
    phi_dot_est = ang_dot_est(1);
    theta_dot_est = ang_dot_est(2);


    %% CF
    
    phi_est = phi_acc_est*cf_alpha + (1-cf_alpha)*(phi_est + T*phi_dot_est);
    theta_est = theta_acc_est*cf_alpha + (1-cf_alpha)*(theta_est+T*theta_dot_est);
    
    %%Buffer update
    acc_buffer = circshift(acc_buffer, 1,2);
    acc_buffer(:,1) = accact_double;

    gyro_buffer = circshift(gyro_buffer, 1,2);
    gyro_buffer(:,1) = gyroact_double;

    phi_acc_est_buffer = circshift(phi_acc_est_buffer, 1,2);
    phi_acc_est_buffer(1) = phi_acc_est;

    theta_acc_est_buffer = circshift(theta_acc_est_buffer, 1,2);
    theta_acc_est_buffer(1) = theta_acc_est;

    phi_est_buffer = circshift(phi_est_buffer, 1, 2);
    phi_est_buffer(1) = phi_est;

    theta_est_buffer = circshift(theta_est_buffer, 1, 2);
    theta_est_buffer(1) = theta_est;

    
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

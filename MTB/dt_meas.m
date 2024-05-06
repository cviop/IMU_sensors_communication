

while(1)
    
    %% accel(6)gyro(6)mag(6)temp(2) - 20 bytes
    
    while((read(nuc, 1, "uint8")))
    end
    fprintf("dt = %.5f\n", toc*1000);
    tic
    data = read(nuc, 20, "uint8"); 
end

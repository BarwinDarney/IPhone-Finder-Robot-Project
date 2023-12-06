%Shivam Patel
%Bonus Project EECS1011
%CarLogic

clear all; close all;
%create serial port object and connect to serial port (COM Port 9)
s1 = serialport('COM9', 9600);
%create serial port object and connect to serial port (COM Port 11)
s2 = serialport('COM11', 9600);
%initialize variables
direction = 0;
j = 0;  
pastRssiValues = 0;
%make a figure
figure;

% Open the serial port s1 
fopen(s1);
%open the serial port s2
fopen(s2);
%loops every second since the rssi value gets sent to matlab every second
%because of the delay(1000); command in RssiChecker script
for i = 1:100
    %Store rssi value read from serial port s1
    rssiValue = fscanf(s1, '%d');
    disp((rssiValue));
    if (j == 2)
        pastRssiValues = rssiValue;
    end
    %reason why it is a range of +/- 5 is because rssi is inconsistant 
    % since it can be interfered with easily for one value so there should 
    % be a range that it makes sending what direction to drive more
    % accurate
    if (rssiValue < -29)
    if (rssiValue >= pastRssiValues -5 || rssiValue < pastRssiValues + 5)
        direction = 1;
        %Print value of direction variable into serial port s2
        fprintf(s2, '%d', direction);
        
    else 
        direction = 2;
        %Print value of direction variable into serial port s2
        fprintf(s2, '%d', direction);
    end    
    elseif (rssiValue > -29);
        direction = 3;
        %Print value of direction variable into serial port s2
        fprintf(s2, '%d', direction);
    else
        % Output error message incase it gets to this point in the code for
        % some reason
        disp("Error!");
    end
    
    %if remainder is 0
    if mod(i,2) == 0
    j = 1;
    else
    j = 2;
    end
    % Array for rssi and time
    rssi(i) = rssiValue;
    time(i) = i;
    pause(0.1);
    %ploting stuff on graph and set the labels
    plot(time, rssi);
    title('Rssi Value of Car Based On Time Driven');
    xlabel('Time [Seconds]');
    ylabel('Rssi');
    %updates figure
    drawnow;
    
end
    












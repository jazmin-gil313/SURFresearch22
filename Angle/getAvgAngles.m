%***PLEASE READ ALL COMMENTS BEFORE RUNNING***
%code works for cvs file output from gad_to_cvs.c code in folder

%set total points for while loop
totalPoints = TBD;
%input the number of lines, to allocate space for output matrix
output = zeros(TBD,2);


counter=3;
j=1;
angleNum =0;
locAngle=0.0;
globAngle = 0.0;

%change 'data' to name of imported MATRIX
  %ensure imported data is a matrix, not table*
while counter < totalPoints+1
    if(data(counter,1) ~= j)
        locAngle = locAngle/angleNum;
        output(j,1) = real(j);
        output(j,2) = real(locAngle);
        globAngle = globAngle +locAngle;

        angleNum =0;
        locAngle=0.0;

        counter =counter+2;
        j = j+1;
    end
    
    x1 = data(counter-2,2);
    y1 = data(counter-2,3);
    x2 = data(counter-1,2);
    y2 = data(counter-1,3);
    x3 = data(counter,2);
    y3 = data(counter,3);
    
    dA = sqrt((x1-x2)^2+ (y1-y2)^2);
    dB = sqrt((x2-x3)^2+ (y2-y3)^2);
    dC = sqrt((x1-x3)^2+ (y1-y3)^2);

    if(dA ~= 0 && dB~=0 && dC~=0)
        input = (dA^2+dB^2-dC^2) / (2*dA*dB);
        locAngle = locAngle + acos(input);
    end

    angleNum = angleNum+1;

    counter=counter+1;
    
end
locAngle = locAngle/angleNum;
output(j,1) = real(j);
output(j,2) = real(locAngle);
globAngle = globAngle +locAngle;

%writes the gobal average on the last line
output(j+2,2) = real(globAngle/j);

%wwrite output to speficied fileName
 %check the writematric page on matlab site get the list of allowed extensions
writematrix(output, fileName);

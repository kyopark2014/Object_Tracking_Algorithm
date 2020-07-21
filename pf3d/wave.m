close all;
clear all;

load px.txt;
load py.txt;
load object.txt;
load estimate.txt;

s = size(px);
Nt=s(1);
Np=s(2);

figure(1);
load angle.txt
plot(angle(:,1));
hold;
color=1;
for m=2:Np
    if color==1
        plot(angle(:,m),'r');
	elseif color == 2
        plot(angle(:,m),'b');
	elseif color == 3
        plot(angle(:,m),'g');
	elseif color == 4
        plot(angle(:,m),'k');
	elseif color == 5
        plot(angle(:,m),'m');
    elseif color == 6
        plot(angle(:,m),'c');
    end
    
    color = color+1;
	if color==7
		color = 1;
    end
end
grid;

figure(2);
plot(object(:,1),object(:,2),'b*-');
hold;
plot(estimate(:,1),estimate(:,2),'r*-');
legend('object','estimate',4);
grid;

figure(3);
plot(object(:,1),object(:,2),'b*-');
hold;
plot(estimate(:,1),estimate(:,2),'r-');
legend('object','estimate',4);

color=1;
for m=1:Nt
    if color==1
        plot(px(m,:),py(m,:),'r.');
	elseif color == 2
		plot(px(m,:),py(m,:),'b.');
	elseif color == 3
		plot(px(m,:),py(m,:),'g.');
	elseif color == 4
		plot(px(m,:),py(m,:),'k.');
	elseif color == 5
		plot(px(m,:),py(m,:),'m.');
    end
    
    color = color+1;
	if color==6
		color = 1;
    end
end

grid;
    
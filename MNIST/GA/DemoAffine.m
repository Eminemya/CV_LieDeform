function DemoAffine

load DemoPoints;

h1=figure;
h2=figure;
for i=1:size(Points, 2)
    

P1=Points{1, i};
P2=Points{2, i};


disp(['Pointset sizes ..' num2str([size(P1, 2) size(P2, 2)])]);
tic;
AA=GetAffine2D(P1, P2, 0.1);
toc;

PP1=AA*P1;

figure(h1); hold off;
plot(P1(1, :), P1(2, :), 'r*'); hold on;
plot(P2(1, :), P2(2, :), 'b*'); drawnow;

figure(h2);hold off;
plot(PP1(1, :), PP1(2, :), 'r*'); hold on;
plot(P2(1, :), P2(2, :), 'b*'); drawnow;

disp(['Pause .... Press enter to continue ...']);

pause;
end

% To use this function, set the variable im to the image you want
% to analyze and then just type bc like this:
%
% >> im=MR_image;
% >> bc;



set(gcf,'doublebuffer','on')
 
%the mouse-click sets a flag for point aquisition 
set(gcf,'windowbuttondownfcn','mousedown=1;');
set(gcf,'windowbuttonupfcn','mouseup=1;');
set(gcf,'windowbuttonmotionfcn','mousemotion=1;');
 
brightness_slider=uicontrol('style','slider','Value',.5,'position',[80 0 160 30],'callback',['brightness=get(brightness_slider,''value'');','disp(num2str(brightness));']);

contrast_slider=uicontrol('style','slider','Value',.5,'position',[300 0 160 30],'callback',['contrast=get(contrast_slider,''value'');','disp(num2str(contrast));']);

%make a control to stop the loop
uicontrol('style','pushbutton',...
    'string','Quit', ...
    'position',[0 0 50 20], ...
    'callback','stopit=1;');
 
%start looping and waiting for a mouse click
stopit = 0;
mousedown = 0;
mouseup = 0;
mousemotion = 0;

old_brightness=0;
brightness=.5;
old_contrast=0;
contrast=.5;
while (stopit==0)
  
    if old_brightness~=brightness | old_contrast~=contrast
      old_brightness=brightness;
      old_contrast=contrast;
      imagesc(im,[brightness-contrast-.01 brightness+contrast+.01]);
      colormap('gray');
      drawnow;
    end
    
    %check for valid object and chek for line 1
    %and see if the mouse was clicked
    %fprintf(1,'foo is %d\n',foo);
    if   mousedown==1     
         
        %wait for the next click
        if mouseup == 1
            mouseup = 0;
            mousedown = 0;
            mousemotion = 0;
        end
    end
    
    drawnow
end  
close
close


function y= loglik(tem,im,sig,opt)
y=0;
if opt==1
    a0=find(tem==0);
    a1=find(tem==1);
    y= sum(log(normpdf(im(a0),0,sig)))+sum(log(normpdf(im(a1),1,sig)));
end




end

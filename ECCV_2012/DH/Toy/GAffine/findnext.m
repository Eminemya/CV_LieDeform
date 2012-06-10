function y=findnext(ratio,r_thres)

    [aa,bb]=hist(ratio,r_thres-0.005:0.01:0.995);
    [ee,dd]=max(aa(2:end));
    ind=find(ratio>=bb(dd)+0.005);
    y=ind(find(ratio(ind)<=bb(dd)+0.015,1,'first'));

end

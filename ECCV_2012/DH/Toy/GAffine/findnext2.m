function y=findnext2(ratio,r_thres)

    [aa,bb]=hist(ratio,r_thres-0.5:0.5:30);
    [ee,dd]=max(aa(2:end));
    ind=find(ratio>=bb(dd)+0.25);
    y=ind(find(ratio(ind)<=bb(dd)+0.75,1,'first'));

end

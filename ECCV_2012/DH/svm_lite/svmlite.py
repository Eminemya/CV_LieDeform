import scipy.io
mat = scipy.io.loadmat('mnist_all.mat')


#training
for i in range(1,10):

    a=open(str(i)+'_train.dat','w')
    a.write('#Training binary classifier for '+str(i)+'\n')
    for j in range(10):
        dd=mat['train'+str(j)]
        if j==i:
            #positive    
            st='1 '
        else:
            st='-1 '
        for ii in range(len(dd)):
            a.write(st+' '.join([str(b)+':'+str(c) for b, c in enumerate(dd[ii]) if c != 0])+'\n')
    a.close()
    """
    a=open(str(i)+'_test.dat','w')
    a.write('#Test binary classifier for '+str(i)+'\n')
    for j in range(10):
        dd=mat['test'+str(j)]
        for ii in range(10):
            a.write('0 '+' '.join([str(b)+':'+str(c) for b, c in enumerate(dd[ii]) if c != 0])+'\n')
    a.close()
    """

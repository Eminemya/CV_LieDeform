// C++ mex implementation of fwd_warp

#include <mex.h>
#include <cstring>
#include <cmath>


template<typename T>
void add_vote(T *I, T *W, int w, int h, int x, int y, T value, T weight)
{
    if (x >= 0 && x < w && y >= 0 && y < h)
    {
        int i = y + x * h;
        
        I[i] += weight * value;
        W[i] += weight;
    }
}


template<typename T>
void do_fwd_warp(int w, int h, 
        const mxArray *mxI, const mxArray *mxVx, const mxArray *mxVy, 
        const mxArray *mxM, mxArray *mxR)
{
    const T *I = (const T*)mxGetData(mxI);
    const T *Vx = (const T*)mxGetData(mxVx);
    const T *Vy = (const T*)mxGetData(mxVy);
    const bool *M = (const bool*)mxGetData(mxM);
    
    T *R = (T*)mxGetData(mxR);    
    
    int N = h * w;
    T *W = new T[N];
    std::memset(W, 0, sizeof(T) * N);
    
    // voting
    
    for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h; ++y)
        {
            int si = y + x * h;
            
            if (M[si])
            {            
                T v = I[si];
                T tx = T(x) + Vx[si];
                T ty = T(y) + Vy[si];

                int tx0 = (int)std::floor(tx);
                int ty0 = (int)std::floor(ty);
                int tx1 = tx0 + 1;
                int ty1 = ty0 + 1;

                T cx0 = T(tx1) - tx;
                T cx1 = T(1) - cx0;            
                T cy0 = T(ty1) - ty;
                T cy1 = T(1) - cy0;

                add_vote(R, W, w, h, tx0, ty0, v, cx0 * cy0);
                add_vote(R, W, w, h, tx0, ty1, v, cx0 * cy1);
                add_vote(R, W, w, h, tx1, ty0, v, cx1 * cy0);
                add_vote(R, W, w, h, tx1, ty1, v, cx1 * cy1);
            }
        }
    }
    
    // calculating results
    
   for (int i = 0; i < N; ++i)
   {
        if (W[i] > 0)
        {
            R[i] /= W[i];
        }
   }
                    
   delete[] W;
}



/**
 * Input
 *  [0]: I:     the source image
 *  [1]: Vx:    the x-field
 *  [2]: Vy:    the y-field
 *  [3]: M:     the indicator mask
 *
 * Output
 *  [0]: R:     the warped image
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // take input
    
    const mxArray *mxI = prhs[0];
    const mxArray *mxVx = prhs[1];
    const mxArray *mxVy = prhs[2];
    const mxArray *mxM = prhs[3];
    
    int h = (int)mxGetM(mxI);
    int w = (int)mxGetN(mxI);
        
    // prepare output
    
    mxClassID cid = mxGetClassID(mxI);    
    mxArray *mxR = mxCreateNumericMatrix(h, w, cid, mxREAL);
    
    // main
    
    switch (cid)
    {
        case mxDOUBLE_CLASS:
            do_fwd_warp<double>(w, h, mxI, mxVx, mxVy, mxM, mxR);
            break;
            
        case mxSINGLE_CLASS:
            do_fwd_warp<float>(w, h, mxI, mxVx, mxVy, mxM, mxR);
            break;
    }
    
    // output
    
    plhs[0] = mxR;
    
}



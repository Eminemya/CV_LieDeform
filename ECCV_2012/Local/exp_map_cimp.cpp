// exponentiation mapping of each point along a velocity field


#include <mex.h>
#include <cmath>

const double STOP_THRES = 1e-9;

inline double norm2(double x, double y)
{
    return std::sqrt(x*x + y*y);
}

class VField
{
public:
    VField(int w, int h, const double *Vx, const double *Vy)
    : m_w(w), m_h(h), m_Vx(Vx), m_Vy(Vy)
    {
        m_left = 0;
        m_right = w - 1;
        m_top = 0;
        m_bottom = h - 1;
    }
    
    bool in_field(double x, double y) const
    {
        return x >= m_left && x <= m_right && y >= m_top && y <= m_bottom;
    }
    
    double velo_x(int x, int y) const
    {
        return m_Vx[y + x * m_h];       
    }
    
    double velo_y(int x, int y) const
    {
        return m_Vy[y + x * m_h];
    }
            
    void get_velocity(double x, double y, double &vx, double &vy) const
    {
        int x0 = (int)std::floor(x);
        int x1 = (int)std::ceil(x);
        
        int y0 = (int)std::floor(y);
        int y1 = (int)std::ceil(y);
        
        double cx0, cx1, cy0, cy1;
        
        if (x0 < x1)
        {
            cx0 = x1 - x;
            cx1 = x - x0;
        }
        else
        {
            cx0 = 0.5;
            cx1 = 0.5;
        }
        
        if (y0 < y1)
        {
            cy0 = y1 - y;
            cy1 = y - y0;
        }
        else
        {
            cy0 = 0.5;
            cy1 = 0.5;
        }
        
       double c00 = cx0 * cy0;
       double c01 = cx0 * cy1;
       double c10 = cx1 * cy0;
       double c11 = cx1 * cy1;
       
       vx = c00 * velo_x(x0, y0) + 
            c01 * velo_x(x0, y1) + 
            c10 * velo_x(x1, y0) + 
            c11 * velo_x(x1, y1);
       
       vy = c00 * velo_y(x0, y0) + 
            c01 * velo_y(x0, y1) + 
            c10 * velo_y(x1, y0) + 
            c11 * velo_y(x1, y1);
    }
    
    
    bool trace(double x0, double y0, double &xt, double &yt, double t, double step) const
    {
        xt = x0;
        yt = y0;
        
        double vx = 0;
        double vy = 0;
        
        double r = t;
        
        while (r > 0)
        {
            if (in_field(xt, yt))
            {
               get_velocity(xt, yt, vx, vy);
               double vm = norm2(vx, vy);
               
               double s;
               if (r * vm > step)
               {
                   s = step / vm;
                   r -= s;
               }
               else
               {
                   s = r;
                   r = 0;
               }
               
               xt += s * vx;
               yt += s * vy;                              
               
               if (vm < STOP_THRES) return true;
            }
            else
            {
                return false;
            }
        }
        
        return true;
    }
    
    
private:
    int m_w;
    int m_h;
    const double *m_Vx;
    const double *m_Vy;
    
    double m_left;
    double m_right;
    double m_top;
    double m_bottom;
};



/**
 * Input:
 *  [0] Vx:     The x-field
 *  [1] Vy:     The y-field
 *  [2] xs:     The x-coordinates of source points
 *  [3] ys:     The y-coordinates of source points
 *  [4] ts:     The running time
 *  [5] s:      The maximum step length
 * 
 * Output:
 *  [0] xt:     The x-coordinates of target points [n x 1 double]
 *  [1] yt:     The y-coordinates of target points [n x 1 double]
 *  [2] M:      The map of within-field indicator [n x 1 bool]
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // take inputs
    
    const mxArray *mVx = prhs[0];
    const mxArray *mVy = prhs[1];
    const mxArray *mXs = prhs[2];
    const mxArray *mYs = prhs[3];
    const mxArray *mTs = prhs[4];
    const mxArray *mStep = prhs[5];
    
    int h = (int)mxGetM(mVx);
    int w = (int)mxGetN(mVx);
    
    int n = (int)mxGetNumberOfElements(mXs);
            
    const double *Vx = mxGetPr(mVx);
    const double *Vy = mxGetPr(mVy);
    const double *xs = mxGetPr(mXs);
    const double *ys = mxGetPr(mYs);
    const double *ts = mxGetPr(mTs);
    
    double step = mxGetScalar(mStep);
    
    // prepare output
    
    mxArray *mXt = mxCreateDoubleMatrix(n, 1, mxREAL);
    mxArray *mYt = mxCreateDoubleMatrix(n, 1, mxREAL);
    mxArray *mM = mxCreateLogicalMatrix(n, 1);
    
    double *xt = mxGetPr(mXt);
    double *yt = mxGetPr(mYt);
    bool *M = (bool*)mxGetData(mM);
        
    // main
    
    VField F(w, h, Vx, Vy);
    
    for (int i = 0; i < n; ++i)
    {
        M[i] = F.trace(xs[i], ys[i], xt[i], yt[i], ts[i], step);
    }
       
    // output
    
    plhs[0] = mXt;
    plhs[1] = mYt;
    plhs[2] = mM;
    
}

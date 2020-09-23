/** Hello World for ceres
 * Finding the minimum of the function 1/2*(a-x)^2
 * Using auto differential to compute jacobian matrix
 * Author: mhy
 */
#include "ceres/ceres.h"
#include "glog/logging.h"
#include<iostream>

struct CostFunctor
{
    //optional
    //following constructor is optional，if you need to pass other data to the struct然后采用才C++11标准中结构
    //using standard c++11 struct initialization list method to initialize the struct
    /*
    const data_type  _a, _b;  
    CostFunctor(data_type a,data_type b): _a ( a ), _b ( b ) { } 
    */
    double _a;
    CostFunctor(double a):_a(a){ }

    template<typename T>
    bool operator()(const T* const x, T* residual)const
    {
        residual[0] = _a - x[0]; //T(10.0) or 10.0 is both OK
        return true;
    }
};

int main(int argc, char **argv)
{   
    google::InitGoogleLogging(argv[0]);

    //problem: 1/2*(a-x)^2, initial value of x is 5.0
    double x = 5.0;
    double a = 20.0;

    ceres::Problem problem;

    ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction<CostFunctor,1,1>(new CostFunctor(a));
    //template <user-defined-functor, size-of-residual, size-of-param1>
    //what is in () is the constructor of the functor, you can put some  
    problem.AddResidualBlock(cost_function, NULL, &x); //x is the param to be change, which minimize the cost function

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;//show the detailed iteration step
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary); 

    std::cout<<summary.BriefReport()<<std::endl;
    std::cout<<"x: "<<5.0<<" -> "<<x<<std::endl;

    return 0;
}
/** Hello World for ceres
 * Finding the minimum of the function 1/2*(a-x)^2
 * Using numeric differentiation to compute jacobian matrix
 * Author: mhy
 * 
 * drawbacks:
 * 如果你的parameter block是在一流形上的，numerical differentiation可能会有问题
 * 因为这个方式只是扰动parameter block中单个coordinate，这也就表示我们认为parameter block在欧式空间里而忽视了流形的structure。
 * e.g. Pertubing the coordiantes of a unit quaternion will vilate the unit norm property of the parameter block.
 */ 

#include "ceres/ceres.h"
#include "glog/logging.h"
#include <iostream>

//The user defines a functor which computes the residual value 
//and construct a NumericDiffCostFunction using it
struct NumericDiffCostFunctor
{
    double _a;
    NumericDiffCostFunctor(double a):_a(a){ }

    bool operator()(const double* const x, double* residual) const
    {   
        residual[0] = _a - x[0];
        return true;
    }
};

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);

    double a = 10.0;
    double x = 5.0;

    ceres::Problem problem;
    ceres::CostFunction* cost_function = 
        new ceres::NumericDiffCostFunction<NumericDiffCostFunctor, ceres::CENTRAL, 1, 1>(new NumericDiffCostFunctor(a));
    //an extra template parameter that indicates the kind of finite differencing scheme 
    //to be used for computing the numerical derivatives
    //有三种numeric differentiation的方式，FORWARD， CENTRAL， RIDDERS

    problem.AddResidualBlock(cost_function, NULL, &x);

    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout<< summary.BriefReport() <<std::endl;
    std::cout<< "x: "<< 5.0<<" -> "<<x<<std::endl;
    
    return 0;
}

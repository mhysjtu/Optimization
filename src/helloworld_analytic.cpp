/** Hello World for ceres
 * Finding the minimum of the function 1/2*(a-x)^2
 * Using analytic jacobian matrix
 * Author: mhy
 * 
 * implementing CostFunction objects is a bit tedious. 
 * We recommend that unless you have a good reason to manage the jacobian computation yourself, 
 * you use AutoDiffCostFunction or NumericDiffCostFunction to construct your residual blocks.
 * 
 * more advanced ways of constructing and computing cost functions.
 * DynamicAutoDiffCostFunction
 * CostFunctionToFunctor
 * NumericDiffFunctor
 * ConditionedCostFunction 
 */

#include "ceres/ceres.h"
#include "glog/logging.h"

class SimpleCostFunction : public ceres::SizedCostFunction<1, 1> 
{
public:
    virtual ~SimpleCostFunction(){}

    //Evaluate is provided with an input array of parameters, 
    //an output array residuals for residuals 
    //and an output array jacobians for Jacobians
    virtual bool Evaluate(double const* const* parameters,
                          double* residuals, 
                          double ** jacobians) const
    {
        const double x = parameters[0][0];
        // f(x) = 10 - x
        residuals[0] = 10 - x;

        //The jacobians array is optional, Evaluate is expected to check when it is non-null, 
        //and if it is the case then fill it with the values of the derivative of the residual function
        if (jacobians && jacobians[0])
        {
            // f'(x) = -1
            // Since there's only 1 parameter and that parameter
            // has 1 dimension, there is only 1 element to fill in the
            // jacobians.
            jacobians[0][0] = -1;
        }
        return true;
    }
};

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);

    double x = 5.0;

    ceres::Problem problem;
    ceres::CostFunction* cost_function = new SimpleCostFunction;
    problem.AddResidualBlock(cost_function, NULL, &x);

    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout<< summary.BriefReport() <<std::endl;
    std::cout<< "x: "<< 5.0<<" -> "<<x<<std::endl;

    return 0;
}



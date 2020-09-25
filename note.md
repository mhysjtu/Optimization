## auto diff
```cpp
struct CostFunctor{
    template<typename T>
    bool operator()(const T* const x, T* residual)const{
        residual[0] = 10.0 - x[0]; 
        return true;
    }
};
ceres::CostFunction* cost_function = 
    new ceres::AutoDiffCostFunction<CostFunctor,1,1>(new CostFunctor);
```

## numeric diff
```cpp
struct CostFunctor{
    bool operator()(const double* const x, double* residual) const{   
        residual[0] = 10.0 - x[0];
        return true;
    }
};
ceres::CostFunction* cost_function = 
    new ceres::NumericDiffCostFunction<CostFunctor, ceres::CENTRAL, 1, 1>(new CostFunctor);
```

## analytic diff
```cpp
class SimpleCostFunction : public ceres::SizedCostFunction<1, 1> {
public:
    virtual ~SimpleCostFunction(){}
    virtual bool Evaluate(double const* const* parameters,
                          double* residuals, 
                          double ** jacobians) const{
        const double x = parameters[0][0];
        residuals[0] = 10 - x;

        if (jacobians && jacobians[0]){
            jacobians[0][0] = -1;
        }
        return true;
    }
};
ceres::CostFunction* cost_function = 
    new SimpleCostFunction;
```
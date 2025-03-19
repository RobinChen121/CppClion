/* Copyright 2025, Gurobi Optimization, LLC */

/* This example formulates and solves the following simple MIP model:

     maximize    x +   y + 2 z
     subject to  x + 2 y + 3 z <= 4
                 x +   y       >= 1
                 x, y, z binary
*/

#include "gurobi_c++.h"
using namespace std;

int main(int argc, char *argv[]) {
  try {
    // Create an environment
    GRBEnv env = GRBEnv(true);
    // env.set("LogFile", "mip1.log");
    env.set(GRB_IntParam_OutputFlag, 0);
    env.start();
    // Start an empty environment. If the environment has already been started,
    // this method will do nothing.

    // Create an empty model
    GRBModel model = GRBModel(env);

    // Create variables
    GRBVar x = model.addVar(0.0, 1.0, 1.0, GRB_BINARY, "x");
    GRBVar y = model.addVar(0.0, 1.0, 1.0, GRB_BINARY, "y");
    GRBVar z = model.addVar(0.0, 1.0, 2.0, GRB_BINARY, "z");

    // Set objective: maximize x + y + 2 z, 必须在定义变量之后
    // model.setObjective(x + y + 2 * z, GRB_MAXIMIZE);
    model.set(GRB_IntAttr_ModelSense,
              0); // 这个加上 addVar 中的 obj 系数后，跟 setObjective 等价

    // Add constraint: x + 2 y + 3 z <= 4
    model.addConstr(x + 2 * y + 3 * z <= 4, "c0");

    // Add constraint: x + y >= 1
    model.addConstr(x + y >= 1, "c1");

    // Optimize model
    model.optimize();

    model.write("mip1.lp");

    cout << x.get(GRB_StringAttr_VarName) << " " << x.get(GRB_DoubleAttr_X)
         << endl;
    cout << y.get(GRB_StringAttr_VarName) << " " << y.get(GRB_DoubleAttr_X)
         << endl;
    cout << z.get(GRB_StringAttr_VarName) << " " << z.get(GRB_DoubleAttr_X)
         << endl;

    cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
  } catch (GRBException e) {
    cout << "Error code = " << e.getErrorCode() << endl;
    cout << e.getMessage() << endl;
  } catch (...) {
    cout << "Exception during optimization" << endl;
  }

  return 0;
}

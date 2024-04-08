
#include <jluna.hpp>
int main() {
jluna::initialize(2,false,"d:/jjluna/bin/jluna.dll","","d:/ai4edll/ai4e.dll");
jluna::Main.safe_eval("println(\"abc\")");
jluna::Main.safe_eval("using ModelingToolkit");
jluna::Main.safe_eval("println(ModelingToolkit)");
jluna::Main.safe_eval("println(ModelingToolkit.ODESystem)");


  std::cout<<"hello"<<std::endl;
    return 0;
}

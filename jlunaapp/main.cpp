
#include <jluna.hpp>
int main() {
jluna::initialize(2,false,"D:/jjluna/bin/jluna.dll","","./ai4e.dll");
jluna::Main.safe_eval("println(\"abc\")");
  std::cout<<"hello"<<std::endl;
    return 0;
}

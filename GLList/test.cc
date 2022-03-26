#include "glthreads.h"

#include <iostream>
#include <memory.h>
#include <string>
using namespace std;
class emp
{
public:
    std::string name;
    unsigned int salary;
    std::string designation;
    Node node;

    emp(string name, unsigned int salary, string designation)
        : name(name), salary(salary), designation(designation)
    {
        node.init();
    }

    static void print_emp_details(const emp &emp)
    {
        std::cout << emp.name << std::endl;
        std::cout << emp.salary << std::endl;
    }
};

int main()
{
    emp emp1("ahmed", 1000, "hr");
    emp emp2("mohamed", 2000, "staff");
    emp emp3("ahmd", 6000, "vp");

    glthread emp_list;

    emp_list.initThread(offsetof(emp, node));

    emp_list.addNode(emp1.node);
    emp_list.addNode(emp2.node);
    emp_list.addNode(emp3.node);

    emp *ptr = nullptr;
    ITERATE_GL_THREADS_BEGIN(emp_list, emp, ptr)
    {
        emp::print_emp_details(*ptr);
    }
    ITERATE_GL_THREADS_END;

    return 0;
}

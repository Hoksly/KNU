#include <iostream>
#include <string>

class Procedure
{
public:
    std::string name;
    std::string description;
    std::string department;
    std::string category;

    void printProcedureDetails(std::ostream &os) const
    {
        os << "Procedure Name: " << name << std::endl;
        os << "Description: " << description << std::endl;
        os << "Department: " << department << std::endl;
        os << "Category: " << category << std::endl;
    }
};

class ProcedureBuilder
{
private:
    Procedure procedure;

public:
    ProcedureBuilder &setName(const std::string &name)
    {
        procedure.name = name;
        return *this;
    }

    ProcedureBuilder &setDescription(const std::string &description)
    {
        procedure.description = description;
        return *this;
    }

    ProcedureBuilder &setDepartment(const std::string &department)
    {
        procedure.department = department;
        return *this;
    }

    ProcedureBuilder &setCategory(const std::string &category)
    {
        procedure.category = category;
        return *this;
    }

    Procedure build()
    {
        return procedure;
    }
};

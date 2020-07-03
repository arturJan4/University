#include "kalkulator.hpp"

//functions with arity
using namespace Kalkulator;
std::map<std::string, double> zmienna::variables;
std::map<std::string, double> stala::constants;

bool Kalkulator::isNumber(std::string text)
{
    bool seperator = false; // decimal separator(either '.' or ',')
    size_t i = 0;
    if(text[i] == '-')
        ++i;

    while(i < text.length())
    {
        if(!seperator)
        {
            if(text[i] == '.' || text[i] == ',')
                seperator = true;
            else if (!isdigit(text[i]))
                return false;
        }
        else if (!isdigit(text[i]))
            return false;

        ++i;
    }
    return true;
}

double Kalkulator:: stringToDouble(std::string text)
{
    std::replace(text.begin(),text.end(),',','.'); //gdyby ktoś używał przecinkow
    return std::stod(text);
}

std::vector<std::string> Kalkulator::tokenize(const std::string& input, char delimiterP)
{
    //dzielimy na tokeny po spacji
    char delimiter = delimiterP;
    std::vector<std::string> tokens;
    size_t startPos = 0;
    size_t pos = input.find(delimiter);

    while(pos != std::string::npos)
    {
        tokens.push_back(input.substr(startPos, pos - startPos));
        startPos = pos + 1;
        pos = input.find(delimiter,startPos);
    }
    tokens.push_back(input.substr(startPos, std::min(pos, input.size()) - startPos + 1));

    return tokens;
}

void wyrazenie::parse()
{
    std::vector<std::string> tokens = tokenize(input,' ');
    stala temp("fi");//na potrzeby inicjalizacji

    //przydzielamy obiekty do nazwy
    for(const auto& i : tokens)
    {
        auto it = funkcja::reservedFunctions.find(i);
       if(it != funkcja::reservedFunctions.end())
       {
           objects.push(new funkcja(i));
           D(std::cout << i << " to funkcja\n");
       }
       else if(stala::isSet(i))
       {
           objects.push(new stala(i));
           D(std::cout << i << " to stala\n");
       }
       else if(zmienna::isSet(i))
       {
           objects.push(new zmienna(i));
           D(std::cout << i << " to zmienna\n");
       }
       else if(isNumber(i))
       {
           double val = stringToDouble(i);
           objects.push(new liczba(val));
           D(std::cout << i << " to liczba\n");
       }
       else
       {
           D(std::cout << "blad parsera:t" << i << "t\n");
           throw std::invalid_argument("nieznane wyrazenie: " + i + "\n");
       }
    }
    D(std::cout << "\n");
}

double wyrazenie::oblicz()
{
    std::stack<double> calcStack;

    symbol* temp;
    while(!objects.empty())
    {
        temp = objects.front();
        D(std::cout << temp->toString() << " ");
        auto it = funkcja::reservedFunctions.find(temp->toString());
        if(it != funkcja::reservedFunctions.end())
        {
            auto* temp2 = new funkcja(temp->toString());
            D(std::cout << temp2->toString() << " ");

            if(calcStack.empty())
                throw std::invalid_argument("cannot perform binary operation, not enough arguments: " + temp2->toString() + "\n");
            double valTop = calcStack.top();
            temp2->setArg1(valTop);
            calcStack.pop();

            if(temp2->getArity() == 2)
            {
                if(calcStack.empty())
                    throw std::invalid_argument("cannot perform unary operation, not enough arguments: " + temp2->toString() + "\n");

                temp2->setArg2(valTop); //change order of operands
                temp2->setArg1(calcStack.top());
                calcStack.pop();
            }

            calcStack.push(temp2->oblicz());
            delete temp2;
        }
        else
        {
            calcStack.push(temp->oblicz());
        }

        objects.pop();
    }

    if(calcStack.size() != 1)
        throw std::invalid_argument("too many operands\n");
    double val = calcStack.top();
    D(std::cout << " val: " << val << "\n");
    return val;
}

void interactiveCalc::loop()
{
    std::string line;
    while (!finish && std::getline(std::cin, line))
    {
        std::vector<std::string> polecenie = tokenize(line,' ');
        if(polecenie[0] == "print")
        {
            std::string expr;
            for(auto& i : polecenie)
            {
                if(i != "print")
                {
                    expr += i;
                    if(&i != &polecenie.back())
                        expr += " ";
                }
            }
            print(expr);
        }
        else if(polecenie[0] == "assign")
        {
            size_t first = line.find("assign ");
            first += polecenie[0].length();
            size_t last = line.find(" to", first);
            std::string expr = line.substr(first + 1, last - first - 1);
            D(std::cout << "wyrazenie: t" << expr << "t\n");

            last += 4;
            std::string symbol = line.substr(last, std::string::npos );
            D(std::cout << "zmienna: t" << symbol << "t\n");
            assign(expr,symbol);
        }
        else if(polecenie[0] == "clear")
        {
            clear();
        }
        else if(polecenie[0] == "exit")
        {
            exit();
        }
        else
        {
            std::clog << "nieznana komenda\n";
        }

    }
}

void interactiveCalc::print(std::string expr)
{
    try
    {
        auto *temp = new wyrazenie(std::move(expr));
        temp->parse();
        double val = temp->oblicz();
        D(std::cout << "wartosc(print) " << expr << val << "\n");
        std::cout << val << "\n";
        delete temp;
    }
    catch(std::invalid_argument& err)
    {
        std::clog << err.what();
    }
    catch (std::exception& exc) {
        std::clog << exc.what();
    }
}

void interactiveCalc::assign(std::string expr, const std::string& symbol)
{
    try
    {
        if(funkcja::reservedFunctions.find(symbol) != funkcja::reservedFunctions.end()
            || symbol.length() == 0 || symbol.length() > 7
            || symbol == "print" || symbol == "to" || symbol == "assign" || symbol == "clear" || symbol == "exit"
            || (symbol.find(' ') != std::string::npos)
            )
            throw std::invalid_argument("nieprawidlowa nazwa zmiennej (max 7 znakow, roznych od slow kluczowych, bez spacji) \n");

        auto *temp = new wyrazenie(std::move(expr));
        temp->parse();
        double val = temp->oblicz();
        D(std::cout << "wartosc(assign) " << expr << " to: " << val << "\n");

        if(stala::isSet(symbol))
            throw std::invalid_argument("blad - przypisanie do stalej \n");

        zmienna::setValue(symbol,val);
        delete temp;
    }
    catch(std::invalid_argument& err) {
        std::clog << err.what();
    }catch (std::exception& exc) {
        std::clog << exc.what();
    }
}

void interactiveCalc::clear()
{
    zmienna::clear();
}

void interactiveCalc::exit()
{
    finish = true;
}







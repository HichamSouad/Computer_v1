#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include <stdexcept>
#include <cstring>
#include <numeric> 

void removeSpacesAroundSigns(std::string& str) {
    str = std::regex_replace(str, std::regex(R"((\+|-)\s+)"), "$1");
}

void simplifyFraction(int& numerator, int& denominator) {
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

void printReducedForm(const std::map<int, double>& terms) {
    std::cout << "Reduced form: ";
    bool first = true;
    for (const auto& term : terms) {
        if (term.second != 0) {
            if (!first && term.second > 0) {
                std::cout << "+ ";
            }
            else if (!first && term.second < 0) {
                std::cout << "- ";
            }
            std::cout << std::abs(term.second) << " * "<< "X" << "^" << term.first << " ";
            first = false;
        }
    }
    std::cout << "= 0" << std::endl;
}

int polynomialDegree(const std::map<int, double>& terms) {
    int degree = 0;
    for (const auto& term : terms) {
        if (term.second != 0 && term.first > degree) {
            degree = term.first;
        }
    }
    return degree;
}

void calculSolutions(std::map<int, double>& terms) {
    int degree = polynomialDegree(terms);
    if (degree > 2) {
        std::cout << "The polynomial degree is greater than 2, I can't solve." << std::endl;
        return;
    }

    if (degree == 2) {
        std::cout << "Polynomial degree: 2" << std::endl;
        double a = terms[2];
        double b = terms[1];
        double c = terms[0];
        double delta = pow(b, 2) - 4 * a * c;
        if (delta > 0) {
            double x1 = (-b - std::sqrt(delta)) / (2 * a);
            double x2 = (-b + std::sqrt(delta)) / (2 * a);
            std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            std::cout  << x1 << std::endl;
            std::cout  << x2 << std::endl;
        } else if (delta == 0) {
            double x = -b / (2 * a);
            std::cout << "Discriminant is zero, the solution is:" << std::endl;
            std::cout  << x << std::endl;
        } else {
            std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;

            int realNumerator = -b;
            int realDenominator = 2 * a;

            simplifyFraction(realNumerator, realDenominator);

            int imagNumerator = std::sqrt(-delta);
            int imagDenominator = 2 * a;

            simplifyFraction(imagNumerator, imagDenominator);

            std::cout  << realNumerator << "/" << realDenominator << " - " 
                      << imagNumerator << "i/" << imagDenominator << std::endl;
            std::cout  << realNumerator << "/" << realDenominator << " + " 
                      << imagNumerator << "i/" << imagDenominator << std::endl;
        }
    } else if (degree == 1) {
        std::cout << "Polynomial degree: 1" << std::endl;
        double a = terms[1];
        double b = terms[0];
        double x = -b / a;
        std::cout << "The solution is:" << std::endl;
        std::cout  << x << std::endl;
    } else {
        if (terms[0] == 0) {
            std::cout << "Polynomial degree: 0" << std::endl;
            std::cout << "Any real numbers are solutions." << std::endl;
        } else {
            std::cout << "No solution." << std::endl;
        }
    }
}

void parsePolynomial(std::string& termsStr, std::map<int, double>& terms, bool isRightSide = false) {
    std::vector<std::string> termsVec;
    size_t pos = 0;
    while ((pos = termsStr.find("+", pos)) != std::string::npos) {
        termsVec.push_back(termsStr.substr(0, pos));
        termsStr.erase(0, pos + 1);
        pos = 0;
    }
    termsVec.push_back(termsStr);
    for (const auto& term : termsVec) {
        double coefficient = 1.0;
        size_t xPos = term.find('x');
        int exponent = term.find('^') != std::string::npos ? std::stoi(term.substr(term.find('^') + 1)) : 1;
        if (xPos != std::string::npos) {
            std::string coeffStr = term.substr(0, xPos);
       
                if (!coeffStr.empty() && coeffStr != "+" && coeffStr != "-") {
                    coefficient = std::stod(coeffStr);
                } else if (coeffStr == "-") {
                    coefficient = -1.0; 
                }
                coefficient = std::stod(term);
            
        } 
        else {
            coefficient = std::stod(term);
        }
        terms[exponent] += isRightSide ? -coefficient : coefficient;
    }
}


int main(int argc, char* argv[]) {
    
    try
    {
        if (argc < 2){
        std::cout << "please provide enter equation." << std::endl;
        std::string input;
        std::getline(std::cin, input, '\n');
        argv[1] = new char[input.length() + 1];
            std::strcpy(argv[1], input.c_str());
                
        }
        std::string arg  = argv[1];
            std::string leftTerms = arg.substr(0, arg.find('='));
            std::string rightTerms = arg.substr(arg.find('=') + 1);
        
        
            std::vector<std::string> leftTermsVec;
            std::vector<std::string> rightTermsVec;
        
            std::map<int, double> terms;
            removeSpacesAroundSigns(leftTerms);
            removeSpacesAroundSigns(rightTerms);
        
            size_t pos = 0;
            while ((pos = leftTerms.find("-", pos)) != std::string::npos) {
                leftTerms.replace(pos, 1, "+-");
                pos += 2; 
            }
            pos = 0;
            while ((pos = rightTerms.find("-", pos)) != std::string::npos) {
                rightTerms.replace(pos, 1, "+-");
                pos += 2;
            }
        
            parsePolynomial(leftTerms, terms);
            parsePolynomial(rightTerms, terms, true);
        
            //Reduced form output
            printReducedForm(terms);
            //calcul solutions :
            calculSolutions(terms);
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: "<< e.what() << '\n';
    }
    

    return 0;
}


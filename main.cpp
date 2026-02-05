#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <regex>
#include <cmath>

void removeSpacesAroundSigns(std::string& str) {
    str = std::regex_replace(str, std::regex(R"((\+|-)\s+)"), "$1");
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

int printPlynomialDegree(const std::map<int, double>& terms) {
    int degree = 0;
    for (const auto& term : terms) {
        if (term.second != 0 && term.first > degree) {
            degree = term.first;
        }
    }
    std::cout << "Polynomial degree: " << degree << std::endl;
    return degree;
}


void calculSolutions(std::map<int, double>& terms) {
    int degree = printPlynomialDegree(terms);
    if (degree > 2) {
        std::cout << "The polynomial degree is greater than 2, I can't solve." << std::endl;
        return;
    }
    if (degree == 2) {
        double a = terms[2];
        double b = terms[1];
        double c = terms[0];
        double delta = pow(b, 2) - 4 * a * c;
        std::cout << "Delta: " << delta << std::endl;
        if (delta > 0) {
            double x1 = (-b - std::sqrt(delta)) / (2 * a);
            double x2 = (-b + std::sqrt(delta)) / (2 * a);
            std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            std::cout << "x1 = " << x1 << std::endl;
            std::cout << "x2 = " << x2 << std::endl;
        } else if (delta == 0) {
            double x = -b / (2 * a);
            std::cout << "Discriminant is zero, the solution is:" << std::endl;
            std::cout << "x = " << x << std::endl;
        } else {
            double realPart = -b / (2 * a);
            double imaginaryPart = std::sqrt(-delta) / (2 * a);
            std::cout << "Discriminant is strictly negative, there are no real solutions." << std::endl;
            std::cout << "The two complex solutions are:" << std::endl;
            std::cout << "x1 = " << realPart << " - " << imaginaryPart << "i" << std::endl;
            std::cout << "x2 = " << realPart << " + " << imaginaryPart << "i" << std::endl;
        }
    } else if (degree == 1) {
        double a = terms[1];
        double b = terms[0];
        double x = -b / a;
        std::cout << "The solution is:" << std::endl;
        std::cout << "x = " << x << std::endl;
    } else {
        if (terms[0] == 0) {
            std::cout << "Any real numbers are solutions." << std::endl;
        } else {
            std::cout << "No solution." << std::endl;
        }
    }
}

void parsePolynomial(std::string& termsStr, std::map<int, double>& terms, bool isRightSide = false) {
    std::vector<std::string> leftTermsVec;
    size_t pos = 0;
    while ((pos = termsStr.find("+", pos)) != std::string::npos) {
        leftTermsVec.push_back(termsStr.substr(0, pos));
        termsStr.erase(0, pos + 1);
    }
    leftTermsVec.push_back(termsStr);
    for (const auto& term : leftTermsVec) {
        double coefficient = 1.0;
        size_t xPos = term.find('x');
        int exponent = term.find('^') != std::string::npos ? std::stoi(term.substr(term.find('^') + 1)) : 1;
        if (xPos != std::string::npos) {
            std::string coeffStr = term.substr(0, xPos);
            try {
                if (!coeffStr.empty() && coeffStr != "+" && coeffStr != "-") {
                    coefficient = std::stod(coeffStr);
                } else if (coeffStr == "-") {
                    coefficient = -1.0; 
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid coefficient: " << coeffStr << std::endl;
                throw;
            }

            try {
                coefficient = std::stod(term);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid term: " << term << std::endl;
                throw;
            }
        } else {
            try {
                coefficient = std::stod(term);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid term: " << term << std::endl;
                throw;
            }
        }
        terms[exponent] += isRightSide ? -coefficient : coefficient;
    }
}
int main(int argc, char* argv[]) {
    
   
    if (argc < 2){
        std::cin >> argv[1];
        return 1;
    }
    std::string arg  = argv[1];
    std::string leftTerms = arg.substr(0, arg.find('='));
    std::string rightTerms = arg.substr(arg.find('=') + 1);

    std::vector<std::string> leftTermsVec;
    std::vector<std::string> rightTermsVec;

    // std::cout << "Left terms: " << leftTerms << std::endl;
    // std::cout << "Right terms: " << rightTerms << std::endl;

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
    //calcul delta :
    calculSolutions(terms);
    return 0;
}


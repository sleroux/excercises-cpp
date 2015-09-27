#include <iostream>
#include <memory>
#include <math.h>
#include <vector>

struct Factor {
    int value;
    std::unique_ptr<Factor> left_factor;
    std::unique_ptr<Factor> right_factor;
    Factor(int value) : value(value) {}

private:
    void prime_factors(std::vector<int>& primes);

public:
    void print_prime_factors();
};

void
Factor::print_prime_factors()
{
    std::vector<int> primes;
    prime_factors(primes);
    std::string primes_string = "Prime factors for " + std::to_string(value) + " are: ";

    for (auto& prime : primes) {
        primes_string += std::to_string(prime) + " ";
    }

    std::cout << primes_string << std::endl;
}

void
Factor::prime_factors(std::vector<int>& primes)
{
    if (left_factor == nullptr && right_factor == nullptr) {
        primes.push_back(value);
    } else {
        left_factor->prime_factors(primes);
        right_factor->prime_factors(primes);
    }
}

void
generate_factor_tree(Factor* factor)
{
    // Start at largest potential divisor and go down until it divides
    auto largest = floor(sqrt(factor->value));
    for (int divisor = largest; divisor > 1; divisor--) {
        if (factor->value % divisor == 0) {
            int left = divisor;
            int right = factor->value / divisor;
            factor->left_factor = std::unique_ptr<Factor>(new Factor(left));
            factor->right_factor = std::unique_ptr<Factor>(new Factor(right));
            generate_factor_tree(factor->left_factor.get());
            generate_factor_tree(factor->right_factor.get());
        }
    }
}

int main()
{
    int n;
    std::cout << "Integer to factor: ";
    std::cin >> n;

    auto root = std::unique_ptr<Factor>(new Factor(n));
    generate_factor_tree(root.get());
    root->print_prime_factors();

    return 0;
}

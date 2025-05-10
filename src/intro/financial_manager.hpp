#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Investment {
protected:
    double m_capital;

public:
    explicit Investment( double capital ) : m_capital( capital ) {}
    virtual ~Investment() = default;
    virtual void settle() = 0;
    [[nodiscard]] double getCapital() const {
        return m_capital;
    }
};

class Saving : public Investment {
public:
    explicit Saving( double capital ) : Investment( capital ) {}
    void settle() override {
        m_capital *= 1 + 1.78 / 100;
    }
};

class Fund : public Investment {
public:
    explicit Fund( double capital ) : Investment( capital ) {}
    void settle() override {
        int rate  = rand() % 20 + 90;
        m_capital = m_capital * rate / 100.0;
    }
};

class Person {
private:
    double m_principal;
    vector< Investment* > investments;

public:
    explicit Person( double principal ) : m_principal( principal ) {}
    ~Person() {
        for ( auto inv : investments ) {
            delete inv;
        }
    }
    void addInvest( Investment* inv ) {
        investments.push_back( inv );
        m_principal -= inv->getCapital();
    }
    double settle() {
        double total = 0.0;
        for ( auto inv : investments ) {
            inv->settle();
            total += inv->getCapital();
            delete inv;
        }
        investments.clear();
        m_principal += total;
        return m_principal;
    }
};

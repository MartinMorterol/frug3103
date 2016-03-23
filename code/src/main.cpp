#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>

#include "iterateurFoncteur.hpp"
#include "paramInfo.hpp"
#include "can_be_check.hpp"

struct Bidon {
    int a = 5 ;
    int b = 6 ;
    int c = 7 ;

    std::vector<std::reference_wrapper<int>> vec;


    Bidon() {
        vec.push_back(std::ref(a));
        vec.push_back(std::ref(b));
        vec.push_back(std::ref(c));
    }

    // Le parcourt des cases
    using iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::iterator,std::UnWrappe<int>>;
    using const_iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::const_iterator,std::UnWrappe<int>>;

    inline iterator begin()                     { return iterator(vec.begin());         }
   // inline const_iterator begin() const         { return const_iterator(vec.begin());   }
    inline iterator end()                       { return iterator(vec.end());           }
    //inline const_iterator end() const           { return const_iterator(vec.end());     }
};





template<class InputIterator, class UnaryPredicate >
InputIterator find_if_maison (InputIterator first, InputIterator last, UnaryPredicate pred)
{
    static_assert(nbParam<UnaryPredicate>()==1,"La fonction ne doit avoir qu'un seul parametre !");
    static_assert(
        std::is_convertible<typename InputIterator::value_type,
                            decltype(typeParam<0,UnaryPredicate>())>::value,
                  "Les types ne sont pas convertible entre eux :)"
                );

    static_assert(std::is_same<bool,decltype(typeRetour<UnaryPredicate>())>::value,
                  "La méthode doit retourner un bool");
    return std::find_if(first,last,pred);
}

template <class T>
bool foo (T a) { (void)a; return true;}

bool ok (){ return true;}
int main()
{
    using namespace std;

    std::vector<int> test =  { 1 ,2 ,3 , 4 };
   auto it = find_if_maison(test.begin(), test.end() ,[](int s){(void)s; return true;} );
   //auto test3 = std::find_if(test.begin(), test.end(), 5);
   //auto test4 = find_if_maison(test.begin(), test.end() ,5 );

    auto test5 = find_if_maison(test.begin(), test.end() ,[](int x) { return foo(x); });
    //auto test6 = find_if(test.begin(), test.end() ,foo<int> );

    //auto test6 = find_if(test.begin(), test.end() ,[](auto s){(void)s; return true;} );
    //auto test7 = find_if_maison(test.begin(), test.end() ,[](auto s){(void)s; return true;} );
    cout << *it << endl;



    Bidon b;
    for (auto& elem : b) {
        std::cout << elem << std::endl;
    }


    //auto monIterateurBegin =  FoncteurIterator<std::vector<std::reference_wrapper<int>>::iterator,decltype(maLambda)>(b.vec.begin(),maLambda);

    auto maLambda = [] (const std::reference_wrapper<int>& refWrap ) { return refWrap.get(); };
    //auto maLambda = [] ( auto refWrap ) { return refWrap.get(); };

//    cout << typeid(decltype(can_be_checked<int>()).name() << endl;
    /*cout << nbParam(maLambda) <<endl;
    cout << typeid(const std::reference_wrapper<int>&).name() << endl;
    cout << typeid(decltype(typeParam<0>(maLambda))).name() << endl;
    cout << typeid(int).name() << endl;
    cout << typeid(decltype(typeRetour(maLambda))).name() << endl;*/
    can_be_checked<int>::type testqsdf;

    return 0;
}

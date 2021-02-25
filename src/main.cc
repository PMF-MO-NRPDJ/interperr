#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <vector>
#include <numeric>

#include <dune/common/parallel/mpihelper.hh>
#include <dune/grid/yaspgrid.hh>
#include <dune/geometry/quadraturerules.hh>
#include <dune/localfunctions/lagrange/lagrangecube.hh>

// Funkcija na kojoj računamo grešku interpolacije. Ne treba mijenjati.  
template <typename Element>
struct Funkcija{
  static const int dim = Element::dimension;
  Element element;
  Funkcija(Element const & el) : element(el) {}
  // Operator funkcijskog poziva.
  double operator()(Dune::FieldVector<double, dim> const & x_local) const {
      auto x_global = element.geometry().global(x_local);
      double rez = 1.0;
      for(int i=0; i<dim; ++i)
          rez *= std::sin(x_global[i]);
      return rez;
  }
};

// Rutina za računanje greške interpolacije.
template <typename GridView, typename FEM>
double interpolationError(GridView const & gv, FEM const & fem){
    using RangeType = typename FEM::Traits::LocalBasisType::Traits::RangeType;
    const int dim = GridView::dimension;
    auto const & basis = fem.localBasis();
    auto const & interp = fem.localInterpolation();
    std::vector<RangeType> phi; // vrijednosti baznih funkcija
    std::vector<double> coeff;  // interpolacijski koeficijenti

    double global_l2_error2 = 0.0;  // greška interpolacije na kvadrat
    for(auto const & elem : elements(gv)){
       Funkcija funkcija(elem);  
       // Vaš kod koji računa global_l2_error2 (L2 norma greške na kvadrat)
       // ....
    
    
    }
    return std::sqrt(global_l2_error2);
}



int main(int argc, char** argv)
{
    Dune::MPIHelper& helper = Dune::MPIHelper::instance(argc, argv);

    // Grid
    const int dim = 2;
    using GridType = Dune::YaspGrid<dim>;
    using GridView = typename GridType::LeafGridView;

    Dune::FieldVector<double, dim> L(5);
    L[1] = 2;
    std::array<int,dim> N{25,10};
    GridType grid(L,N); 
    auto gv = grid.leafGridView();
    double h = 0.2;  // inicijalni korak h. Kako je mreža kvadratna
                     // kod svakog profinjenja h se prepolavlja. 

    // FEM
    using FEM = Dune::LagrangeCubeLocalFiniteElement<double, double, dim, 1>;
    FEM fem;
    // Vaš kod koji u jednoj petlji profinjuje mrežu i ispisuje procjene za 
    // alpha i C.
    
    

    return 0;
}

#include <iostream>
#include <vector>

#include <cinchtest.h>
#include "mpi.h"

#include <flecsi/coloring/simple_box_colorer.h>

using namespace std;

TEST(simple_colorer, simpletest2d)
{
  int size;
  int rank;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  size_t grid_size[1] = {10};
  size_t ncolors[1]={3};
  size_t nhalo = 1;
  size_t nhalo_domain = 1;
  size_t thru_dim = 0;
  flecsi::coloring::simple_box_colorer_t<1> sbc;
  auto col = sbc.color(grid_size, nhalo, nhalo_domain, thru_dim, ncolors);

  cout<<"Rank-"<<rank<<"::Partition Box:LBND  = { "<<col.partition[0].box.lowerbnd[0]
    <<" } "<<endl;

  cout<<"Rank-"<<rank<<"::Partition Box:UBND  = { "<<col.partition[0].box.upperbnd[0]
    <<" } "<<endl;

  cout<<"Rank-"<<rank<<"::Partition Box:Strides  = { "<<col.partition[0].strides[0]
    <<" } "<<endl;
  cout<<"Rank-"<<rank<<"::Partition-Box:#Halo = " <<col.partition[0].nhalo<<endl;
  cout<<"Rank-"<<rank<<"::Partition-Box:#DomainHalo = " <<col.partition[0].nhalo_domain<<endl;
  cout<<"Rank-"<<rank<<"::Partition-Box:Through dim = " <<col.partition[0].thru_dim<<endl;
  
  cout<<"Rank-"<<rank<<"::Partition-Box:On domain boundary = [ ";
  for (size_t i = 0 ; i < 4; i++)
     cout<<col.partition[0].onbnd[i]<< "  ";
  cout<<"]"<<std::endl;

  //cout<<"Rank-"<<rank<<"::Partition-Box:On domain boundary = [ "<<col.partition.onbnd<<" ]"<<endl;

  cout<<"Rank-"<<rank<<"::Exclusive-Box:LBND  = { "<<col.exclusive[0].box.lowerbnd[0]
    <<" } "<<endl;

  cout<<"Rank-"<<rank<<"::Exclusive-Box:UBND  = { "<<col.exclusive[0].box.upperbnd[0]
    <<" } "<<endl;

  cout<<"Rank-"<<rank<<"::Exclusive-Box:colors = "<<col.exclusive[0].colors[0]<<endl;

  for (auto s: col.shared[0])
  {
    cout<<"Rank-"<<rank<<"::Shared-Boxes:LBND  = { "<<s.box.lowerbnd[0]
      <<" } "<<endl;

    cout<<"Rank-"<<rank<<"::Shared-Boxes:UBND  = { "<<s.box.upperbnd[0]
      <<" } "<<endl;

    cout<<"Rank-"<<rank<<"::Shared-Boxes:#Colors = "<<s.colors.size()<<endl;
    for (auto c: s.colors)
     cout<<"Rank-"<<rank<<"::Shared-Boxes:colors = "<<c<<endl;
    cout<<endl;
  }

  for (auto g: col.ghost[0])
  {
    cout<<"Rank-"<<rank<<"::Ghost-Boxes:LBND  = { "<<g.box.lowerbnd[0]
      <<" } "<<endl;

    cout<<"Rank-"<<rank<<"::Ghost-Boxes:UBND  = { "<<g.box.upperbnd[0]
      <<" } "<<endl;

    cout<<"Rank-"<<rank<<"::Ghost-Boxes:#Colors = "<<g.colors.size()<<endl;;
    for (auto c: g.colors)
     cout<<"Rank-"<<rank<<"::Ghost-Boxes:colors = "<<c<<endl;
    cout<<endl;
  }

  for (auto d: col.domain_halo[0])
  {
    cout<<"Rank-"<<rank<<"::DomainHalo-Boxes:LBND  = { "<<d.lowerbnd[0]
      <<" } "<<endl;

    cout<<"Rank-"<<rank<<"::DomainHalo-Boxes:UBND  = { "<<d.upperbnd[0]
      <<" } "<<endl;
  }
  
  for (auto d: col.overlay)
  {
    cout<<"Rank-"<<rank<<"::Overlay-Boxes:LBND  = { "<<d.lowerbnd[0]
      <<" } "<<endl;

    cout<<"Rank-"<<rank<<"::Overlay-Boxes:UBND  = { "<<d.upperbnd[0]
      <<" } "<<endl;
  }
}
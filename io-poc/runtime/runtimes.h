#pragma once

#include <flecsi-config.h>
#include <ristra-utils-config.h>

#if !defined(FLECSI_ENABLE_MPI)
#error FLECSI_ENABLE_MPI not defined! This file depends on MPI!
#endif

#include <mpi.h>

#include <ristra-utils/control/runtime.h>

#include <io-poc/control/control.h>

using namespace ristra::control;

inline int initialize_MPI(int argc, char ** argv) {
  MPI_Init(&argc, &argv);
  return 0;
} // initialize_MPI

inline int finalize_MPI(int argc, char ** argv, runtime_exit_mode_t mode) {
  MPI_Finalize();
  return 0;
} // finalize_MPI

inline bool output_MPI(int argc, char ** argv) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  return rank == 0 ? true : false;
} // output_MPI

inline runtime_handler_t handler{ initialize_MPI, finalize_MPI, output_MPI };

ristra_append_runtime_handler(handler);

static const bool specialization_control_registered =
  ristra::control::runtime_t::instance().register_driver(
    io_poc::control_t::execute);
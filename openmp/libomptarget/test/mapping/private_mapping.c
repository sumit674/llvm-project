// RUN: %libomptarget-compile-aarch64-unknown-linux-gnu
// RUN: %libomptarget-run-fail-aarch64-unknown-linux-gnu 2>&1 \
// RUN: | %fcheck-aarch64-unknown-linux-gnu

// RUN: %libomptarget-compile-powerpc64-ibm-linux-gnu
// RUN: %libomptarget-run-fail-powerpc64-ibm-linux-gnu 2>&1 \
// RUN: | %fcheck-powerpc64-ibm-linux-gnu

// RUN: %libomptarget-compile-powerpc64le-ibm-linux-gnu
// RUN: %libomptarget-run-fail-powerpc64le-ibm-linux-gnu 2>&1 \
// RUN: | %fcheck-powerpc64le-ibm-linux-gnu

// RUN: %libomptarget-compile-x86_64-pc-linux-gnu
// RUN: %libomptarget-run-fail-x86_64-pc-linux-gnu 2>&1 \
// RUN: | %fcheck-x86_64-pc-linux-gnu

// RUN: %libomptarget-compile-nvptx64-nvidia-cuda
// RUN: %libomptarget-run-fail-nvptx64-nvidia-cuda 2>&1 \
// RUN: | %fcheck-nvptx64-nvidia-cuda

#include <assert.h>
#include <stdio.h>

int main() {
  int data1[3] = {1}, data2[3] = {2}, data3[3] = {3};
  int sum[16] = {0};
#pragma omp target teams distribute parallel for map(tofrom                    \
                                                     : sum)                    \
    firstprivate(data1, data2, data3)
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 3; ++j) {
      sum[i] += data1[j];
      sum[i] += data2[j];
      sum[i] += data3[j];
    }
  }

  for (int i = 0; i < 16; ++i) {
    assert(sum[i] == 6);
  }

  printf("PASS\n");

  return 0;
}

// CHECK: PASS

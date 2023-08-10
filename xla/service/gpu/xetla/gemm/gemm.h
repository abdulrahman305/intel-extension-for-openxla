/* Copyright (c) 2023 Intel Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#pragma once

#include <sycl/sycl.hpp>

namespace gpu {
namespace xetla {

#define HGEMM_DESC_FUNC(WG_M, WG_N, SG_M, SG_N, SG_K, SLM_KS, B_ROW_MAJOR)                         \
  void                                                                                             \
      hgemm_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(              \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const int m, const int n, const int k);                             \
  void                                                                                             \
      hgemm_bias_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(         \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const sycl::half* bias, const int m,                                \
          const int n, const int k);                                                               \
  void                                                                                             \
      hgemm_bias_res_res_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_( \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const sycl::half* bias, const sycl::half* res0,                     \
          const sycl::half* res1, const int m, const int n, const int k);                          \
  void                                                                                             \
      hgemm_bias_gelu_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(    \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const sycl::half* bias, const int m,                                \
          const int n, const int k);                                                               \
  void                                                                                             \
      hgemm_resmul_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(       \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const sycl::half* mul, const int m,                                 \
          const int n, const int k);                                                               \
  void                                                                                             \
      hgemm_silu_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(         \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const int m, const int n, const int k);                             \
  void                                                                                             \
      hgemm_res_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(          \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const sycl::half* res, const int m,                                 \
          const int n, const int k);                                                               \
  void                                                                                             \
      hgemm_qkv_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(          \
          sycl::queue& queue, sycl::half* out0, sycl::half* out1,                                  \
          sycl::half* out2, const sycl::half* a, const sycl::half* b,                              \
          const int m, const int n, const int k);                                                  \
  void                                                                                             \
      hgemm_qkv_bias_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(     \
          sycl::queue& queue, sycl::half* out0, sycl::half* out1,                                  \
          sycl::half* out2, const sycl::half* a, const sycl::half* b,                              \
          const sycl::half* bias, const int m, const int n, const int k);                          \
  void                                                                                             \
      hgemm_bias_res_##WG_M##x##WG_N##_##SG_M##x##SG_N##x##SG_K##_##SLM_KS##_##B_ROW_MAJOR##_(     \
          sycl::queue& queue, sycl::half* out, const sycl::half* a,                                \
          const sycl::half* b, const sycl::half* bias, const sycl::half* res,                      \
          const sycl::half res_scale, const int m, const int n, const int k);

HGEMM_DESC_FUNC(32, 64, 8, 16, 16, 2, true)
HGEMM_DESC_FUNC(8, 512, 8, 16, 16, 1, true)
HGEMM_DESC_FUNC(16, 256, 8, 16, 16, 1, true)
HGEMM_DESC_FUNC(8, 128, 8, 16, 16, 4, true)
HGEMM_DESC_FUNC(32, 256, 8, 32, 16, 1, true)
HGEMM_DESC_FUNC(16, 128, 8, 16, 16, 1, true)
HGEMM_DESC_FUNC(8, 256, 8, 32, 16, 2, true)
HGEMM_DESC_FUNC(8, 512, 8, 32, 16, 2, true)
HGEMM_DESC_FUNC(256, 256, 32, 64, 32, 1, true)
HGEMM_DESC_FUNC(8, 128, 8, 16, 32, 4, true)
HGEMM_DESC_FUNC(32, 128, 8, 32, 32, 1, true)
HGEMM_DESC_FUNC(32, 64, 8, 16, 32, 2, true)
HGEMM_DESC_FUNC(256, 256, 32, 64, 16, 1, true)

HGEMM_DESC_FUNC(32, 64, 8, 16, 16, 2, false)
HGEMM_DESC_FUNC(8, 512, 8, 16, 16, 1, false)
HGEMM_DESC_FUNC(16, 256, 8, 16, 16, 1, false)
HGEMM_DESC_FUNC(8, 128, 8, 16, 16, 4, false)
HGEMM_DESC_FUNC(32, 256, 8, 32, 16, 1, false)
HGEMM_DESC_FUNC(16, 128, 8, 16, 16, 1, false)
HGEMM_DESC_FUNC(8, 256, 8, 32, 16, 2, false)
HGEMM_DESC_FUNC(8, 512, 8, 32, 16, 2, false)
HGEMM_DESC_FUNC(256, 256, 32, 64, 32, 1, false)
HGEMM_DESC_FUNC(8, 128, 8, 16, 32, 4, false)
HGEMM_DESC_FUNC(32, 128, 8, 32, 32, 1, false)
HGEMM_DESC_FUNC(32, 64, 8, 16, 32, 2, false)
HGEMM_DESC_FUNC(256, 256, 32, 64, 16, 1, false)

}  // namespace xetla
}  // namespace gpu

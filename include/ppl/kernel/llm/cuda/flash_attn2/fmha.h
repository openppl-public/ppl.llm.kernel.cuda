// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef __PPL_KERNEL_LLM_CUDA_FLASH_ATTN2_FMHA_H__
#define __PPL_KERNEL_LLM_CUDA_FLASH_ATTN2_FMHA_H__

#include "ppl/kernel/llm/cuda/common/general_include.h"

namespace ppl { namespace kernel { namespace llm { namespace cuda { namespace flash_attn2 {

ppl::common::RetCode flash_attn2_fmha(
    const cudaStream_t stream,
    const cudaDeviceProp& device_prop,
    const ppl::common::datatype_t datatype,
    const void* query,                      // device ptr  (b, max_seqlen, num_heads, head_dim)
    const void* key,                        // device ptr  (b, max_kvlen, num_kv_heads, head_dim)
    const void* value,                      // device ptr  (b, max_kvlen, num_kv_heads, head_dim)
    const void* optional_attn_mask,         // device ptr, (b, num_heads, max_seqlen, max_kvlen)
                                            //     maybe broadcasted to batches/heads
                                            //     set to nullptr to disable mask
    const void* optional_seqstart_q,        // device ptr, (b+1, )
                                            // set to nullptr to disable dynamic batching
    const void* optional_seqstart_k,        // device ptr, (b+1)
    const void* optional_alibi_slopes,      // device ptr, (batch, heads) or (heads,)
                                            // set to nullptr to disable alibi
    const int64_t batch,
    const int64_t query_stride_b,
    const int64_t query_stride_s,
    const int64_t query_stride_h,
    const int64_t key_stride_b,
    const int64_t key_stride_s,
    const int64_t key_stride_h,
    const int64_t value_stride_b,
    const int64_t value_stride_s,
    const int64_t value_stride_h,
    const int64_t mask_stride_b,           // mask shape (batch, num_heads, max_seqlen, max_kvlen)
    const int64_t mask_stride_s,           // can be broadcasted to batches and heads
    const int64_t mask_stride_h,
    const int64_t output_stride_s,
    const int64_t alibi_slopes_stride_b,  // set batch stride to 0 for sharing coeff between batches
    const int64_t max_seqlen,
    const int64_t max_kvlen,
    const int64_t num_heads,
    const int64_t num_kv_heads,
    const int64_t head_dim,
    const bool is_causal,
    const float attn_scale,
    void* output);                          // device ptr, (b, max_seqlen, num_heads, head_dim)

}}}}}

#endif

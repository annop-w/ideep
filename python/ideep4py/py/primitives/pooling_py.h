/*
 *Copyright (c) 2018 Intel Corporation.
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 *
 */


#ifndef _POOLING_PY_H_
#define _POOLING_PY_H_

#include <vector>
#include <memory>
#include "op_param.h"
#include "mdarray.h"
#include "utils.h"
#include "ideep.hpp"

class Pooling2D
{
public:
  using tensor = ideep::tensor;
  using scratch_allocator = ideep::utils::scratch_allocator;
  using pooling_forward = ideep::pooling_forward;
  using pooling_backward = ideep::pooling_backward;
  using prop_kind = ideep::prop_kind;

  static std::vector<mdarray> Forward(mdarray *src,
                                      pooling_param_t *pp) {
    auto dst = pooling_forward::compute<scratch_allocator>(
                  *(src->get()), pp->out_dims,
                  tensor::dims {pp->sy, pp->sx},
                  tensor::dims {pp->kh, pp->kw},
                  tensor::dims {pp->pad_lh, pp->pad_lw},
                  tensor::dims {pp->pad_rh, pp->pad_rw},
                  pooling_algo_convert(pp->algo_kind),
                  prop_kind::forward_training);

    std::vector<mdarray> outs;
    outs.push_back(mdarray(dst));

    if (pp->algo_kind == pooling_param_t::algorithm::pooling_max)
      outs.push_back(mdarray(*dst.get_extra()));

    return outs;
  }

  static mdarray Backward(mdarray *grady,
                          mdarray *ws,
                          pooling_param_t *pp) {
    auto gx = pooling_backward::compute<scratch_allocator>(
                  *(grady->get()),
                  ws ? ws->get() : NULL,
                  pp->out_dims, NULL,
                  tensor::dims {pp->sy, pp->sx},
                  tensor::dims {pp->kh, pp->kw},
                  tensor::dims {pp->pad_lh, pp->pad_lw},
                  tensor::dims {pp->pad_rh, pp->pad_rw},
                  pooling_algo_convert(pp->algo_kind));

    auto out = mdarray(gx);
    return out;
  }

};

#endif // _POOLING_PY_H_
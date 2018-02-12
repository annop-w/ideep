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


#ifndef _LRN_H_
#define _LRN_H_

#include <mkldnn.hpp>
#include <vector>
#include <memory>
#include "layer.h"
#include "op_param.h"
#include "tensor.h"

template <typename T>
class LocalResponseNormalization : public Layer<T>
{
public:
    LocalResponseNormalization();
    ~LocalResponseNormalization();

    /*
     * Lrn Forward
     * params:
     * src: input, x
     * pp: lrn parameters
     *
     * ret
     * vector<Tensor*>:
     * return dst and workspace
     */
    static std::vector<Tensor *> Forward(Tensor *src, lrn_param_t *pp);

    /*
     * Lrn backward
     * param:
     * src: x
     * diff_dst: diff dst, gy
     * pp: lrn parameters
     * return diff_src gx
     */
    static Tensor *Backward(Tensor* src, Tensor *diff_dst, Tensor *ws, lrn_param_t* pp);

};

#endif // _LRN_H_


// vim: et ts=4 sw=4 cindent cino^=l0,\:0,N-s

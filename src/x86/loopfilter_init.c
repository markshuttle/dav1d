/*
 * Copyright © 2018, VideoLAN and dav1d authors
 * Copyright © 2018, Two Orioles, LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "src/cpu.h"
#include "src/loopfilter.h"

decl_loopfilter_sb_fn(dav1d_lpf_h_sb_y_avx2);
decl_loopfilter_sb_fn(dav1d_lpf_v_sb_y_avx2);
decl_loopfilter_sb_fn(dav1d_lpf_h_sb_uv_avx2);
decl_loopfilter_sb_fn(dav1d_lpf_v_sb_uv_avx2);

void bitfn(dav1d_loop_filter_dsp_init_x86)(Dav1dLoopFilterDSPContext *const c) {
    const unsigned flags = dav1d_get_cpu_flags();

    if (!(flags & DAV1D_X86_CPU_FLAG_AVX2)) return;

#if BITDEPTH == 8 && ARCH_X86_64
    c->loop_filter_sb[0][0] = dav1d_lpf_h_sb_y_avx2;
    c->loop_filter_sb[0][1] = dav1d_lpf_v_sb_y_avx2;
    c->loop_filter_sb[1][0] = dav1d_lpf_h_sb_uv_avx2;
    c->loop_filter_sb[1][1] = dav1d_lpf_v_sb_uv_avx2;
#endif
}

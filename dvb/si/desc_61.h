/*****************************************************************************
 * desc_61.h: ETSI EN 300 468 Descriptor 0x61: Short smoothing buffer
 *****************************************************************************
 * Copyright (C) 2011 Unix Solutions Ltd.
 *
 * Authors: Georgi Chorbadzhiyski <georgi@unixsol.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *****************************************************************************/

/*
 * Normative references:
 *  - ETSI EN 300 468 V1.11.1 (2010-04) (SI in DVB systems)
 */

#ifndef __BITSTREAM_DVB_DESC_61_H__
#define __BITSTREAM_DVB_DESC_61_H__

#include <bitstream/common.h>
#include <bitstream/mpeg/psi/descriptors.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
 * Descriptor 0x61: Short smoothing buffer descriptor
 *****************************************************************************/
#define DESC61_HEADER_SIZE      (DESC_HEADER_SIZE + 1)

static inline void desc61_init(uint8_t *p_desc)
{
    desc_set_tag(p_desc, 0x61);
    desc_set_length(p_desc, DESC61_HEADER_SIZE - DESC_HEADER_SIZE);
}

static inline uint8_t desc61_get_sb_size(const uint8_t *p_desc)
{
    return p_desc[2] >> 6;
}

static inline void desc61_set_sb_size(uint8_t *p_desc, uint8_t i_sb_size)
{
    p_desc[2] = (p_desc[2] & 0x3f) | (i_sb_size << 6);
}

static inline uint8_t desc61_get_sb_leak_rate(const uint8_t *p_desc)
{
    return p_desc[2] & 0x3f;
}

static inline void desc61_set_sb_leak_rate(uint8_t *p_desc, uint8_t i_sb_leak_rate)
{
    p_desc[2] = (p_desc[2] & 0xc0) | (i_sb_leak_rate & 0x3f);
}

static inline bool desc61_validate(const uint8_t *p_desc)
{
    return desc_get_length(p_desc) >= DESC61_HEADER_SIZE - DESC_HEADER_SIZE;
}

static inline void desc61_print(const uint8_t *p_desc, f_print pf_print,
                                void *opaque, print_type_t i_print_type)
{
    switch (i_print_type) {
    case PRINT_XML:
        pf_print(opaque, "<SHORT_SMOOTHING_BUFFER_DESC sb_size=\"%u\" sb_leak_rate=\"%u\"/>",
                 desc61_get_sb_size(p_desc),
                 desc61_get_sb_leak_rate(p_desc)
                );
        break;
    default:
        pf_print(opaque, "    - desc 61 short_smoothing_buffer sb_size=%u sb_leak_rate=%u",
                 desc61_get_sb_size(p_desc),
                 desc61_get_sb_leak_rate(p_desc)
                );
    }
}

#ifdef __cplusplus
}
#endif

#endif

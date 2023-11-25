/**
 * Copyright (c) 2015, Chao Wang (hit9 <hit9@icloud.com>)
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef SHARE_H
#define SHARE_H

#define BUF_UNIT 128
#define FILE_READ_BUF_UNIT 1024
#define FILE_WRITE_BUF_UNIT 128

typedef enum {
    TD_OK = 0,
    TD_EIOR = 1,
    TD_EIOW = 2,
    TD_ENOMEM = 3,
    TD_ESYNTAX = 4,
    TD_ENOTFOUND = 5,
    TD_EINVALIDIDX = 6,
} td_error_t;

static const char *td_emsgs[] = {
    [TD_EIOR]         = "error to read %s\n",
    [TD_EIOW]         = "error to write %s\n",
    [TD_ENOMEM]       = "no memory\n",
    [TD_ESYNTAX]      = "syntax error at line %lu\n",
    [TD_ENOTFOUND]    = "task %lu not found\n",
    [TD_EINVALIDIDX]  = "invalid task index %d\n",
};

#endif

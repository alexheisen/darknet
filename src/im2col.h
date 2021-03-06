#ifndef IM2COL_H
#define IM2COL_H

#include <stddef.h>
#include <stdint.h>

void im2col_cpu(float* data_im,
        int channels, int height, int width,
        int ksize, int stride, int pad, float* data_col);

#ifdef GPU

void im2col_ongpu(float *im,
         int channels, int height, int width,
         int ksize, int stride, int pad,float *data_col);

void im2col_align_ongpu(float *im,
    int channels, int height, int width,
    int ksize, int stride, int pad, float *data_col, int bit_align);

void im2col_align_bin_ongpu(float *im,
    int channels, int height, int width,
    int ksize, int stride, int pad, float *data_col, int bit_align);

void float_to_bit_gpu(float *src, unsigned char *dst, size_t size);

void transpose_bin_gpu(unsigned char *A, unsigned char *B, const int n, const int m,
    const int lda, const int ldb, const int block_size);

void transpose_uint32_gpu(uint32_t *src, uint32_t *dst, int src_h, int src_w, int src_align, int dst_align);

void transpose_uint32_gpu_2(uint32_t *src, uint32_t *dst, int src_h, int src_w, int src_align, int dst_align);

void repack_input_gpu(float *input, float *re_packed_input, int w, int h, int c);

void repack_input_gpu_2(float *input, float *re_packed_input, int w, int h, int c);

void repack_input_gpu_bin(float *input, uint32_t *re_packed_input_bin, int w, int h, int c);

void fill_int8_gpu(unsigned char *src, unsigned char val, size_t size);

// shared_memory + partial coalescing = GOOD
void gemm_nn_custom_bin_mean_transposed_gpu(int M, int N, int K,
    unsigned char *A, int lda,
    unsigned char *B, int ldb,
    float *C, int ldc, float *mean_arr, float *bias);

// sequentially - BAD
void gemm_nn_custom_bin_mean_transposed_sequentially_gpu(int M, int N, int K,
    unsigned char *A, int lda,
    unsigned char *B, int ldb,
    float *C, int ldc, float *mean_arr);

void convolve_gpu(float *input, float *weights, float *output, int in_w, int in_h, int in_c, int n, int size, int pad);

void convolve_bin_gpu(float *input, float *weights, float *output, int in_w, int in_h, int in_c, int n, int size, int pad,
    int new_lda, float *mean_arr_gpu);

void convolve_bin_cpu(float *input, float *weights, float *output, int in_w, int in_h, int in_c, int n,
    int size, int pad, int new_lda, float *mean_arr_gpu);

void convolve_cpu(float *input, float *weights, float *output, int in_w, int in_h, int in_c, int n, int size, int pad);

#endif
#endif

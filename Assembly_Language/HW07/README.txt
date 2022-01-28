**AS HW07 CSIE 3B 408410120 鍾博丞**

**I strongly suggest that use markdown (switch .txt to .md) to read this report.**

- CPU

    - Model

      AMD R9-3900X

    - Flags

      fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr **sse** **sse2** ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl nonstop_tsc cpuid extd_apicid aperfmperf rapl pni pclmulqdq monitor ssse3 fma cx16 **sse4_1** **sse4_2** movbe popcnt aes xsave **avx** f16c rdrand lahf_lm cmp _legacy svm extapic cr8_legacy abm **sse4a** misalignsse 3dnowprefetch osvw ibs skinit wdt tce topoext perfctr_core perfctr_nb bpext perfctr_llc mwaitx cpb cat_l3 cdp_l3 hw_pstate ssbd mba ibpb stibp vmmcall fsgsbase bmi1 **avx2** smep bmi2 cqm rdt_a rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local clzero irperf xsaveerptr rdpru wbnoinvd arat npt lbrv svm_lock nrip_save tsc_scale vm cb_clean flushbyasid decodeassists pausefilter pfthreshold avic v_vmsave_vmload vgif v_spec_ctrl umip rdpid overflow_recov succor smca sme sev sev_es

- RAM

    32GB DDR4 3600MHz (Double channel)

- SSD

    ADATA SX8200Pro 1TB TLC (Seq. R: 3500MB/s, Seq. W: 3000MB/s, Random R: 451.3K IOPS, Random W: 325.6K IOPS)

- Environment

    Arch Linux 5.15.8-arch1-1 using KDE plasma

- Instruction set used

  AVX

- compiled with 

```bash
gcc -g -mavx hw7.c -o hw7
gcc -g -mavx hw7_simd.c -o hw7_simd
```

- or with Makefile

```bash
make
```

- execute the program

```bash
./hw7
./hw7_simd
```

- Intrinsic Functions used

```assembly
_mm256_setzero_ps
_mm256_mul_ps
_mm256_add_ps
_mm256_hadd_ps
```

**The output of hw7simd is output_simd.txt, to compare the results with and without simd instruction**

- Result

  - Without simd

    | Action  | Read data time (ns) | Compute data time (ns) | Write data time (ns) |
    | ------- | ------------------- | ---------------------- | -------------------- |
    | #1      | 12,834,171          | 20,002,303             | 57,364               |
    | #2      | 12,824,782          | 20,574,504             | 58,080               |
    | #3      | 12,922,115          | 20,516,238             | 60,776               |
    | #4      | 12,925,752          | 20,487,882             | 56,898               |
    | #5      | 12,596,287          | 19,734,257             | 57,499               |
    | **AVG** | 12,820,621          | **20,263,037**         | 58,119.4             |
    | STDEV   | 134,052.4330        | 373,921.1881           | 1,541.7843           |

  - With simd

    | Action  | Read data time (ns) | Compute data time (ns) | Write data time (ns) |
    | ------- | ------------------- | ---------------------- | -------------------- |
    | #1      | 12,687,909          | 4,956,230              | 56,517               |
    | #2      | 11,867,887          | 4,977,876              | 59,311               |
    | #3      | 11,285,623          | 4,796,464              | 56,496               |
    | #4      | 11,997,463          | 4,962,167              | 57,999               |
    | #5      | 12,946,264          | 4,771,313              | 52,730               |
    | **AVG** | 12,157,029.2        | **4,892,810**          | 56,610.6             |
    | STDEV   | 665,796.1927        | 100,140.8844           | 2,464.7903           |
    
  - Almost **4 times faster** in compute data with simd.

- Result with optimize -O3

  - Without simd

    | Action  | Read data time (ns) | Compute data time (ns) | Write data time (ns) |
    | ------- | ------------------- | ---------------------- | -------------------- |
    | #1      | 11,778,090          | 5,550,657              | 62,777               |
    | #2      | 11,903,780          | 5,287,050              | 54,072               |
    | #3      | 13,647,131          | 5,358,344              | 54,893               |
    | #4      | 11,981,348          | 5,516,380              | 54,182               |
    | #5      | 12,255,403          | 5,334,760              | 55,985               |
    | **AVG** | 12,313,150.4        | **5,409,438.2**        | 56,381.8             |
    | STDEV   | 765,964.3582        | 116,775.0191           | 3,655.3678           |

  - With simd

    | Action  | Read data time (ns) | Compute data time (ns) | Write data time (ns) |
    | ------- | ------------------- | ---------------------- | -------------------- |
    | #1      | 11,920,308          | 690,362                | 56,796               |
    | #2      | 12,592,572          | 694,290                | 59,400               |
    | #3      | 11,757,793          | 702,445                | 56,034               |
    | #4      | 17,562,406          | 709,788                | 84,016               |
    | #5      | 11,710,094          | 707,324                | 57,457               |
    | **AVG** | 13,108,634.6        | **700,841.8**          | 62,758.6             |
    | STDEV   | 2,514,717.143       | 8,327.3038             | 11,998.6613          |

  - Almost **7 times faster** in compute data with simd.

- It has 3.75 times faster by optimizing flag -O3 without simd.

- It has 6.98 times faster by optimizing flag -O3 with simd.

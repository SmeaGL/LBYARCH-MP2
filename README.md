# LBYARCH-MP2
Machine Project for LBYARCH course 

Analysis
1. The assembly implementation is significantly faster than the C implementation.
2. Efficiency-wise, assembly code demonstrates better performance due to its low-level control over hardware and the use of SIMD instructions (mulss, addss) for floating-point operations.
3. Functional correctness is equally important, and ensuring the results match across both implementations is critical.
4. Debugging assembly code is more challenging than debugging C code because it lacks the high-level abstractions provided by C and requires a deep understanding of hardware-level details.
5. Assembly shows greater potential for optimized execution, especially for larger datasets or performance-critical applications.
6. While both implementations highlight high performance, the assembly version demands a greater focus on precision and attention to detail to achieve the expected, accurate results. This trade-off makes C more suitable for general-purpose, maintainable code, whereas assembly shines in scenarios requiring maximum performance and efficiency.

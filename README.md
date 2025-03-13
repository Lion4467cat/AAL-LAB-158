# AAL-LAB-158
The programs of AAL Lab
for the bubble sort programs following are the inferences from the output
Based on the computed table and the output data, here are some key inferences:

Quadratic Growth Confirmation:

Notice that the ratio n²/Swap_Count remains nearly constant (around 4) across the different array sizes. This indicates that the number of swaps grows roughly as a constant times n².
In theoretical worst-case bubble sort, the maximum number of swaps is about n(n-1)/2, which is quadratic in n. Although your data comes from random arrays (not worst-case), the near-constant ratio strongly supports that the swap count scales quadratically.
Inefficiency for Large n:

As n increases, the actual swap count rises dramatically. For example, going from n = 100 to n = 5000, the swap count increases from 2334 to over 6 million.
This reinforces the understanding that bubble sort becomes extremely inefficient for large datasets.
Time Taken vs. Swap Count:

While the measured time values are very small for small arrays, they increase noticeably as n grows. This increase is consistent with the quadratic growth of the swap count.
However, note that time measurements can be influenced by other factors (like system load), but the trend still aligns with the expected complexity.
Other Ratios:

### ln(n)/Swap_Count and n/Swap_Count: These ratios decrease as n increases, which makes sense because bubble sort does not have a logarithmic or linear behavior—the dominant cost is quadratic.
###  n·ln(n)/Swap_Count: This ratio also decreases with increasing n, again reinforcing that the underlying behavior of bubble sort is not n·ln(n) but closer to quadratic.



### Overall Inference:
The experimental data confirms that bubble sort’s performance is dominated by quadratic behavior. Even though the arrays were randomly generated (which might sometimes yield fewer swaps than the worst-case), the ratios and trends indicate that as the input size increases, the number of swaps (and therefore the time taken) increases approximately as n². This demonstrates why bubble sort is generally unsuitable for larger datasets and why more efficient sorting algorithms are preferred in practice.

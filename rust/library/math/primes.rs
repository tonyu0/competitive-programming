// ========== prime-factorization ==========
//nを素因数分解
fn prime_factorization(n: usize) -> Vec<u64> {
    let mut table: Vec<u64> = vec![0; n + 1];
    let mut i = 2;
    while i * i <= n {
        while n % i == 0 {
            table[i] += 1;
            n /= i;
        }
        i += 1;
    }
    if n != 1 {
        table[n] += 1;
    }
    table
}
// ========== eratosthenes ==========
fn eratosthenes(n: size) -> Vec<bool> {
    let mut is_prime: Vec<bool> = vec![true; n];
    is_prime[0] = false;
    is_prime[1] = false;
    for i in 2..n {
        if is_prime[i] {
            let mut j = i * 2;
            while j <= n {
                is_prime[j] = false;
                j += i;
            }
        }
    }
    is_prime
}

// ========== pascal ==========
fn pascal(n: usize) -> Vec<Vec<usize>> {
    let mut c: Vec<Vec<usize>> = vec![vec![0; n]; n];
    for i in 0..n {
        c[i][0] = 1;
        for j in 1..i {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
        c[i][i] = 1;
    }
    c
}

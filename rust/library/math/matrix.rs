// ========== matrix ==========
// mul(a_x*y, b_z*w) = c_x*w
fn mul(a: Vec<Vec<u64>>, b: Vec<Vec<u64>>) -> Vec<Vec<u64>> {
    let mut res: Vec<Vec<u64>> = vec![vec![0; b[0].len()]; a.len()];
    for i in 0..a.len() {
        for j in 0..b[0].len() {
            let mut val = 0;
            for k in 0..b.len() {
                val ^= a[i][k] & b[k][j];
            }
            res[i][j] = val;
        }
    }
    res
}
// 正方行列のみ
fn pow(mut a: Vec<Vec<u64>>, mut e: u64) -> Vec<Vec<u64>> {
    let mut res: Vec<Vec<u64>> = vec![vec![0; a.len()]; a.len()];
    for i in 0..a.len() {
        res[i][i] = !0u64;
    }
    while e > 0 {
        if e & 1 == 1 {
            res = mul(res, a.clone());
        }
        a = mul(a.clone(), a.clone());
        e >>= 1;
    }
    res
}

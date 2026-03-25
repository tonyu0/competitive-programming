// ========== random ==========
fn rand() -> u32 {
    static mut X: u32 = 123456789;
    static mut Y: u32 = 362436069;
    static mut Z: u32 = 521288629;
    static mut W: u32 = 88675123;
    unsafe {
        let t = X ^ (X << 11);
        X = Y;
        Y = Z;
        Z = W;
        W = (W ^ (W >> 19)) ^ (t ^ (t >> 8));
        W
    }
}

// ========== gcd ==========
fn gcd(a: u64, b: u64) -> u64 {
    if b == 0 {
        return a;
    }
    gcd(b, a % b)
}
fn lcm(a: u64, b: u64) -> u64 {
    a / gcd(a, b) * b
}
fn gcd_array(a: &Vec<u64>) -> u64 {
    let mut res = a[0];
    for i in 1..a.len() {
        res = gcd(res, a[i]);
    }
    res
}
fn lcm_array(a: &Vec<u64>) -> u64 {
    let mut res = a[0];
    for i in 1..a.len() {
        res = lcm(res, a[i]);
    }
    res
}

// ========== permutation ==========
fn permutation(n: usize, p: &mut Vec<usize>, used: &mut Vec<bool>, all: &mut Vec<Vec<usize>>) {
    if p.len() == n {
        all.push(p.to_vec());
        return;
    }
    for i in 0..n {
        if !used[i] {
            p.push(i);
            used[i] = true;
            permutation(n, p, used, all);
            p.pop();
            used[i] = false;
        }
    }
}
// ========== cumsum 2d ==========
fn cumsum_2d(w: usize, h: usize) -> Vec<Vec<usize>> {
    let mut s: Vec<Vec<usize>> = vec![vec![0; w + 5]; h + 5];
    for i in 0..h {
        for j in 0..w {
            s[i + 1][j + 1] = a[i][j];
        }
    }
    for i in 1..h + 1 {
        for j in 1..w + 1 {
            s[i][j + 1] += s[i][j];
        }
    }
    for i in 1..h + 1 {
        for j in 1..w + 1 {
            s[i + 1][j] += s[i][j];
        }
    }
    s
}
